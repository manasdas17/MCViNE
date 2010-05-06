#!/usr/bin/env python
# Mike McKerns (mmckerns@caltech.edu)

#######################################################################
# scaling and optimizer configuration parameters
# hard-wired: use DE solver, parameter sensitivity calculation
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
# the subdiameter calculation
#######################################################################
def costFactory(i):
  """a cost factory for the cost function"""

  def cost(rv):
    """compute the diameter as a calculation of cost

  Input:
    - rv -- 1-d array of model parameters

  Output:
    - diameter -- scale * | F(x) - F(x')|**2
    """

    # prepare x and xprime
    params = rv[:-1]                         #XXX: assumes Xi' is at rv[-1]
    params_prime = rv[:i]+rv[-1:]+rv[i+1:-1] #XXX: assumes Xi' is at rv[-1]

    # get the F(x) response
    Fx = model(params)

    # get the F(x') response
    Fxp = model(params_prime)

    # compute diameter
    return -scale * ((Fx - Fxp)**2).sum()

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

 #stepmon = VerboseSow(100)
  stepmon = Sow()
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
  diameter_squared = -solver.bestEnergy / scale  #XXX: scale != 0
  func_evals = len(evalmon.y)
  return diameter_squared, func_evals


#######################################################################
# loop over model parameters to calculate concentration of measure
#######################################################################
def UQ(start,end,lower,upper):
  diameters = []
  function_evaluations = []
  total_func_evals = 0
  total_diameter = 0.0

  for i in range(start,end+1):
    lb = lower + [lower[i]]
    ub = upper + [upper[i]]
  
    #construct cost function and run optimizer
    cost = costFactory(i)
    subdiameter, func_evals = optimize(cost,lb,ub) #XXX: no initial conditions

    function_evaluations.append(func_evals)
    diameters.append(subdiameter)

    total_func_evals += function_evaluations[-1]
    total_diameter += diameters[-1]

  print "subdiameters (squared): %s" % diameters
  print "diameter (squared): %s" % total_diameter
  print "func_evals: %s => %s" % (function_evaluations, total_func_evals)

  return total_diameter


#######################################################################
# rank, bounds, and restart information 
#######################################################################
if __name__ == '__main__':
  function_name = "SourceMonitorInstrument"

  # interval bounds for [source_E0,source_dE]
  bounds = [(60.0,80.0),(0.0,10.0)]
  lower_bounds = [i[0] for i in bounds]
  upper_bounds = [i[1] for i in bounds]

  RVstart = 0; RVend = 1
  RVmax = len(lower_bounds) - 1

  # when not a random variable, set the value to the lower bound
  for i in range(0,RVstart):
    upper_bounds[i] = lower_bounds[i]
  for i in range(RVend+1,RVmax+1):
    upper_bounds[i] = lower_bounds[i]

  lbounds = lower_bounds[RVstart:1+RVend]
  ubounds = upper_bounds[RVstart:1+RVend]

  print "...SETTINGS..."
  print "npop = %s" % npop
  print "maxiter = %s" % maxiter
  print "maxfun = %s" % maxfun
  print "convergence_tol = %s" % convergence_tol
  print "crossover = %s" % crossover
  print "percent_change = %s" % percent_change
  print "..............\n\n"

  print " model: f(x) = %s(x)" % function_name
  param_string = "["
  for i in range(RVmax+1): 
    param_string += "'x%s'" % str(i+1)
    if i == (RVmax):
      param_string += "]"
    else:
      param_string += ", "

  print " parameters: %s" % param_string
  print "  varying 'xi', with i = %s" % range(RVstart+1,RVend+2)
  print " lower bounds: %s" % lower_bounds
  print " upper bounds: %s" % upper_bounds
# print " ..."
  diameter = UQ(RVstart,RVend,lower_bounds,upper_bounds)

# EOF
