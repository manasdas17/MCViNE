#!/usr/bin/env python
# Mike McKerns (mmckerns@caltech.edu)

#######################################################################
# scaling and optimizer configuration parameters
# hard-wired: use DE solver, fit to data existing file
#######################################################################
scale = 1.0
npop = 20
maxiter = 1000
maxfun = 1e+6
convergence_tol = 1e-4
crossover = 0.9
percent_change = 0.9


#######################################################################
# the model function
#######################################################################
def model(coeffs):
  source_E0, source_dE = coeffs
  from SourceMonitorInstrumentModel import simulate
  return simulate(source_E0, source_dE)


#######################################################################
# the data reader
#######################################################################
def data(histogram_data):
  from histogram.hdf import load
  h = load(histogram_data)
  # now intensities and energies are numpy arrays
  # return h.I, h.energy
  return h.I


#######################################################################
# the goodness of fit to data
#######################################################################
def costFactory(datafile):
  """a cost factory for the cost function"""

  # read the data
  G = data(datafile)

  def cost(params):
    """compute goodness of fit to data as a calculation of cost

  Input:
    - params -- 1-d array of model parameters

  Output:
    - goodness of fit -- scale * | F(x) - G |**2
    """

    # get the F(x) response
    Fx = model(params)

    # compute goodness of fit
    return scale * (Fx - G)**2

  return cost


#######################################################################
# the differential evolution optimizer
#######################################################################
def optimize(cost,lb,ub):
  from mystic.differential_evolution import DifferentialEvolutionSolver2
  from mystic.termination import CandidateRelativeTolerance as CRT
  from mystic.strategy import Best1Exp
  from mystic import getch, random_seed, VerboseSow, Sow

  random_seed(123)

  stepmon = VerboseSow(100)
 #stepmon = Sow()
  evalmon = Sow()

  ndim = len(lb) # [(1 + RVend) - RVstart] + 1

  solver = DifferentialEvolutionSolver2(ndim,npop)
  solver.SetRandomInitialPoints(min=lb,max=ub)
  solver.SetStrictRanges(min=lb,max=ub)
  solver.SetEvaluationLimits(maxiter,maxfun)

  tol = convergence_tol
  solver.Solve(cost,termination=CRT(tol,tol),strategy=Best1Exp, \
               CrossProbability=crossover,ScalingFactor=percent_change, \
               StepMonitor=stepmon, EvaluationMonitor=evalmon)

  print "solved: %s" % solver.Solution()
  fitness = solver.bestEnergy / scale  #XXX: scale != 0
  func_evals = len(evalmon.y)
  return fitness, func_evals


#######################################################################
# prepare cost function and calculate goodness of fit
#######################################################################
def fit(datafile,lower,upper):

  #construct cost function and run optimizer
  cost = costFactory(datafile)
  fitness, func_evals = optimize(cost,lower,upper) #XXX: no initial conditions

  print "goodness of fit: %s" % fitness
  print "func_evals: %s" % func_evals

  return fitness


#######################################################################
# rank, bounds, and restart information 
#######################################################################
if __name__ == '__main__':
  histogram_data = "e.h5/I(E)"
  function_name = "SourceMonitorInstrument"

  # interval bounds for [source_E0,source_dE]
  bounds = [(60.0,80.0),(0.0,10.0)]
  lower_bounds = [i[0] for i in bounds]
  upper_bounds = [i[1] for i in bounds]

  FVstart = 0; FVend = 1
  FVmax = len(lower_bounds) - 1

  # when not a fit variable, set the value to the lower bound
  for i in range(0,FVstart):
    upper_bounds[i] = lower_bounds[i]
  for i in range(FVend+1,FVmax+1):
    upper_bounds[i] = lower_bounds[i]

  print "...SETTINGS..."
  print "npop = %s" % npop
  print "maxiter = %s" % maxiter
  print "maxfun = %s" % maxfun
  print "convergence_tol = %s" % convergence_tol
  print "crossover = %s" % crossover
  print "percent_change = %s" % percent_change
  print "..............\n\n"

  print " data: '%s'" % histogram_data
  print " model: f(x) = %s(x)" % function_name
  param_string = "["
  for i in range(FVmax+1): 
    param_string += "'x%s'" % str(i+1)
    if i == (FVmax):
      param_string += "]"
    else:
      param_string += ", "

  print " parameters: %s" % param_string
  print "  fitting 'xi', with i = %s" % range(FVstart+1,FVend+2)
  print " lower bounds: %s" % lower_bounds
  print " upper bounds: %s" % upper_bounds
# print " ..."
  fitness = fit(histogram_data,lower_bounds,upper_bounds)

# EOF
