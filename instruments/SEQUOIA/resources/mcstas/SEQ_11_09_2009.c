/* Automatically generated file. Do not edit. 
 * Format:     ANSI C source code
 * Creator:    McStas <http://neutron.risoe.dk>
 * Instrument: SEQ_11_09_2009.instr (Fermi_T0)
 * Date:       Mon May 23 13:28:14 2011
 */


#define MCSTAS_VERSION "1.12a - Apr. 02, 2009"
#define MC_USE_DEFAULT_MAIN
#define MC_EMBEDDED_RUNTIME

#line 1 "mcstas-r.h"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/mcstas-r.h
*
* %Identification
* Written by: KN
* Date:    Aug 29, 1997
* Release: McStas X.Y
* Version: $Revision: 1.101 $
*
* Runtime system header for McStas.
*
* In order to use this library as an external library, the following variables
* and macros must be declared (see details in the code)
*
*   struct mcinputtable_struct mcinputtable[];
*   int mcnumipar;
*   char mcinstrument_name[], mcinstrument_source[];
*   int mctraceenabled, mcdefaultmain;
*   extern MCNUM  mccomp_storein[];
*   extern MCNUM  mcAbsorbProp[];
*   extern MCNUM  mcScattered;
*   #define MCSTAS_VERSION "the McStas version"
*
* Usage: Automatically embbeded in the c code.
*
* $Id: mcstas-r.h,v 1.101 2009/04/02 09:47:46 pkwi Exp $
*
*       $Log: mcstas-r.h,v $
*       Revision 1.101  2009/04/02 09:47:46  pkwi
*       Updated runtime and interoff from dev branch (bugfixes etc.)
*
*       Proceeding to test before release
*
*       Revision 1.108  2009/01/23 14:01:12  farhi
*       Back to smaller buffer size for MPI exchange, to ensure that it works on
*       *most* machines.
*
*       Revision 1.107  2009/01/23 10:51:30  farhi
*       Minor speedup: Identity rotation matrices are now checked for and
*       caculations reduced.
*       It seems this McSatsStable commit did not got through for McStas 1.12a
*
*       Revision 1.106  2009/01/15 15:42:44  farhi
*       Saving lists using MPI: must use MPI_Ssend to avoid the buffer max size
*       in MPI1
*
*       Revision 1.105  2008/10/21 15:19:18  farhi
*       use common CHAR_BUFFER_LENGTH = 1024
*
*       Revision 1.104  2008/09/02 08:36:17  farhi
*       MPI support: block size defined in mcstas-r.h as 1e5. Correct bug when
*       p0, p1 or p2 are NULL, and re-enable S(q,w) save in Isotropic_Sqw with
*       MPI.
*
*       Revision 1.103  2008/08/26 13:32:05  farhi
*       Remove Threading support which is poor efficiency and may give wrong
*       results
*       Add quotes around string instrument parameters from mcgui simulation
*       dialog
*
*       Revision 1.102  2008/08/25 14:13:28  farhi
*       changed neutron-mc to mcstas-users
*
*       Revision 1.101  2008/07/17 12:50:18  farhi
*       MAJOR commit to McStas 2.x
*       uniformized parameter naming in components
*       uniformized SITE for instruments
*       all compile OK
*
*       Revision 1.99  2008/04/25 08:26:33  erkn
*       added utility functions/macros for intersecting with a plane and mirroring a vector in a plane
*
*       Revision 1.98  2008/04/21 15:50:19  pkwi
*       Name change randvec_target_rect -> randvec_target_rect_real .
*
*       The renamed routine takes local emmission coordinate into account, correcting for the
*       effects mentioned by George Apostolopoulus <gapost@ipta.demokritos.gr> to the
*       mcstas-users list (parameter list extended by four parms).
*
*       For backward-compatibility, a define has been added that maps randvec_target_rect
*       to the new routine, defaulting to the "old" behaviour.
*
*       To make any use of these modifications, we need to correct all (or all relevant) comps
*       that have calls to randvec_target_rect.
*
*       Will supply a small doc with plots showing that we now correct for the effect pointed
*       out by George.
*
*       Similar change should in principle happen to the _sphere focusing routine.
*
*       Revision 1.97  2008/02/10 20:55:53  farhi
*       OpenMP number of nodes now set properly from either --threads=NB or
*       --threads which sets the computer core nb.
*
*       Revision 1.96  2008/02/10 15:12:56  farhi
*       mcgui: save log when File/Quit
*       mcrun/mcgui: OpenMP now uses the specified number of nodes
*       mcstas-r: number of OpenMP nodes can be set by user. If left at default
*       (--threads), then use omp_get_num_threads. This may be inaccurate on some systems..
*
*       Revision 1.95  2008/02/09 22:26:27  farhi
*       Major contrib for clusters/multi-core: OpenMP support
*       	try ./configure --with-cc=gcc4.2 or icc
*       then mcrun --threads ...
*       Also tidy-up configure. Made relevant changes to mcrun/mcgui to enable OpenMP
*       Updated install-doc accordingly
*
*       Revision 1.94  2007/08/09 16:47:34  farhi
*       Solved old gcc compilation issue when using macros in macros.
*       Solved MPI issuie when exiting in the middle of a simulation. Now use MPI_Abort.
*
*       Revision 1.93  2007/05/29 14:57:56  farhi
*       New rand function to shoot on a triangular distribution. Useful to simulate chopper time spread.
*
*       Revision 1.92  2007/02/01 15:49:45  pkwi
*       For some instruments (e.g. h8) , it seems that <sys/stat.h> is needed to compile on Mac OS X (like FreeBSD)
*
*       Added define to include this.
*
*       Revision 1.91  2007/01/29 15:51:56  farhi
*       mcstas-r: avoid undef of USE_NEXUS as napi is importer afterwards
*
*       Revision 1.90  2007/01/25 14:57:36  farhi
*       NeXus output now supports MPI. Each node writes a data set in the NXdata
*       group. Uses compression LZW (may be unactivated with the
*       -DUSE_NEXUS_FLAT).
*
*       Revision 1.89  2007/01/23 00:41:05  pkwi
*       Edits by Jiao Lin (linjao@caltech.edu) for embedding McStas in the DANSE project. Define -DDANSE during compile will enable these edits.
*
*       Have tested that McStas works properly without the -DDANSE.
*
*       Jiao: Could you please test if all is now OK?
*       (After 15 minutes) Get current CVS tarball from http://www.mcstas.org/cvs
*
*       Revision 1.88  2007/01/22 01:38:25  farhi
*       Improved NeXus/NXdata support. Attributes may not be at the right place
*       yet.
*
*       Revision 1.87  2007/01/21 15:43:08  farhi
*       NeXus support. Draft version (functional). To be tuned.
*
*       Revision 1.86  2006/08/28 10:12:25  pchr
*       Basic infrastructure for spin propagation in magnetic fields.
*
*       Revision 1.85  2006/08/15 12:09:35  pkwi
*       Global define GRAVITY=9.81, used in PROP_ routines and Guide_gravity. Will add handeling of
*
*       -g xx / --gravitation==xx
*
*       in mcstas-r.c at a later time.
*
*       Revision 1.84  2006/08/03 13:11:18  pchr
*       Added additional functions for handling vectors.
*
*       Revision 1.83  2006/07/25 08:49:13  pchr
*       Inserted missing end brackets in routines PROP_X0 and PROP_Y0.
*
*       Revision 1.82  2006/07/06 08:59:21  pchr
*       Added new draw methods for rectangle and box.
*
*       Revision 1.81  2006/05/19 14:17:40  farhi
*       Added support for multi threading with --threads=NB option for mcrun or instr.out
*       Requires new option in mcgui run dialog: a popup menu to select run mode ?
*
*       Revision 1.80  2006/04/05 11:45:05  pkwi
*       Need to include <sys/stat.h> on FreeBSD 6.0 / PC-BSD (maybe also other bsd's?!) for prototype declaration of mkdir call...
*
*       Revision 1.79  2006/03/15 16:00:42  farhi
*       minor modifications (position of FLT_MAX in code)
*
*       Revision 1.78  2005/08/31 08:35:53  farhi
*       MCdisplay now prints component name and position when building view (bug/request 44 closed)
*
*       Revision 1.77  2005/08/24 11:55:12  pkwi
*       Usage of mcallowbackprop flag in all PROP routines. Use in component by e.g.
*
*       ALLOWBACKPROP;
*       PROP_Z0;
*
*       Prop routines disallow backpropagation on exit.
*
*       Revision 1.76  2005/08/24 09:51:31  pkwi
*       Beamstop and runtime modified according to Emmanuels remarks.
*
*       To allow backpropagation in a specific component, use
*
*       ALLOW_BACKPROP;
*
*       before calling
*
*       PROP_Z0;
*
*       (One could consider making the backpropagation flag common to all propagation routines, should we do so?)
*
*       Revision 1.75  2005/08/12 11:23:19  pkwi
*       Special Z0 backpropagation macro defined to allow backpropagation without absorbtion. Needed in Beamstop.comp. We foresee usage elsewhere. Problematic: Duplication of code - can we think of a better way to handle this problem?
*
*       Revision 1.74  2005/07/25 14:55:08  farhi
*       DOC update:
*       checked all parameter [unit] + text to be OK
*       set all versions to CVS Revision
*
*       Revision 1.73  2005/07/18 14:43:05  farhi
*       Now gives a warning message per component for 'computational absorbs'
*
*       Revision 1.72  2005/06/20 08:09:07  farhi
*       Changed all ABSORB by adding mcAbsorbProp incrementation
*       in PROP macros
*
*       Revision 1.71  2005/05/29 09:50:32  pkwi
*       t=0 now allowed in PROP_X0, PROP_Y0, PROP_Z0. As far as I can see, there are no other occurancies of this problem in the propagation routines.
*
*       Fixes bug #43 on BugZilla
*
*       Revision 1.70  2005/02/24 15:57:20  farhi
*       FIXED gravity bug (probably OK). Gravity is not handled properly in other Guide elements. Will adapt so that it works better...
*       The n.v was not computed using the actual 'v' values when reaching the guide side, but before propagation. So the velocity was not reflected, but scattered depending on the previous neutron position/velocity, bringing strange divergence effects.
*       On other guide elements, should update the n.v term just before reflection, not computing it before propagation... This probably holds for some other components (monochromators ???) to be checked !
*
*       Revision 1.69  2005/02/23 12:36:53  farhi
*       Added gravitation support in PROP_X0 and PROP_Y0
*
*       Revision 1.66  2005/02/16 12:21:39  farhi
*       Removed left spaces at end of lines
*
*       Revision 1.65  2005/01/26 14:41:16  farhi
*       Updated constant values from CODATA 2002
*
*       Revision 1.64  2005/01/18 10:32:28  farhi
*       Clarify a macro for MPI
*
*       Revision 1.63  2004/11/30 16:14:47  farhi
*       Uses NOSIGNALS and put back PROP_X0 and Y0 for some contrib comps
*
*       Revision 1.62  2004/09/21 12:25:03  farhi
*       Reorganised code so that I/O functions are includable easely (for mcformat.c)
*
*       Revision 1.59  2004/09/03 14:19:14  farhi
*       Correct invertion in mcformat specs structure
*
*       Revision 1.58  2004/07/30 14:49:15  farhi
*       MPI update for usage with mcrun.
*       Still done by Christophe Taton. CC=mpicc and CFLAGS = -DUSE_MPI.
*       Execute (using mpich) with:
*                 mpirun -np NumNodes -machinefile <file> instr.out parameters...
*            where <file> is text file that lists the machines to use
*
*       Revision 1.57  2004/07/16 14:59:03  farhi
*       MPI support. Requires to have mpi installed, and compile with
*          CC=mpicc and CFLAGS = -DUSE_MPI.
*       Work done by Christophe Taton from ENSIMAG/Grenoble
*       Execute (using mpich) with:
*          mpirun -np NumNodes -machinefile <file> instr.out parameters...
*       where <file> is text file that lists the machines to use
*
*       Revision 1.56  2004/06/30 12:11:29  farhi
*       Updated obsolete MCDETECTOR_OUT #define -> mcdetector_out_0d
*
*       Revision 1.55  2003/10/21 14:08:12  pkwi
*       Rectangular focusing improved: Renamed randvec_target_rect to randvec_target_rect_angular. Wrote new randvec_target_rect routine, w/h in metres. Both routines use use component orientation (ROT_A_CURRENT_COMP) as input.
*
*       Modifications to Res_sample and V_sample to match new features of the runtime.
*
*       Revision 1.54  2003/09/05 08:59:18  farhi
*       added INSTRUMENT parameter default value grammar
*       mcinputtable now has also default values
*       mcreadpar now uses default values if parameter not given
*       extended instr_formal parameter struct
*       extended mcinputtable structure type
*
*       Revision 1.53  2003/04/07 11:50:51  farhi
*       Extended the way mcplot:plotter is assigned. Set --portable ok
*       Handle Scilab:Tk and ~GTk menu (shifted)
*       Updated help in mcrun and mcstas-r.c
*
*       Revision 1.52  2003/04/04 18:20:21  farhi
*       remove some warnings (duplicated decl) for --no-runtime on Dec OSF
*
*       Revision 1.51  2003/04/04 14:27:19  farhi
*       Moved format definitions to mcstas-r.c for --no-runtime to work
*
*       Revision 1.50  2003/02/11 12:28:46  farhi
*       Variouxs bug fixes after tests in the lib directory
*       mcstas_r  : disable output with --no-out.. flag. Fix 1D McStas output
*       read_table:corrected MC_SYS_DIR -> MCSTAS define
*       monitor_nd-lib: fix Log(signal) log(coord)
*       HOPG.trm: reduce 4000 points -> 400 which is enough and faster to resample
*       Progress_bar: precent -> percent parameter
*       CS: ----------------------------------------------------------------------
*
* Revision 1.5 2002/10/19 22:46:21 ef
*        gravitation for all with -g. Various output formats.
*
* Revision 1.4 2002/09/17 12:01:21 ef
*       removed unused macros (PROP_Y0, X0), changed randvec_target_sphere to circle
* added randvec_target_rect
*
* Revision 1.3 2002/08/28 11:36:37 ef
*       Changed to lib/share/c code
*
* Revision 1.2 2001/10/10 11:36:37 ef
*       added signal handler
*
* Revision 1.1 1998/08/29 11:36:37 kn
*       Initial revision
*
*******************************************************************************/

#ifndef MCSTAS_R_H
#define MCSTAS_R_H "$Revision: 1.101 $"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <float.h>

/* If the runtime is embedded in the simulation program, some definitions can
   be made static. */

#ifdef MC_EMBEDDED_RUNTIME
#define mcstatic static
#else
#define mcstatic
#endif

#ifdef __dest_os
#if (__dest_os == __mac_os)
#define MAC
#endif
#endif

#ifdef __FreeBSD__
#define NEED_STAT_H
#endif

#if defined(__APPLE__) && defined(__GNUC__)
#define NEED_STAT_H
#endif

#ifdef NEED_STAT_H
#include <sys/stat.h>
#endif

#ifndef MC_PATHSEP_C
#ifdef WIN32
#define MC_PATHSEP_C '\\'
#define MC_PATHSEP_S "\\"
#else  /* !WIN32 */
#ifdef MAC
#define MC_PATHSEP_C ':'
#define MC_PATHSEP_S ":"
#else  /* !MAC */
#define MC_PATHSEP_C '/'
#define MC_PATHSEP_S "/"
#endif /* !MAC */
#endif /* !WIN32 */
#endif /* MC_PATHSEP_C */

#ifndef MCSTAS_VERSION
#define MCSTAS_VERSION "External Run-time"
#endif

#ifdef MC_PORTABLE
#ifndef NOSIGNALS
#define NOSIGNALS
#endif
#endif

#ifdef MAC
#ifndef NOSIGNALS
#define NOSIGNALS
#endif
#endif

#ifdef USE_MPI
#ifndef NOSIGNALS
#define NOSIGNALS
#endif
#endif

#if (USE_NEXUS == 0)
#undef USE_NEXUS
#endif

/* I/O section part ========================================================= */

/* Note: the enum instr_formal_types definition MUST be kept
   synchronized with the one in mcstas.h and with the
   instr_formal_type_names array in cogen.c. */
enum instr_formal_types
  {
    instr_type_double, instr_type_int, instr_type_string
  };
struct mcinputtable_struct {
  char *name; /* name of parameter */
  void *par;  /* pointer to instrument parameter (variable) */
  enum instr_formal_types type;
  char *val;  /* default value */
};

typedef double MCNUM;
typedef struct {MCNUM x, y, z;} Coords;
typedef MCNUM Rotation[3][3];

/* the following variables are defined in the McStas generated C code
   but should be defined externally in case of independent library usage */
#ifndef DANSE
extern struct mcinputtable_struct mcinputtable[];
extern int    mcnumipar;
extern char   mcinstrument_name[], mcinstrument_source[];
extern MCNUM  mccomp_storein[]; /* 11 coords * number of components in instrument */
extern MCNUM  mcAbsorbProp[];
extern MCNUM  mcScattered;
#ifndef MC_ANCIENT_COMPATIBILITY
extern int mctraceenabled, mcdefaultmain;
#endif
#endif

/* file I/O definitions and function prototypes */

struct mcformats_struct {
  char *Name;  /* may also specify: append, partial(hidden), binary */
  char *Extension;
  char *Header;
  char *Footer;
  char *BeginSection;
  char *EndSection;
  char *AssignTag;
  char *BeginData;
  char *EndData;
  char *BeginErrors;
  char *EndErrors;
  char *BeginNcount;
  char *EndNcount;
  };

#ifndef MC_EMBEDDED_RUNTIME /* the mcstatic variables (from mcstas-r.c) */
extern FILE * mcsiminfo_file;
extern int    mcgravitation;
extern int    mcdotrace;
extern struct mcformats_struct mcformats[];
extern struct mcformats_struct mcformat;
extern struct mcformats_struct mcformat_data;
#else
mcstatic FILE *mcsiminfo_file        = NULL;
#endif

/* Useful macros ============================================================ */

#define DETECTOR_OUT(p0,p1,p2) mcdetector_out_0D(NAME_CURRENT_COMP,p0,p1,p2,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_0D(t,p0,p1,p2) mcdetector_out_0D(t,p0,p1,p2,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_1D(t,xl,yl,xvar,x1,x2,n,p0,p1,p2,f) \
     mcdetector_out_1D(t,xl,yl,xvar,x1,x2,n,p0,p1,p2,f,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_2D(t,xl,yl,x1,x2,y1,y2,m,n,p0,p1,p2,f) \
     mcdetector_out_2D(t,xl,yl,x1,x2,y1,y2,m,n,p0,p1,p2,f,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_OUT_3D(t,xl,yl,zl,xv,yv,zv,x1,x2,y1,y2,z1,z2,m,n,p,p0,p1,p2,f) \
     mcdetector_out_3D(t,xl,yl,zl,xv,yv,zv,x1,x2,y1,y2,z1,z2,m,n,p,p0,p1,p2,f,NAME_CURRENT_COMP,POS_A_CURRENT_COMP)
#define DETECTOR_CUSTOM_HEADER(t)  if (t && strlen(t)) { \
     mcDetectorCustomHeader=malloc(strlen(t)); \
     if (mcDetectorCustomHeader) strcpy(mcDetectorCustomHeader, t); }

#define randvec_target_rect(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9)  randvec_target_rect_real(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,0,0,0,1)

/* MPI stuff ================================================================ */

#ifdef USE_MPI
#include "mpi.h"

/*
 * MPI_MASTER(i):
 * execution of i only on master node
 */
#define MPI_MASTER(statement) { \
  if(mpi_node_rank == mpi_node_root)\
  { statement; } \
}

#ifndef MPI_REDUCE_BLOCKSIZE
#define MPI_REDUCE_BLOCKSIZE 10000
#endif

int mc_MPI_Reduce(void* sbuf, void* rbuf,
                  int count, MPI_Datatype dtype,
                  MPI_Op op, int root, MPI_Comm comm);

#define exit(code) MPI_Abort(MPI_COMM_WORLD, code)

#else /* !USE_MPI */
#define MPI_MASTER(instr) instr
#endif /* USE_MPI */

#ifdef USE_MPI
static int mpi_node_count;
#endif

#ifdef USE_THREADS  /* user want threads */
#error Threading (USE_THREADS) support has been removed for very poor efficiency. Use MPI/SSH grid instead.
#endif

/* I/O function prototypes ================================================== */

/* The mcformat.Name may contain additional keywords:
 *  no header: omit the format header
 *  no footer: omit the format footer
 */

void   mcset_ncount(double count);
double mcget_ncount(void);
double mcget_run_num(void);
double mcdetector_out(char *cname, double p0, double p1, double p2, char *filename);
double mcdetector_out_0D(char *t, double p0, double p1, double p2, char *c, Coords pos);
double mcdetector_out_1D(char *t, char *xl, char *yl,
                  char *xvar, double x1, double x2, int n,
                  double *p0, double *p1, double *p2, char *f, char *c, Coords pos);
double mcdetector_out_2D(char *t, char *xl, char *yl,
                  double x1, double x2, double y1, double y2, int m,
                  int n, double *p0, double *p1, double *p2, char *f,
                  char *c, Coords pos);
double mcdetector_out_3D(char *t, char *xl, char *yl, char *zl,
      char *xvar, char *yvar, char *zvar,
                  double x1, double x2, double y1, double y2, double z1, double z2, int m,
                  int n, int p, double *p0, double *p1, double *p2, char *f,
                  char *c, Coords pos);
void   mcinfo_simulation(FILE *f, struct mcformats_struct format,
  char *pre, char *name); /* used to add sim parameters (e.g. in Res_monitor) */
void   mcsiminfo_init(FILE *f);
void   mcsiminfo_close(void);
char *mcfull_file(char *name, char *ext);

#ifndef FLT_MAX
#define FLT_MAX         3.40282347E+38F /* max decimal value of a "float" */
#endif

#ifndef CHAR_BUF_LENGTH
#define CHAR_BUF_LENGTH 1024
#endif

/* Following part is only embedded when not redundent with mcstas.h ========= */

#ifndef MCSTAS_H

#ifndef NOSIGNALS
#include <signal.h>
#define SIG_MESSAGE(msg) strcpy(mcsig_message, msg);
#else
#define SIG_MESSAGE(msg)
#endif /* !NOSIGNALS */



/* Useful macros ============================================================ */

#define RAD2MIN  ((180*60)/PI)
#define MIN2RAD  (PI/(180*60))
#define DEG2RAD  (PI/180)
#define RAD2DEG  (180/PI)
#define AA2MS    629.622368        /* Convert k[1/AA] to v[m/s] */
#define MS2AA    1.58825361e-3     /* Convert v[m/s] to k[1/AA] */
#define K2V      AA2MS
#define V2K      MS2AA
#define Q2V      AA2MS
#define V2Q      MS2AA
#define SE2V     437.393377        /* Convert sqrt(E)[meV] to v[m/s] */
#define VS2E     5.22703725e-6     /* Convert (v[m/s])**2 to E[meV] */
#define FWHM2RMS 0.424660900144    /* Convert between full-width-half-max and */
#define RMS2FWHM 2.35482004503     /* root-mean-square (standard deviation) */
#define HBAR     1.05457168e-34    /* [Js] h bar Planck constant CODATA 2002 */
#define MNEUTRON 1.67492728e-27    /* [kg] mass of neutron CODATA 2002 */
#define GRAVITY  9.81              /* [m/s^2] gravitational acceleration */

#ifndef PI
# ifdef M_PI
#  define PI M_PI
# else
#  define PI 3.14159265358979323846
# endif
#endif

/* mccomp_posa and mccomp_posr are defined in McStas generated C code */
#define POS_A_COMP_INDEX(index) \
    (mccomp_posa[index])
#define POS_R_COMP_INDEX(index) \
    (mccomp_posr[index])
/* mcScattered defined in McStas generated C code */
#define SCATTERED mcScattered

/* Retrieve component information from the kernel */
/* Name, position and orientation (both absolute and relative)  */
/* Any component: For "redundancy", see comment by KN */
#define tmp_name_comp(comp) #comp
#define NAME_COMP(comp) tmp_name_comp(comp)
#define tmp_pos_a_comp(comp) (mcposa ## comp)
#define POS_A_COMP(comp) tmp_pos_a_comp(comp)
#define tmp_pos_r_comp(comp) (mcposr ## comp)
#define POS_R_COMP(comp) tmp_pos_r_comp(comp)
#define tmp_rot_a_comp(comp) (mcrota ## comp)
#define ROT_A_COMP(comp) tmp_rot_a_comp(comp)
#define tmp_rot_r_comp(comp) (mcrotr ## comp)
#define ROT_R_COMP(comp) tmp_rot_r_comp(comp)

/* Current component */
#define NAME_CURRENT_COMP  NAME_COMP(mccompcurname)
#define INDEX_CURRENT_COMP mccompcurindex
#define POS_A_CURRENT_COMP POS_A_COMP(mccompcurname)
#define POS_R_CURRENT_COMP POS_R_COMP(mccompcurname)
#define ROT_A_CURRENT_COMP ROT_A_COMP(mccompcurname)
#define ROT_R_CURRENT_COMP ROT_R_COMP(mccompcurname)



#define SCATTER do {mcDEBUG_SCATTER(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz, \
        mcnlt,mcnlsx,mcnlsy, mcnlp); mcScattered++;} while(0)
#define ABSORB do {mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz, \
        mcnlt,mcnlsx,mcnlsy, mcnlp); mcDEBUG_ABSORB(); MAGNET_OFF; goto mcabsorb;} while(0)
/* Note: The two-stage approach to MC_GETPAR is NOT redundant; without it,
* after #define C sample, MC_GETPAR(C,x) would refer to component C, not to
* component sample. Such are the joys of ANSI C.

* Anyway the usage of MCGETPAR requires that we use sometimes bare names...
*/
#define MC_GETPAR2(comp, par) (mcc ## comp ## _ ## par)
#define MC_GETPAR(comp, par) MC_GETPAR2(comp,par)

#define STORE_NEUTRON(index, x, y, z, vx, vy, vz, t, sx, sy, sz, p) \
  mcstore_neutron(mccomp_storein,index, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
#define RESTORE_NEUTRON(index, x, y, z, vx, vy, vz, t, sx, sy, sz, p) \
  mcrestore_neutron(mccomp_storein,index, &x, &y, &z, &vx, &vy, &vz, &t, &sx, &sy, &sz, &p);

#define MAGNET_ON \
  do { \
    mcMagnet = 1; \
  } while(0)

#define MAGNET_OFF \
  do { \
    mcMagnet = 0; \
  } while(0)

#define ALLOW_BACKPROP \
  do { \
    mcallowbackprop = 1; \
  } while(0)

#define DISALLOW_BACKPROP \
  do { \
    mcallowbackprop = 0; \
  } while(0)

#define PROP_MAGNET(dt) \
  do { \
    /* change coordinates from local system to magnet system */ \
    Rotation rotLM, rotTemp; \
    Coords   posLM = coords_sub(POS_A_CURRENT_COMP, mcMagnetPos); \
    rot_transpose(ROT_A_CURRENT_COMP, rotTemp); \
    rot_mul(rotTemp, mcMagnetRot, rotLM); \
    mcMagnetPrecession(mcnlx, mcnly, mcnlz, mcnlt, mcnlvx, mcnlvy, mcnlvz, \
	   	       &mcnlsx, &mcnlsy, &mcnlsz, dt, posLM, rotLM); \
  } while(0)

#define mcPROP_DT(dt) \
  do { \
    if (mcMagnet && dt > 0) PROP_MAGNET(dt);\
    mcnlx += mcnlvx*(dt); \
    mcnly += mcnlvy*(dt); \
    mcnlz += mcnlvz*(dt); \
    mcnlt += (dt); \
  } while(0)

/* ADD: E. Farhi, Aug 6th, 2001 PROP_GRAV_DT propagation with acceleration */
#define PROP_GRAV_DT(dt, Ax, Ay, Az) \
  do { \
    if(dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }\
    if (mcMagnet) printf("Spin precession gravity\n"); \
    mcnlx  += mcnlvx*(dt) + (Ax)*(dt)*(dt)/2; \
    mcnly  += mcnlvy*(dt) + (Ay)*(dt)*(dt)/2; \
    mcnlz  += mcnlvz*(dt) + (Az)*(dt)*(dt)/2; \
    mcnlvx += (Ax)*(dt); \
    mcnlvy += (Ay)*(dt); \
    mcnlvz += (Az)*(dt); \
    mcnlt  += (dt); \
    DISALLOW_BACKPROP;\
  } while(0)

#define PROP_DT(dt) \
  do { \
    if(dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    if (mcgravitation) { Coords mcLocG; double mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    PROP_GRAV_DT(dt, mc_gx, mc_gy, mc_gz); } \
    else mcPROP_DT(dt); \
    DISALLOW_BACKPROP;\
  } while(0)


#define PROP_Z0 \
  do { \
    if (mcgravitation) { Coords mcLocG; int mc_ret; \
    double mc_dt, mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    mc_ret = solve_2nd_order(&mc_dt, -mc_gz/2, -mcnlvz, -mcnlz); \
    if (mc_ret && mc_dt>=0) PROP_GRAV_DT(mc_dt, mc_gx, mc_gy, mc_gz); \
    else { if (mcallowbackprop ==0) {mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }}; }\
    else mcPROP_Z0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define mcPROP_Z0 \
  do { \
    double mc_dt; \
    if(mcnlvz == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mc_dt = -mcnlz/mcnlvz; \
    if(mc_dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mcPROP_DT(mc_dt); \
    mcnlz = 0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define PROP_X0 \
  do { \
    if (mcgravitation) { Coords mcLocG; int mc_ret; \
    double mc_dt, mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    mc_ret = solve_2nd_order(&mc_dt, -mc_gx/2, -mcnlvx, -mcnlx); \
    if (mc_ret && mc_dt>=0) PROP_GRAV_DT(mc_dt, mc_gx, mc_gy, mc_gz); \
    else { if (mcallowbackprop ==0) {mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }}; }\
    else mcPROP_X0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define mcPROP_X0 \
  do { \
    double mc_dt; \
    if(mcnlvx == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mc_dt = -mcnlx/mcnlvx; \
    if(mc_dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mcPROP_DT(mc_dt); \
    mcnlx = 0; \
    DISALLOW_BACKPROP;\
  } while(0)

#define PROP_Y0 \
  do { \
    if (mcgravitation) { Coords mcLocG; int mc_ret; \
    double mc_dt, mc_gx, mc_gy, mc_gz; \
    mcLocG = rot_apply(ROT_A_CURRENT_COMP, coords_set(0,-GRAVITY,0)); \
    coords_get(mcLocG, &mc_gx, &mc_gy, &mc_gz); \
    mc_ret = solve_2nd_order(&mc_dt, -mc_gy/2, -mcnlvy, -mcnly); \
    if (mc_ret && mc_dt>=0) PROP_GRAV_DT(mc_dt, mc_gx, mc_gy, mc_gz); \
    else { if (mcallowbackprop ==0) {mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }}; }\
    else mcPROP_Y0; \
    DISALLOW_BACKPROP;\
  } while(0)


#define mcPROP_Y0 \
  do { \
    double mc_dt; \
    if(mcnlvy == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mc_dt = -mcnly/mcnlvy; \
    if(mc_dt < 0 && mcallowbackprop == 0) { mcAbsorbProp[INDEX_CURRENT_COMP]++; ABSORB; }; \
    mcPROP_DT(mc_dt); \
    mcnly = 0; \
    DISALLOW_BACKPROP; \
  } while(0)

#define vec_prod(x, y, z, x1, y1, z1, x2, y2, z2) \
  do { \
    double mcvp_tmpx, mcvp_tmpy, mcvp_tmpz; \
    mcvp_tmpx = (y1)*(z2) - (y2)*(z1); \
    mcvp_tmpy = (z1)*(x2) - (z2)*(x1); \
    mcvp_tmpz = (x1)*(y2) - (x2)*(y1); \
    (x) = mcvp_tmpx; (y) = mcvp_tmpy; (z) = mcvp_tmpz; \
  } while(0)

#define scalar_prod(x1, y1, z1, x2, y2, z2) \
  ((x1)*(x2) + (y1)*(y2) + (z1)*(z2))

#define NORM(x,y,z) \
  do { \
    double mcnm_tmp = sqrt((x)*(x) + (y)*(y) + (z)*(z)); \
    if(mcnm_tmp != 0.0) \
    { \
      (x) /= mcnm_tmp; \
      (y) /= mcnm_tmp; \
      (z) /= mcnm_tmp; \
    } \
  } while(0)

#define rotate(x, y, z, vx, vy, vz, phi, ax, ay, az) \
  do { \
    double mcrt_tmpx = (ax), mcrt_tmpy = (ay), mcrt_tmpz = (az); \
    double mcrt_vp, mcrt_vpx, mcrt_vpy, mcrt_vpz; \
    double mcrt_vnx, mcrt_vny, mcrt_vnz, mcrt_vn1x, mcrt_vn1y, mcrt_vn1z; \
    double mcrt_bx, mcrt_by, mcrt_bz; \
    double mcrt_cos, mcrt_sin; \
    NORM(mcrt_tmpx, mcrt_tmpy, mcrt_tmpz); \
    mcrt_vp = scalar_prod((vx), (vy), (vz), mcrt_tmpx, mcrt_tmpy, mcrt_tmpz); \
    mcrt_vpx = mcrt_vp*mcrt_tmpx; \
    mcrt_vpy = mcrt_vp*mcrt_tmpy; \
    mcrt_vpz = mcrt_vp*mcrt_tmpz; \
    mcrt_vnx = (vx) - mcrt_vpx; \
    mcrt_vny = (vy) - mcrt_vpy; \
    mcrt_vnz = (vz) - mcrt_vpz; \
    vec_prod(mcrt_bx, mcrt_by, mcrt_bz, \
             mcrt_tmpx, mcrt_tmpy, mcrt_tmpz, mcrt_vnx, mcrt_vny, mcrt_vnz); \
    mcrt_cos = cos((phi)); mcrt_sin = sin((phi)); \
    mcrt_vn1x = mcrt_vnx*mcrt_cos + mcrt_bx*mcrt_sin; \
    mcrt_vn1y = mcrt_vny*mcrt_cos + mcrt_by*mcrt_sin; \
    mcrt_vn1z = mcrt_vnz*mcrt_cos + mcrt_bz*mcrt_sin; \
    (x) = mcrt_vpx + mcrt_vn1x; \
    (y) = mcrt_vpy + mcrt_vn1y; \
    (z) = mcrt_vpz + mcrt_vn1z; \
  } while(0)

#define mirror(x,y,z,rx,ry,rz,nx,ny,nz) \
  do { \
    double mcrt_tmpx= (nx), mcrt_tmpy = (ny), mcrt_tmpz = (nz); \
    double mcrt_tmpt; \
    NORM(mcrt_tmpx, mcrt_tmpy, mcrt_tmpz); \
    mcrt_tmpt=scalar_prod((rx),(ry),(rz),mcrt_tmpx,mcrt_tmpy,mcrt_tmpz); \
    (x) = rx -2 * mcrt_tmpt*mcrt_rmpx; \
    (y) = ry -2 * mcrt_tmpt*mcrt_rmpy; \
    (z) = rz -2 * mcrt_tmpt*mcrt_rmpz; \
  } while (0)

#ifdef MC_TRACE_ENABLED
#define DEBUG
#endif

#ifdef DEBUG
#define mcDEBUG_INSTR() if(!mcdotrace); else { printf("INSTRUMENT:\n"); printf("Instrument '%s' (%s)\n", mcinstrument_name, mcinstrument_source); }
#define mcDEBUG_COMPONENT(name,c,t) if(!mcdotrace); else {\
  printf("COMPONENT: \"%s\"\n" \
         "POS: %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", \
         name, c.x, c.y, c.z, t[0][0], t[0][1], t[0][2], \
         t[1][0], t[1][1], t[1][2], t[2][0], t[2][1], t[2][2]); \
  printf("Component %30s AT (%g,%g,%g)\n", name, c.x, c.y, c.z); \
  }
#define mcDEBUG_INSTR_END() if(!mcdotrace); else printf("INSTRUMENT END:\n");
#define mcDEBUG_ENTER() if(!mcdotrace); else printf("ENTER:\n");
#define mcDEBUG_COMP(c) if(!mcdotrace); else printf("COMP: \"%s\"\n", c);
#define mcDEBUG_STATE(x,y,z,vx,vy,vz,t,s1,s2,p) if(!mcdotrace); else \
  printf("STATE: %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", \
         x,y,z,vx,vy,vz,t,s1,s2,p);
#define mcDEBUG_SCATTER(x,y,z,vx,vy,vz,t,s1,s2,p) if(!mcdotrace); else \
  printf("SCATTER: %g, %g, %g, %g, %g, %g, %g, %g, %g, %g\n", \
         x,y,z,vx,vy,vz,t,s1,s2,p);
#define mcDEBUG_LEAVE() if(!mcdotrace); else printf("LEAVE:\n");
#define mcDEBUG_ABSORB() if(!mcdotrace); else printf("ABSORB:\n");
#else
#define mcDEBUG_INSTR()
#define mcDEBUG_COMPONENT(name,c,t)
#define mcDEBUG_INSTR_END()
#define mcDEBUG_ENTER()
#define mcDEBUG_COMP(c)
#define mcDEBUG_STATE(x,y,z,vx,vy,vz,t,s1,s2,p)
#define mcDEBUG_SCATTER(x,y,z,vx,vy,vz,t,s1,s2,p)
#define mcDEBUG_LEAVE()
#define mcDEBUG_ABSORB()
#endif

#ifdef TEST
#define test_printf printf
#else
#define test_printf while(0) printf
#endif

#ifndef MC_RAND_ALG
#define MC_RAND_ALG 1
#endif

#if MC_RAND_ALG == 0
   /* Use system random() (not recommended). */
#  define MC_RAND_MAX RAND_MAX
#elif MC_RAND_ALG == 1
   /* "Mersenne Twister", by Makoto Matsumoto and Takuji Nishimura. */
#  define MC_RAND_MAX ((unsigned long)0xffffffff)
#  define random mt_random
#  define srandom mt_srandom
#elif MC_RAND_ALG == 2
   /* Algorithm used in McStas CVS-080208 and earlier (not recommended). */
#  define MC_RAND_MAX 0x7fffffff
#  define random mc_random
#  define srandom mc_srandom
#else
#  error "Bad value for random number generator choice."
#endif

#define rand01() ( ((double)random())/((double)MC_RAND_MAX+1) )
#define randpm1() ( ((double)random()) / (((double)MC_RAND_MAX+1)/2) - 1 )
#define rand0max(max) ( ((double)random()) / (((double)MC_RAND_MAX+1)/(max)) )
#define randminmax(min,max) ( rand0max((max)-(min)) + (min) )

#ifndef DANSE
void mcinit(void);
void mcraytrace(void);
void mcsave(FILE *);
void mcfinally(void);
void mcdisplay(void);
#endif

void mcdis_magnify(char *);
void mcdis_line(double, double, double, double, double, double);
void mcdis_dashed_line(double, double, double, double, double, double, int);
void mcdis_multiline(int, ...);
void mcdis_rectangle(char *, double, double, double, double, double);
void mcdis_box(double, double, double, double, double, double);
void mcdis_circle(char *, double, double, double, double);


typedef int mc_int32_t;
mc_int32_t mc_random(void);
void mc_srandom (unsigned int x);
unsigned long mt_random(void);
void mt_srandom (unsigned long x);

Coords coords_set(MCNUM x, MCNUM y, MCNUM z);
Coords coords_get(Coords a, MCNUM *x, MCNUM *y, MCNUM *z);
Coords coords_add(Coords a, Coords b);
Coords coords_sub(Coords a, Coords b);
Coords coords_neg(Coords a);
Coords coords_scale(Coords b, double scale);
double coords_sp(Coords a, Coords b);
Coords coords_xp(Coords b, Coords c);
void   coords_print(Coords a);

void rot_set_rotation(Rotation t, double phx, double phy, double phz);
int  rot_test_identity(Rotation t);
void rot_mul(Rotation t1, Rotation t2, Rotation t3);
void rot_copy(Rotation dest, Rotation src);
void rot_transpose(Rotation src, Rotation dst);
Coords rot_apply(Rotation t, Coords a);
void mccoordschange(Coords a, Rotation t, double *x, double *y, double *z,
    double *vx, double *vy, double *vz, double *time,
    double *s1, double *s2);
void mccoordschange_polarisation(Rotation t,
    double *sx, double *sy, double *sz);
double mcestimate_error(double N, double p1, double p2);
void mcreadparams(void);

void mcsetstate(double x, double y, double z, double vx, double vy, double vz,
                double t, double sx, double sy, double sz, double p);
void mcgenstate(void);
double randnorm(void);
double randtriangle(void);
void normal_vec(double *nx, double *ny, double *nz,
    double x, double y, double z);
int inside_rectangle(double, double, double, double);
int box_intersect(double *dt_in, double *dt_out, double x, double y, double z,
    double vx, double vy, double vz, double dx, double dy, double dz);
int cylinder_intersect(double *t0, double *t1, double x, double y, double z,
    double vx, double vy, double vz, double r, double h);
int sphere_intersect(double *t0, double *t1, double x, double y, double z,
                 double vx, double vy, double vz, double r);
/* ADD: E. Farhi, Aug 6th, 2001 solve_2nd_order */
int solve_2nd_order(double *Idt,
    double A,  double B,  double C);
void randvec_target_circle(double *xo, double *yo, double *zo,
    double *solid_angle, double xi, double yi, double zi, double radius);
#define randvec_target_sphere randvec_target_circle
#define plane_intersect_Gfast solve_2nd_order
void randvec_target_rect_angular(double *xo, double *yo, double *zo,
    double *solid_angle,
               double xi, double yi, double zi, double height, double width, Rotation A);
void randvec_target_rect_real(double *xo, double *yo, double *zo,
    double *solid_angle,
	       double xi, double yi, double zi, double height, double width, Rotation A,
			 double lx, double ly, double lz, int order);
void extend_list(int count, void **list, int *size, size_t elemsize);

int mcstas_main(int argc, char *argv[]);


#endif /* !MCSTAS_H */

#endif /* MCSTAS_R_H */
/* End of file "mcstas-r.h". */

#line 1007 "SEQ_11_09_2009.c"

#line 1 "nexus-lib.h"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/nexus-lib.h
*
* %Identification
* Written by: EF
* Date:    Jan 17, 2007
* Release: McStas CVS-080208
* Version: $Revision: 1.8 $
*
* NeXus Runtime system header for McStas.
* Overrides default mcstas runtime functions.
* Embedded within instrument in runtime mode.
*
* Usage: Automatically embbeded in the c code whenever required.
*
* $Id: nexus-lib.h,v 1.8 2008/02/09 22:26:27 farhi Exp $
*
* $Log: nexus-lib.h,v $
* Revision 1.8  2008/02/09 22:26:27  farhi
* Major contrib for clusters/multi-core: OpenMP support
* 	try ./configure --with-cc=gcc4.2 or icc
* then mcrun --threads ...
* Also tidy-up configure. Made relevant changes to mcrun/mcgui to enable OpenMP
* Updated install-doc accordingly
*
* Revision 1.7  2007/03/05 19:02:55  farhi
* NEXUS support now works as MPI. NEXUS keyword is optional and only -DUSE_NEXUS is required. All instruments may then export in NEXUS if McStas
* has been installed with --with-nexus
*
* Revision 1.6  2007/03/02 14:35:56  farhi
* Updated install doc for NeXus and reconfigure tool.
* better NeXus support with compression
*
* Revision 1.5  2007/02/09 13:21:38  farhi
* NeXus compression does not work right. Use flat NeXus as default.
*
* Revision 1.4  2007/01/26 16:23:25  farhi
* NeXus final integration (mcplot, mcgui, mcrun).
* Only mcgui initiate mcstas.nxs as default output file, whereas
* simulation may use instr_time.nxs
*
* Revision 1.3  2007/01/22 15:13:42  farhi
* Fully functional NeXus output format.
* Works also for lists, but as catenation is not working in NAPI, one
* has to store all in memory (e.g. with large Monitor_nD bufsize), so that
* its written in one go at the end of sim.
*
* Revision 1.2  2007/01/22 01:38:25  farhi
* Improved NeXus/NXdata support. Attributes may not be at the right place
* yet.
*
* Revision 1.1  2007/01/21 15:43:08  farhi
* NeXus support. Draft version (functional). To be tuned.
*
*
*******************************************************************************/

#ifdef USE_NEXUS

#include "napi.h"
#include <sys/stat.h>

/* NeXus variables to be used in functions */
NXhandle mcnxHandle;
char    *mcnxFilename=NULL;
char     mcnxversion[128];       /* init in cogen_init: 4,5 xml and compress */

/* NeXus output functions that replace calls to pfprintf in mcstas-r */
int mcnxfile_init(char *name, char *ext, char *mode, NXhandle *nxhandle);
int mcnxfile_close(NXhandle *nxHandle);

/* header/footer. f=mcsiminfo_file, datafile */
/* creates Entry=valid_parent+file+timestamp */
int mcnxfile_header(NXhandle nxhandle, char *part,
    char *pre,                  /* %1$s  PRE  */
    char *instrname,            /* %2$s  SRC  */
    char *file,                 /* %3$s  FIL  */
    char *format_name,          /* %4$s  FMT  */
    char *date,                 /* %5$s  DAT  */
    char *user,                 /* %6$s  USR  */
    char *valid_parent,         /* %7$s  PAR = file */
    long  date_l);               /* %8$li DATL */

/* tag=value */
int mcnxfile_tag(NXhandle nxhandle,
    char *pre,          /* %1$s PRE */
    char *valid_section,/* %2$s SEC */
    char *name,         /* %3$s NAM */
    char *value);        /* %4$s VAL */

/* begin/end section */
int mcnxfile_section(NXhandle nxhandle, char *part,
    char *pre,          /* %1$s  PRE  */
    char *type,         /* %2$s  TYP  */
    char *name,         /* %3$s  NAM  */
    char *valid_name,   /* %4$s  VNA  */
    char *parent,       /* %5$s  PAR  */
    char *valid_parent, /* %6$s  VPA  */
    int   level);        /* %7$i  LVL */

/* data block begin/end */
int mcnxfile_datablock(NXhandle nxhandle, char *part,
      char *pre,          /* %1$s   PRE  */
      char *valid_parent, /* %2$s   PAR  */
      char *filename,     /* %3$s   FIL  */
      char *xlabel,       /* %4$s   XLA  */
      char *valid_xlabel, /* %5$s   XVL  */
      char *ylabel,       /* %6$s   YLA  */
      char *valid_ylabel, /* %7$s   YVL  */
      char *zlabel,       /* %8$s   ZLA  */
      char *valid_zlabel, /* %9$s   ZVL  */
      char *title,        /* %10$s  TITL */
      char *xvar,         /* %11$s  XVAR */
      char *yvar,         /* %12$s  YVAR */
      char *zvar,         /* %13$s  ZVAR */
      int  m,            /* %14$i  MDIM */
      int  n,            /* %15$i  NDIM */
      int  p,            /* %16$i  PDIM */
      double x1,           /* %17$g  XMIN */
      double x2,           /* %18$g  XMAX */
      double y1,           /* %19$g  YMIN */
      double y2,           /* %20$g  YMAX */
      double z1,           /* %21$g  ZMIN */
      double z2,           /* %22$g  ZMAX */
      double *p0,
      double *p1,
      double *p2);

#endif
/* End of file "nexus-lib.h". */

#line 1147 "SEQ_11_09_2009.c"

#line 1 "nexus-lib.c"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/nexus-lib.c
*
* %Identification
* Written by: KN
* Date:    Jan 17, 2007
* Release: McStas 1.12a
* Version: $Revision: 1.12 $
*
* NeXus Runtime output functions for McStas.
* Overrides default mcstas runtime functions.
* Embedded within instrument in runtime mode.
*
* Usage: Automatically embbeded in the c code whenever required.
*
* $Id: nexus-lib.c,v 1.12 2008/02/09 22:26:27 farhi Exp $
*
* $Log: nexus-lib.c,v $
* Revision 1.12  2008/02/09 22:26:27  farhi
* Major contrib for clusters/multi-core: OpenMP support
* 	try ./configure --with-cc=gcc4.2 or icc
* then mcrun --threads ...
* Also tidy-up configure. Made relevant changes to mcrun/mcgui to enable OpenMP
* Updated install-doc accordingly
*
* Revision 1.11  2007/03/06 09:39:15  farhi
* NeXus default output is now "5 zip". Then NEXUS keyword is purely optional.
*
* Revision 1.10  2007/03/05 19:02:55  farhi
* NEXUS support now works as MPI. NEXUS keyword is optional and only -DUSE_NEXUS is required. All instruments may then export in NEXUS if McStas
* has been installed with --with-nexus
*
* Revision 1.9  2007/03/02 14:35:56  farhi
* Updated install doc for NeXus and reconfigure tool.
* better NeXus support with compression
*
* Revision 1.8  2007/02/24 16:44:41  farhi
* nexus support adapted partially for SNS. File name can be specified with -f option of instr.exe or mcrun or follow NEXUS keyword. The NULL filename will set 'instr_timestamp'.
*
* Revision 1.7  2007/02/09 13:21:37  farhi
* NeXus compression does not work right. Use flat NeXus as default.
*
* Revision 1.6  2007/01/26 16:23:25  farhi
* NeXus final integration (mcplot, mcgui, mcrun).
* Only mcgui initiate mcstas.nxs as default output file, whereas
* simulation may use instr_time.nxs
*
* Revision 1.5  2007/01/25 14:57:36  farhi
* NeXus output now supports MPI. Each node writes a data set in the NXdata
* group. Uses compression LZW when -DUSE_NEXUS_COMP.
*
* Revision 1.3  2007/01/22 15:13:42  farhi
* Fully functional NeXus output format.
* Works also for lists, but as catenation is not working in NAPI, one
* has to store all in memory (e.g. with large Monitor_nD bufsize), so that
* its written in one go at the end of sim.
*
* Revision 1.2  2007/01/22 01:38:25  farhi
* Improved NeXus/NXdata support. Attributes may not be at the right place
* yet.
*
* Revision 1.1  2007/01/21 15:43:08  farhi
* NeXus support. Draft version (functional). To be tuned.
*
*
*******************************************************************************/

#ifdef USE_NEXUS

/* NeXus output functions that replace calls to pfprintf in mcstas-r */
int mcnxfile_init(char *name, char *ext, char *mode, NXhandle *nxhandle)
{
  int mcnxMode=NXACC_CREATE5;
  char mcnxExt[10];
  strcpy(mcnxExt, ext);
  char nxversion[128];
  int i;
  if (!mcnxversion || !strlen(mcnxversion)) strcpy(nxversion, "5 zip");
  else for (i=0; i< strlen(mcnxversion) && i < 128; nxversion[i]=tolower(mcnxversion[i++]));

  if    (strstr(nxversion,"xml")) { mcnxMode =NXACC_CREATEXML; strcpy(mcnxExt, "xml"); }
  else if (strstr(nxversion,"4")) { mcnxMode =NXACC_CREATE;     }
  else if (strstr(nxversion,"5")) { mcnxMode =NXACC_CREATE5;    }

  if (!strcmp(mode, "a"))    mcnxMode |= NXACC_RDWR;
  mcnxFilename = mcfull_file(name, mcnxExt);
  if (NXopen(mcnxFilename, mcnxMode, nxhandle) == NX_ERROR) {
    mcsiminfo_file = NULL;
  } else { mcsiminfo_file=(FILE*)mcnxFilename; }
  return(mcsiminfo_file != NULL);
}

int mcnxfile_close(NXhandle *nxHandle)
{
  return(NXclose(nxHandle));
}

/* mcnxfile_header: header/footer. f=mcsiminfo_file, datafile */
/* write class attributes in current SDS. Returns: NX_ERROR or NX_OK */
int mcnxfile_header(NXhandle nxhandle, char *part,
    char *pre,                  /* %1$s  PRE  */
    char *instrname,            /* %2$s  SRC  */
    char *file,                 /* %3$s  FIL  */
    char *format_name,          /* %4$s  FMT  */
    char *date,                 /* %5$s  DAT  */
    char *user,                 /* %6$s  USR  */
    char *valid_parent,         /* %7$s  PAR = file */
    long  date_l)               /* %8$li DATL */
{
  if (!strcmp(part, "header")) {
    if (NXputattr(nxhandle, "user_name", user, strlen(user), NX_CHAR) == NX_ERROR)
      return(NX_ERROR);
    char creator[128];
    sprintf(creator, "%s McStas " MCSTAS_VERSION " [www.mcstas.org]", instrname);
    NXputattr(nxhandle, "creator", creator, strlen(creator), NX_CHAR);
    NXputattr(nxhandle, "simulation_begin", date, strlen(date), NX_CHAR);
    char *url="http://www.nexusformat.org/";
    NXputattr(nxhandle, "URL", url, strlen(url), NX_CHAR);
    char *browser="hdfview or NXbrowse or HDFExplorer";
    NXputattr(nxhandle, "Browser", browser, strlen(browser), NX_CHAR);
#if defined (USE_MPI) || defined(USE_THREADS)
    NXputattr (nxhandle, "number_of_nodes", &mpi_node_count, 1, NX_INT32);
#endif
    return(NXputattr(nxhandle, "Format", format_name, strlen(format_name), NX_CHAR));
  } else
    return(NXputattr(nxhandle, "simulation_end", date, strlen(date), NX_CHAR));
} /* mcnxfile_header */

/* mcnxfile_tag: tag=value in the current group. Returns: NX_ERROR or NX_OK */
int mcnxfile_tag(NXhandle nxhandle,
    char *pre,          /* %1$s PRE */
    char *valid_section,/* %2$s SEC */
    char *name,         /* %3$s NAM */
    char *value)        /* %4$s VAL */
{
  return(NXputattr(nxhandle, name, value, strlen(value), NX_CHAR));
} /* mcnxfile_tag */

/* mcnxfile_section: begin/end section. Returns: NX_ERROR or NX_OK */
int mcnxfile_section(NXhandle nxhandle, char *part,
    char *pre,          /* %1$s  PRE  */
    char *type,         /* %2$s  TYP  */
    char *name,         /* %3$s  NAM  */
    char *valid_name,   /* %4$s  VNA  */
    char *parent,       /* %5$s  PAR  */
    char *valid_parent, /* %6$s  VPA  */
    int   level)        /* %7$i  LVL */
{
  char nxname[1024];
  int length;
  if (!strcmp(part, "end_data"))   return(NXclosedata(nxhandle));
  if (!strcmp(part, "end"))        return(NXclosegroup(nxhandle));

  if (!strcmp(type, "instrument")) strcpy(nxname, "instrument");
  else if (!strcmp(type, "simulation")) strcpy(nxname, "simulation");
  else strcpy(nxname, valid_name);
  if (!strcmp(part, "instr_code")) {
    FILE *f;
    char *instr_code=NULL;
    struct stat stfile;
    if (stat(name,&stfile) != 0) {
      instr_code = (char*)malloc(1024);
      if (instr_code) sprintf(instr_code, "File %s not found", name);
    } else {
      long filesize = stfile.st_size;
      f=fopen(name, "r");
      instr_code = (char*)malloc(filesize);
      if (instr_code && f) fread(instr_code, 1, filesize, f);
      if (f) fclose(f);
    }
    length = strlen(instr_code);
    if (length) {
      NXmakedata(nxhandle, "instr_code", NX_CHAR, 1, &length);
        NXopendata(nxhandle, "instr_code");
        NXputdata (nxhandle, instr_code);
        NXputattr (nxhandle, "file_name", name, strlen(name), NX_CHAR);
        NXputattr (nxhandle, "file_size", &length, 1, NX_INT32);
        NXputattr (nxhandle, "McStas_version", MCSTAS_VERSION, strlen(MCSTAS_VERSION), NX_CHAR);
        NXputattr (nxhandle, "instr_name", parent, strlen(parent), NX_CHAR);
      return(NXclosedata(nxhandle));
    } else
    return(NX_ERROR);
  }
  if (!strcmp(part, "begin")) {
    char nxtype[128];
    sprintf(nxtype, "NX%s", type);
    if (NXmakegroup(nxhandle, nxname, nxtype) == NX_ERROR)
      fprintf(stderr, "Warning: could not open SDS to store %s %s information\n",
        nxname, nxtype);
    NXopengroup(nxhandle, nxname, nxtype);
    /* open a SDS to store attributes */
    sprintf(nxname, "Information about %s of type %s is stored in attributes", name, nxtype);
    length = strlen(nxname);
    NXmakedata(nxhandle, "information", NX_CHAR, 1, &length);
    NXopendata(nxhandle, "information");
    NXputdata (nxhandle, nxname);
    NXputattr(nxhandle, "name", name, strlen(name), NX_CHAR);
    NXputattr(nxhandle, "parent", parent, strlen(parent), NX_CHAR);
  }
  return(NX_OK);
} /* mcnxfile_section */

/* mcnxfile_datablock: data block begin/end. Returns: NX_ERROR or NX_OK */
int mcnxfile_datablock(NXhandle nxhandle, char *part,
      char *format, char *valid_parent, char *filename, char *xlabel, char *valid_xlabel, char *ylabel, char *valid_ylabel, char *zlabel, char *valid_zlabel, char *title, char *xvar, char *yvar, char *zvar, int  m, int  n, int  p, double x1, double x2, double y1, double y2, double z1, double z2, double *p0, double *p1, double *p2)
{
  /* write axes, only for data */
  if (strstr(part, "data")) {
    int i;
    if (!strstr(format, "list")) {
    /* X axis */
    if (m > 1) {
      double axis[m];
      for(i = 0; i < m; i++)
        axis[i] = x1+(x2-x1)*(i+0.5)/(abs(m));
      if (strstr(mcnxversion,"compress") || strstr(mcnxversion,"zip"))
        NXcompmakedata(nxhandle, valid_xlabel, NX_FLOAT64, 1, &m, NX_COMP_LZW, &m);
      else
        NXmakedata(nxhandle, valid_xlabel, NX_FLOAT64, 1, &m);

      NXopendata(nxhandle, valid_xlabel);
      NXputdata (nxhandle, axis);
      NXputattr (nxhandle, "long_name", xlabel, strlen(xlabel), NX_CHAR);
      NXputattr (nxhandle, "short_name", xvar, strlen(xvar), NX_CHAR);
      int naxis=1;
      NXputattr (nxhandle, "axis", &naxis, 1, NX_INT32);
      NXputattr (nxhandle, "units", xvar, strlen(xvar), NX_CHAR);
      int nprimary=1;
      NXputattr (nxhandle, "primary", &nprimary, 1, NX_INT32);
      NXclosedata(nxhandle);
    }
    if (n >= 1) {
      double axis[n];
      for(i = 0; i < n; i++)
        axis[i] = y1+(y2-y1)*(i+0.5)/(abs(n));
      if (strstr(mcnxversion,"compress") || strstr(mcnxversion,"zip"))
        NXcompmakedata(nxhandle, valid_ylabel, NX_FLOAT64, 1, &n, NX_COMP_LZW, &n);
      else
        NXmakedata(nxhandle, valid_ylabel, NX_FLOAT64, 1, &n);

      NXopendata(nxhandle, valid_ylabel);
      NXputdata (nxhandle, axis);
      NXputattr (nxhandle, "long_name", ylabel, strlen(ylabel), NX_CHAR);
      NXputattr (nxhandle, "short_name", yvar, strlen(yvar), NX_CHAR);
      int naxis=2;
      NXputattr (nxhandle, "axis", &naxis, 1, NX_INT32);
      NXputattr (nxhandle, "units", yvar, strlen(yvar), NX_CHAR);
      int nprimary=1;
      NXputattr (nxhandle, "primary", &nprimary, 1, NX_INT32);
      NXclosedata(nxhandle);
    }
    if (p > 1) {
      double axis[p];
      for(i = 0; i < p; i++)
        axis[i] = z1+(z2-z1)*(i+0.5)/(abs(p));
      if (strstr(mcnxversion,"compress") || strstr(mcnxversion,"zip"))
        NXcompmakedata(nxhandle, valid_zlabel, NX_FLOAT64, 1, &p, NX_COMP_LZW, &p);
      else
        NXmakedata(nxhandle, valid_zlabel, NX_FLOAT64, 1, &p);

      NXopendata(nxhandle, valid_zlabel);
      NXputdata (nxhandle, axis);
      NXputattr (nxhandle, "long_name", zlabel, strlen(zlabel), NX_CHAR);
      NXputattr (nxhandle, "short_name", zvar, strlen(zvar), NX_CHAR);
      int naxis=3;
      NXputattr (nxhandle, "axis", &naxis, 1, NX_INT32);
       NXputattr (nxhandle, "units", zvar, strlen(zvar), NX_CHAR);
      int nprimary=1;
      NXputattr (nxhandle, "primary", &nprimary, 1, NX_INT32);
      NXclosedata(nxhandle);
    }
  } } /* end format != list for data */
  /* write data */
  int rank=0;
  int dims[3];  /* number of elements to write */
  if (m > 1) { rank++; dims[0]=m; }
  if (n > 1) { rank++; dims[1]=n; }
  if (p > 1) { rank++; dims[2]=p; }
  char *nxname=part;
  double *data;
  if (strstr(part,"data"))         { data=p1; }
  else if (strstr(part,"errors"))  { data=p2; }
  else if (strstr(part,"ncount"))  { data=p0; }
  /* ignore errors for making/opening data (in case this has already been done */
  if (strstr(mcnxversion,"compress") || strstr(mcnxversion,"zip"))
    NXmakedata(nxhandle, nxname, NX_FLOAT64, rank, dims);
  else
    NXcompmakedata(nxhandle, nxname, NX_FLOAT64, rank, dims, NX_COMP_LZW, dims);

  NXopendata(nxhandle, nxname);
  int israw=(strstr(format, " raw") != NULL);
  if (data == p2 && !israw) {
    double* s = (double*)malloc(abs(m*n*p)*sizeof(double));
    if (s) {
      long    i;
      for (i=0; i<abs(m*n*p); i++)
        s[i] = mcestimate_error(p0[i],p1[i],p2[i]);
      NXputdata (nxhandle, s);
      free(s);
    } else {
      fprintf(stderr, "McStas: Out of memory for writing 'errors' in NeXus file '%s'. Writing 'raw' errors (mcnxfile_datablock)\n", filename);
      NXputdata (nxhandle, data);
      char *msg="yes: 'errors' is p^2, not sigma.";
      NXputattr(nxhandle, "raw", msg, strlen(msg), NX_CHAR);
    }
  } else
    NXputdata (nxhandle, data);
  NXputattr(nxhandle, "parent", valid_parent, strlen(valid_parent), NX_CHAR);
  int signal=1;
  if (strstr(part,"data")) {
    NXputattr(nxhandle, "signal", &signal, 1, NX_INT32);
    NXputattr(nxhandle, "short_name", filename, strlen(filename), NX_CHAR);
  }
  char nxtitle[1024];
  sprintf(nxtitle, "%s '%s'", nxname, title);
  NXputattr(nxhandle, "long_name", nxtitle, strlen(nxtitle), NX_CHAR);
  /* first write attributes */
  char creator[128];
  sprintf(creator, "%s/%s", mcinstrument_name, valid_parent);
  NXputattr(nxhandle, "creator", creator, strlen(creator), NX_CHAR);
  return(NXclosedata(nxhandle));
} /* mcnxfile_datablock */

#endif
/* End of file "nexus-lib.c". */

#line 1482 "SEQ_11_09_2009.c"

#line 1 "mcstas-r.c"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2008, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Runtime: share/mcstas-r.c
*
* %Identification
* Written by: KN
* Date:    Aug 29, 1997
* Release: McStas X.Y
* Version: $Revision: 1.194 $
*
* Runtime system for McStas.
* Embedded within instrument in runtime mode.
*
* Usage: Automatically embbeded in the c code whenever required.
*
* $Id: mcstas-r.c,v 1.194 2009-04-02 09:47:46 pkwi Exp $
*
* $Log: mcstas-r.c,v $
* Revision 1.194  2009-04-02 09:47:46  pkwi
* Updated runtime and interoff from dev branch (bugfixes etc.)
*
* Proceeding to test before release
*
* Revision 1.217  2009/03/26 13:41:36  erkn
* fixed bug in mcestimate_error. Missing factor 1/N in quadratic (1st) term of square sum.
*
* Revision 1.216  2009/02/20 16:17:55  farhi
* Fixed warnings and a few bugs detected with GCC 4.3.
*
* Revision 1.215  2009/02/13 14:03:20  farhi
* Fixed GCC 4.3 warnings. More will come in components.
*
* Revision 1.214  2009/02/12 10:43:48  erkn
* check abs. value to protect for rounding errors - not signed value.
*
* Revision 1.213  2009/02/11 15:11:05  farhi
* printf format fixes revealed with gcc 4.3
*
* Revision 1.212  2009/01/23 10:51:30  farhi
* Minor speedup: Identity rotation matrices are now checked for and
* caculations reduced.
* It seems this McSatsStable commit did not got through for McStas 2.0
*
* Revision 1.211  2009/01/18 14:43:13  farhi
* Fixed MPI event list output (broken and reported first by A. Percival).
* This required to split lists in small blocks not to overflow the MPI
* buffer.
*
* Revision 1.207  2008/10/21 15:19:18  farhi
* use common CHAR_BUFFER_LENGTH = 1024
*
* Revision 1.206  2008/10/14 14:29:50  farhi
* sans sample expanded with cylinder and sphere. cosmetics and updated
* todo.
*
* Revision 1.205  2008/10/09 14:47:53  farhi
* cosmetics for SIGNAL displaying starting date
*
* Revision 1.204  2008/09/08 10:08:21  farhi
* in save sessions, filename was not registered in mcopenedfiles,
* but was searching for simfile (always opened) leading
* to always catenated files. This happen when e.g. sending USR2 or using
* intermediate saves.
*
* Revision 1.203  2008/09/05 10:04:20  farhi
* sorry, my mistake...
*
* Revision 1.202  2008/09/02 14:50:42  farhi
* cosmetics
*
* Revision 1.201  2008/09/02 08:36:17  farhi
* MPI support: block size defined in mcstas-r.h as 1e5. Correct bug when
* p0, p1 or p2 are NULL, and re-enable S(q,w) save in Isotropic_Sqw with
* MPI.
*
* Revision 1.200  2008/08/29 15:35:08  farhi
* Split MPI_Reduce into 1e5 bits to avoid de-sync of nodes.. This was done
* in fact in last commit.
*
* Revision 1.199  2008/08/29 15:32:28  farhi
* Indicate memory allocation size when reporting error.
*
* Revision 1.198  2008/08/26 13:32:05  farhi
* Remove Threading support which is poor efficiency and may give wrong
* results
* Add quotes around string instrument parameters from mcgui simulation
* dialog
*
* Revision 1.197  2008/08/25 14:13:28  farhi
* changed neutron-mc to mcstas-users
*
* Revision 1.196  2008/08/19 11:25:52  farhi
* make sure the opened file list is reset when calling mcsave (same save
* session). already opened files are catenated, just as with the catenate
* word in mcformat.Name
*
* Revision 1.195  2008/08/07 21:52:10  farhi
* Second major commit for v2: fixed sources, and most instruments for
* automatic testing. A few instruments need more work still.
*
* Revision 1.194  2008/07/17 12:50:18  farhi
* MAJOR commit to McStas 2.x
* uniformized parameter naming in components
* uniformized SITE for instruments
* all compile OK
*
* Revision 1.192  2008/04/25 08:26:33  erkn
* added utility functions/macros for intersecting with a plane and mirroring a vector in a plane
*
* Revision 1.191  2008/04/21 16:08:05  pkwi
* OpenMPI mpicc dislikes declaration of the counter var in the for(   ) (C99 extension)
*
* Revision 1.190  2008/04/21 15:50:19  pkwi
* Name change randvec_target_rect -> randvec_target_rect_real .
*
* The renamed routine takes local emmission coordinate into account, correcting for the
* effects mentioned by George Apostolopoulus <gapost@ipta.demokritos.gr> to the
* mcstas-users list (parameter list extended by four parms).
*
* For backward-compatibility, a define has been added that maps randvec_target_rect
* to the new routine, defaulting to the "old" behaviour.
*
* To make any use of these modifications, we need to correct all (or all relevant) comps
* that have calls to randvec_target_rect.
*
* Will supply a small doc with plots showing that we now correct for the effect pointed
* out by George.
*
* Similar change should in principle happen to the _sphere focusing routine.
*
* Revision 1.189  2008/04/02 13:20:20  pkwi
* Minor correction: && -> || , otherwise we still stop at the cmdline/default ncount...
*
* Revision 1.188  2008/04/02 12:32:38  farhi
* Add explicit condition for node raytrace loop end with ncount value,
* instead of using local copy of ncount. Makes mcset_ncount work again...
*
* Revision 1.187  2008/03/27 12:47:26  farhi
* Fixed unwanted additional NL chars when using mcformat on PGPLOT 1D
*
* Revision 1.186  2008/03/25 14:34:49  pkwi
* Restoring Revision 1.184 since last commit breaks mcplot 1-D plots.
*
* (Emmanuel will fix 'locally' for mcformat)
*
* Revision 1.184  2008/03/11 16:13:08  farhi
* Infrastructure for running mcrun/mcgui on a grid. --force-compile spans
* over nodes. Local data files are sent to slaves for proper execution of
* complex components.
*
* Revision 1.183  2008/02/14 08:56:35  farhi
* McRun/McGUI SSH grid now operates on each simulation. This emulates completely
* MPI without installing it. Simulation steps for scans may also be distributed,
* and single runs can be sent to execute on other machines transparently.
* mcrun code has reduced in size. mcformat is used to merge nodes.
*
* Revision 1.182  2008/02/10 20:55:53  farhi
* OpenMP number of nodes now set properly from either --threads=NB or
* --threads which sets the computer core nb.
*
* Revision 1.180  2008/02/09 22:26:27  farhi
* Major contrib for clusters/multi-core: OpenMP support
* 	try ./configure --with-cc=gcc4.2 or icc
* then mcrun --threads ...
* Also tidy-up configure. Made relevant changes to mcrun/mcgui to enable OpenMP
* Updated install-doc accordingly
*
* Revision 1.179  2008/01/18 15:39:08  farhi
* mcformat merge mode now takes into account individual Ncount so that addition
* is a weighted sum. Event lists (when 'list' is found in Format) are catenated
* un-weighted.
* Option --format_data aliased to --format-data (internal usage)
*
* Revision 1.178  2007/12/12 08:48:58  pkwi
* Fix for wrong ncount in monitor 'ratios' in case of MPI
*
* Revision 1.177  2007/11/21 09:16:55  farhi
* Added MPI_Barrier to easy synchronization of nodes before Reduce (hey Dude !)
* (Windows) Fixed mcformat catenation of path containing disk label.
*
* Revision 1.176  2007/11/20 20:48:44  pkwi
* Fixes for MPI and input from virtual sources.
*
* When using a virtual source (with N neutron rays), the ncount is now
* restricted to exactly
*
* Ncnt = N * ceil(k/m)
*
* where k is a requested number of repetitions and m is the number of mpi hosts.
*
* Revision 1.175  2007/11/20 14:58:23  farhi
* Fixed change of ncount when using MPI (e.g. Virtual sources)
*
* Revision 1.174  2007/10/18 10:01:22  farhi
* mcdetector_out: fflush(NULL) to flush all opened streams, not only for MPI.
*
* Revision 1.173  2007/10/17 13:05:04  farhi
* MPI run: solve output scrambling when using MPI: force fflush when saving.
*
* Revision 1.172  2007/10/02 09:59:00  farhi
* Fixed exit call for instr --help and --info with or without MPI.
*
* Revision 1.171  2007/09/14 14:46:48  farhi
* mcstas-r: instr.out with MPI may now exit without error code in case of 'usage' and 'info'.
*
* Revision 1.170  2007/08/10 11:30:44  pkwi
* Compilation of mcformat warned about missing newline at end of mcstas-r.c. Added.
*
* Revision 1.169  2007/08/09 16:47:34  farhi
* Solved old gcc compilation issue when using macros in macros.
* Solved MPI issuie when exiting in the middle of a simulation. Now use MPI_Abort.
*
* Revision 1.168  2007/06/30 10:05:11  farhi
* Focus: new TOF-angle detector, so tht it looks like real data
* mcstas-r.c: fixed 2D monitor calls that are in fact 1D.
* Plus cosmetics
*
* Revision 1.167  2007/06/13 08:46:08  pkwi
* A couple of bugfixes...
*
* Virtual_input got the n+1'th weight for the n'th neutron.
*
* mcstas-r.c base adress for store/restore pointers fixed.
*
* These bugs had effect on use of virtual sources plus the new SPLIT keyword...
*
* Will double-check if this is a problem with current stable relase 1.10 and
* report to mcstas-users.
*
* Thanks to Kim Lefmann / Linda Udby for noticing a subtile energy-widening
* effect when using a virtual source!
*
* Revision 1.166  2007/06/11 09:05:33  pkwi
* We need to also check on filename_orig here, otherwise free() is run on a descriptive string in case of Monitor.comp.
*
* Revision 1.165  2007/06/06 12:30:07  pkwi
* Re-introducing --help item for MPI enabled instruments. Was removed on last cvs commit... Please remember to cvs update before committing.
*
* Revision 1.164  2007/05/29 14:57:56  farhi
* New rand function to shoot on a triangular distribution. Useful to simulate chopper time spread.
*
* Revision 1.162  2007/05/18 13:34:54  farhi
* mcformat: warning when using --scan to non McStas/PGPLOT format
* new instrument with sample container and single environment sheild
* removed OpenGENIE format (never used)
*
* Revision 1.161  2007/05/11 10:17:27  farhi
* fix field naming when generating/converting data files.
*
* Revision 1.160  2007/04/20 12:25:25  farhi
* Field names should not exceed e.g. 32 (for Matlab/scilab, etc compatibility).
* Now using VALID_NAME_LENGTH define.
*
* Revision 1.159  2007/04/03 13:29:49  farhi
* store/restore neutron now uses incremented pointer.
* Might improve slightly performances
*
* Revision 1.158  2007/03/12 14:06:35  farhi
* Warning 'Low Stat' when >25 % error in detector results
*
* Revision 1.157  2007/03/05 19:02:55  farhi
* NEXUS support now works as MPI. NEXUS keyword is optional and only -DUSE_NEXUS is required. All instruments may then export in NEXUS if McStas
* has been installed with --with-nexus
*
* Revision 1.156  2007/02/24 16:44:41  farhi
* nexus support adapted partially for SNS. File name can be specified with -f option of instr.exe or mcrun or follow NEXUS keyword. The NULL filename will set 'instr_timestamp'.
*
* Revision 1.155  2007/02/17 13:37:50  farhi
* cogen: display tip when no NEXUS keyword but user wants NeXus output.
* mcstas-r.c: fixed pb when using MPI, that gave 0 detector values.
*
* Revision 1.154  2007/02/06 14:07:40  vel
* Axes limits for 3rd axis using  DETECTOR_OUT_3D are corrected
*
* Revision 1.153  2007/02/05 10:16:08  pkwi
* Mac OS, MPI related: Disable use of sighandler in case of NOSIGNALS
*
* Revision 1.152  2007/01/29 15:51:56  farhi
* mcstas-r: avoid undef of USE_NEXUS as napi is importer afterwards
*
* Revision 1.151  2007/01/29 15:16:07  farhi
* Output file customization in header, through the DETECTOR_CUSTOM_HEADER macro.
* Small adds-on in install doc.
*
* Revision 1.150  2007/01/26 16:23:25  farhi
* NeXus final integration (mcplot, mcgui, mcrun).
* Only mcgui initiate mcstas.nxs as default output file, whereas
* simulation may use instr_time.nxs
*
* Revision 1.149  2007/01/25 14:57:36  farhi
* NeXus output now supports MPI. Each node writes a data set in the NXdata
* group. Uses compression LZW (may be unactivated with the
* -DUSE_NEXUS_FLAT).
*
* Revision 1.148  2007/01/23 00:41:05  pkwi
* Edits by Jiao Lin (linjao@caltech.edu) for embedding McStas in the DANSE project. Define -DDANSE during compile will enable these edits.
*
* Have tested that McStas works properly without the -DDANSE.
*
* Jiao: Could you please test if all is now OK?
* (After 15 minutes) Get current CVS tarball from http://www.mcstas.org/cvs
*
* Revision 1.147  2007/01/22 18:22:43  farhi
* NeXus support for lists and Virtual_output

* Revision 1.146  2007/01/22 15:13:42  farhi
* Fully functional NeXus output format.
* Works also for lists, but as catenation is not working in NAPI, one
* has to store all in memory (e.g. with large Monitor_nD bufsize), so that
* its written in one go at the end of sim.
*
* Revision 1.145  2007/01/22 01:38:25  farhi
* Improved NeXus/NXdata support. Attributes may not be at the right place
* yet.
*
* Revision 1.144  2007/01/21 15:43:08  farhi
* NeXus support. Draft version (functional). To be tuned.
*
* Revision 1.143  2006/12/19 18:51:52  farhi
* Trace disables MPI and Threads only in multicpu mode...
*
* Revision 1.142  2006/12/19 15:11:57  farhi
* Restored basic threading support without mutexes. All is now in mcstas-r.c
*
* Revision 1.141  2006/10/12 12:09:11  farhi
* mcformat can now handle scans, but only works with PGPLOT output format now.
* Input format is any, compatible with --merge as well.
*
* Revision 1.140  2006/10/09 11:31:35  farhi
* Added blue/white sky to VRML output files. Prefer Octagaplayer.
*
* Revision 1.139  2006/10/03 22:14:24  farhi
* Added octaga VRML player in install
*
* Revision 1.138  2006/09/05 15:26:18  farhi
* Update of mcformat
*
* Revision 1.137  2006/08/30 12:13:41  farhi
* Define mutexes for mcstas-r parts.
*
* Revision 1.136  2006/08/28 10:12:25  pchr
* Basic infrastructure for spin propagation in magnetic fields.
*
* Revision 1.135  2006/08/03 13:11:18  pchr
* Added additional functions for handling vectors.
*
* Revision 1.134  2006/07/11 12:21:17  pchr
* Changed polarization default value to be (0, 0, 0) (old was: sy=1)
*
* Revision 1.133  2006/07/06 08:59:21  pchr
* Added new draw methods for rectangle and box.
*
* Revision 1.132  2006/06/01 09:12:45  farhi
* Correct bug related to event for run_num > ncount
* Now forces simulation to finish both in Virtual_input and mcraytrace()
*
* Revision 1.131  2006/05/29 11:51:02  farhi
* Fixed thread joining that caused SEGV when using many threads
*
* Revision 1.130  2006/05/19 19:01:15  farhi
* rum_num now regularly incremented and display warning when pthread requested but not compiled
*
* Revision 1.129  2006/05/19 14:17:40  farhi
* Added support for multi threading with --threads=NB option for mcrun or instr.out
* Requires new option in mcgui run dialog: a popup menu to select run mode ?
*
* Revision 1.128  2006/03/22 14:54:13  farhi
* Added EOL chars (\n) for all matrix output to all formats except IDL
* (which has limitations in the way matrix are entered).
* Will generate data sets to be handled by mcformat/mcconvert
*
* Revision 1.127  2006/03/15 15:59:37  farhi
* output format function more robust (uses default args if called with NULL args)
*
* Revision 1.126  2006/03/02 12:39:33  pkwi
* Corrected typo in last commit:
*
* tout should have been t_out - resulted in:
*
* lp-07151:~> mcrun -c vanadium_example.instr
* Translating instrument definition 'vanadium_example.instr' into C ...
* mcstas -t -o vanadium_example.c vanadium_example.instr
* Warning: 'Source_flat' is an obsolete component (not maintained).
* Compiling C source 'vanadium_example.c' ...
* gcc -g -O2 -o vanadium_example.out vanadium_example.c -lm
* mcstas-r.c: In function `cylinder_intersect':
* mcstas-r.c:3713: error: `tout' undeclared (first use in this function)
* mcstas-r.c:3713: error: (Each undeclared identifier is reported only once
* mcstas-r.c:3713: error: for each function it appears in.)
* ** Error exit **
* lp-07151:~>
*
* Please make simple tests of compilation etc. before committing...
*
* Revision 1.125  2006/03/01 16:06:25  farhi
* Fixed error in cylinder_intersect when trajectory is parallel to the cylinder axis (raised by T. Vanvuure).
*
* Revision 1.124  2005/12/12 13:43:14  farhi
* remove gridding on Matlab in-line plots
*
* Revision 1.123  2005/11/08 14:20:33  farhi
* misprint
*
* Revision 1.122  2005/11/08 13:37:49  farhi
* Warnings for formats are now easier to read
*
* Revision 1.121  2005/09/16 08:43:19  farhi
* Removed floor+0.5 in Monitor_nD
* Take care of ploting with bin centers in mcplot stuff (inline+matlab+scilab+octave...)
*
* Revision 1.120  2005/08/24 09:51:31  pkwi
* Beamstop and runtime modified according to Emmanuels remarks.
*
* To allow backpropagation in a specific component, use
*
* ALLOW_BACKPROP;
*
* before calling
*
* PROP_Z0;
*
* (One could consider making the backpropagation flag common to all propagation routines, should we do so?)
*
* Revision 1.119  2005/07/25 14:55:08  farhi
* DOC update:
* checked all parameter [unit] + text to be OK
* set all versions to CVS Revision
*
* Revision 1.118  2005/07/21 10:19:24  farhi
* Corrected big bug in randvec_*_rect routines when shooting 4PI
* (when one of the params is 0)
* 'circle' routine was OK.
*
* Revision 1.117  2005/07/05 12:04:22  farhi
* Solve bug with default values and non optional parameters
*
* Revision 1.116  2005/07/04 09:06:42  farhi
* test for scilab not bianry and large matrix -> warning more often...
*
* Revision 1.115  2005/06/29 15:08:49  lieutenant
* x values centred (for 1-dim PGPLOT plots) Bug 39
*
* Revision 1.114  2005/06/22 08:56:23  farhi
* Adding 'b' flag to fopen (new files) for binary support on Win32
*
* Revision 1.113  2005/06/20 08:04:18  farhi
* More cautious message for Low Stat
* Add rounding error check in coords_sub
*
* Revision 1.112  2005/05/07 14:29:01  lieutenant
* function coords_add: z=0 if abs(z)<1e-14 to prevent loss of neutrons by numerical rounding errors
*
* Revision 1.111  2005/03/30 21:37:21  farhi
* Corrected gravity bug at last after left test modification (A was replaced by 0 for comp testing, and not put back). Thanks Klaus ! Small time values replaced by 0 in 2nd order solve (Klaus).
*
* Revision 1.110  2005/03/23 14:41:11  farhi
* Added test not to overwrite/delete a temp file by itself
*
* Revision 1.109  2005/03/02 10:40:27  farhi
* Now displays warning for Low Statistics and large matrices in text mode for Matlab/Scilab
*
* Revision 1.108  2005/02/24 15:57:20  farhi
* FIXED gravity bug (probably OK). Gravity is not handled properly in other Guide elements. Will adapt so that it works better...
* The n.v was not computed using the actual 'v' values when reaching the guide side, but before propagation. So the velocity was not reflected, but scattered depending on the previous neutron position/velocity, bringing strange divergence effects.
* On other guide elements, should update the n.v term just before reflection, not computing it before propagation... This probably holds for some other components (monochromators ???) to be checked !
*
* Revision 1.107  2005/02/23 12:29:55  farhi
* FIXED GRAVITATION BUG: was in the choice of the intersection time (2nd order
* equation result) of trajectory with plane
*
* Revision 1.105  2005/02/17 15:54:56  farhi
* Added 'per bin' in labels if more that 1 bin. Requested by R. Cubitt
*
* Revision 1.104  2005/02/16 12:20:36  farhi
* Removed left space chars at end of lines
*
* Revision 1.103  2004/11/30 16:13:22  farhi
* Put back PROP_X0 and Y0 that are used in some contrib components
* Uses NOSIGNALS and set signal handling from that
*
* Revision 1.102  2004/11/29 14:29:02  farhi
* Show title as filename in 'Detector: ... "filename"' line if no file name given
*
* Revision 1.101  2004/11/16 13:35:47  farhi
* Correct HTML -> VRML data format pre selection. May be overridden when using the --format_data option (currently undocumented)
*
* Revision 1.100  2004/09/30 08:23:41  farhi
* Correct pointer mismatch in 'xlimits' for PGPLOT data files
*
* Revision 1.99  2004/09/21 12:25:02  farhi
* Reorganised code so that I/O functions are includable easely (for mcformat.c)
*
* Revision 1.97  2004/09/09 13:46:52  farhi
* Code clean-up
*
* Revision 1.96  2004/09/07 12:28:21  farhi
* Correct allocation bug SEGV in multi-format handling
*
* Revision 1.95  2004/09/03 13:51:07  farhi
* add extension automatically in data/sim files
* may use a format for sim files, and an oher for data, e.g. HTML/VRML.
* added --data_format option to handle 2nd file format.
*
* Revision 1.94  2004/09/01 14:03:41  farhi
* 1 new VRML format for single data files. requires more work for the 'sim' file
* 2 add more info in output file name headers about how to view data
* 3 re-arranged format structure fields in more logical way
* 4 checked all formats for valid export
* 5 compute and update y/z min/max for correct values in data block of files
* 6 correct bug in dynamic format fields alloction when replacing aliases
* 7 adding more field aliases
* 8 use more dynamic allocations to avoid local const variables
*
* Revision 1.93  2004/08/25 09:45:41  farhi
* Main change in the format definition specifications. Aliases are now available to ease maintenance and writing of new formats, e.g. %FIL instead of %2$s !!
*
* Revision 1.92  2004/08/04 10:38:08  farhi
* Added 'raw' data set support (N,p,sigma) -> (N,p,p2) in data files, so that this is additive (for better grid support)
*
* Revision 1.91  2004/07/30 14:49:15  farhi
* MPI update for usage with mcrun.
* Still done by Christophe Taton. CC=mpicc and CFLAGS = -DUSE_MPI.
* Execute (using mpich) with:
*           mpirun -np NumNodes -machinefile <file> instr.out parameters...
*      where <file> is text file that lists the machines to use
*
* Revision 1.90  2004/07/16 14:59:03  farhi
* MPI support. Requires to have mpi installed, and compile with
*    CC=mpicc and CFLAGS = -DUSE_MPI.
* Work done by Christophe Taton from ENSIMAG/Grenoble
* Execute (using mpich) with:
*    mpirun -np NumNodes -machinefile <file> instr.out parameters...
* where <file> is text file that lists the machines to use
*
* Revision 1.88  2004/06/30 15:06:06  farhi
* Solved 'pre' SEGV occuring when indenting/unindenting a Parameter block
* in a data file. Removed Date field in mcinfo_simulation, as this is now included
* in all data files.
*
* Revision 1.86  2004/06/16 14:03:07  farhi
* Corrected misprint
*
* Revision 1.85  2004/03/05 17:43:47  farhi
* Default instr parameters are now correctly handled in all instrument usage cases.
*
* Revision 1.84  2004/03/03 13:41:23  pkwi
* Corrected error in relation to instrument default values: 0's were used in all cases.
*
* Revision 1.83  2004/02/26 12:53:27  farhi
* Scilab format now enables more than one monitor file for a single component
* (e.g. Monitor_nD with multiple detectors).
*
* Revision 1.82  2004/02/23 12:48:42  farhi
* Additional check for default value and unset parameters
*
* Revision 1.81  2004/02/19 14:42:52  farhi
* Experimental Octave/OpenGENIE output format (for ISIS)
*
* Revision 1.80  2004/01/23 16:14:12  pkwi
* Updated version of Mersenne Twister algorithm. make test'ed ok on my machine.
*
* Revision 1.79  2003/11/28 18:08:32  farhi
* Corrected error for IDL import
*
* Revision 1.77  2003/10/22 15:51:26  farhi
* <instr> -i also displays default parameter values (if any), which may be
* read by mcgui for init of Run Simulation dialog
*
* Revision 1.76  2003/10/22 09:18:00  farhi
* Solved name conflict problem for Matlab/Scilab by adding 'mc_' prefix
* to all component/file field names. Works ok for both, and also in binary.
*
* Revision 1.75  2003/10/21 14:08:12  pkwi
* Rectangular focusing improved: Renamed randvec_target_rect to randvec_target_rect_angular. Wrote new randvec_target_rect routine, w/h in metres. Both routines use use component orientation (ROT_A_CURRENT_COMP) as input.
*
* Modifications to Res_sample and V_sample to match new features of the runtime.
*
* Revision 1.74  2003/10/21 11:54:48  farhi
* instrument default parameter value handling now works better
* either from args or from mcreadparam (prompt)
*
* Revision 1.73  2003/09/05 08:59:17  farhi
* added INSTRUMENT parameter default value grammar
* mcinputtable now has also default values
* mcreadpar now uses default values if parameter not given
* extended instr_formal parameter struct
* extended mcinputtable structure type
*
* Revision 1.72  2003/08/26 12:32:43  farhi
* Corrected 4PI random vector generation to retain initial vector length
*
* Revision 1.71  2003/08/20 09:25:00  farhi
* Add the instrument Source tag in scan files (origin of data !)
*
* Revision 1.70  2003/08/12 13:35:52  farhi
* displays known signals list in instrument help (-h)
*
* Revision 1.68  2003/06/17 14:21:54  farhi
* removed 'clear %4$s' in Scilab/Matlab 'end of section' format which
* caused pb when comp_name == file_name
*
* Revision 1.67  2003/06/12 10:22:00  farhi
* -i show info as McStas format, --info use MCSTAS_FORMAT or --format setting
*
* Revision 1.66  2003/06/10 11:29:58  pkwi
* Corrected multiple parse errors: Added two missing sets of curly brackets { } in parameter parsing function.
*
* Revision 1.65  2003/06/05 09:25:59  farhi
* restore header support in data files when --format option found
*
* Revision 1.64  2003/05/26 10:21:00  farhi
* Correct core dump for instrument STRING parameters in 'string printer'
*
* Revision 1.63  2003/05/20 11:54:38  farhi
* make sighandler not restart SAVE when already saving (USR2)
*
* Revision 1.62  2003/05/16 12:13:03  farhi
* added path rehash for Matlab mcload_inline
*
* Revision 1.61  2003/04/25 16:24:44  farhi
* corrected 4PI scattering from randvec_* functions causing mcdisplay to crash
* when using (0,0,0) vector for coordinate transformations
*
* Revision 1.60  2003/04/16 14:55:47  farhi
* Major change in saving data so that it's shown just like PGPLOT
* and axes+labels should follow data orientation (if transposed)
* when in binary mode, sets -a as default. Use +a to force text header
*
* Revision 1.59  2003/04/09 15:51:33  farhi
* Moved MCSTAS_FORMAT define
*
* Revision 1.58  2003/04/08 18:55:56  farhi
* Made XML format more NeXus compliant
*
* Revision 1.57  2003/04/07 11:50:50  farhi
* Extended the way mcplot:plotter is assigned. Set --portable ok
* Handle Scilab:Tk and ~GTk menu (shifted)
* Updated help in mcrun and mcstas-r.c
*
* Revision 1.56  2003/04/04 18:36:12  farhi
* Corrected $ and % chars for IDL format, conflicting with pfprintf (Dec/SGI)
*
* Revision 1.55  2003/04/04 15:11:08  farhi
* Use MCSTAS_FORMAT env var for default plotter, or use mcstas_config
* Corrected strlen(NULL pointer) for getenv(MCSTAS_FORMAT)==NULL
*
* Revision 1.54  2003/04/04 14:26:25  farhi
* Managed --no-runtime to work. Use MCSTAS_FORMAT env/define for default format
* Make --no-output-files still print out the integrated counts
*
* Revision 1.53  2003/02/18 09:10:52  farhi
* Just changed a message (warning for -a flag binary)
*
* Revision 1.51  2003/02/11 12:28:46  farhi
* Variouxs bug fixes after tests in the lib directory
* mcstas_r  : disable output with --no-out.. flag. Fix 1D McStas output
* read_table:corrected MC_SYS_DIR -> MCSTAS define
* monitor_nd-lib: fix Log(signal) log(coord)
* HOPG.trm: reduce 4000 points -> 400 which is enough and faster to resample
* Progress_bar: precent -> percent parameter
* CS: ----------------------------------------------------------------------
*
* Revision 1.50  2003/02/06 14:25:05  farhi
* Made --no-output-files work again and 1D McStas data 4 columns again
*
* : ----------------------------------------------------------------------
*
* Revision 1.7 2002/10/19 22:46:21 ef
*        gravitation for all with -g. Various output formats.
*
* Revision 1.6 2002/09/17 12:01:21 ef
*        changed randvec_target_sphere to circle
* added randvec_target_rect
*
* Revision 1.5 2002/09/03 19:48:01 ef
*        corrected randvec_target_sphere. created target_rect.
*
* Revision 1.4 2002/09/02 18:59:05 ef
*        moved adapt_tree functions to independent lib. Updated sighandler.
*
* Revision 1.3 2002/08/28 11:36:37 ef
*        Changed to lib/share/c code
*
* Revision 1.2 2001/10/10 11:36:37 ef
*        added signal handler
*
* Revision 1.1 1998/08/29 11:36:37 kn
*        Initial revision
*
*******************************************************************************/

#ifndef MCSTAS_R_H
#include "mcstas-r.h"
#endif
#ifdef DANSE
#include "mcstas-globals.h"
#endif

/*******************************************************************************
* The I/O format definitions and functions
*******************************************************************************/

#ifndef DANSE
#ifdef MC_ANCIENT_COMPATIBILITY
int mctraceenabled = 0;
int mcdefaultmain  = 0;
#endif
/* else defined directly in the McStas generated C code */

static   long mcseed                 = 0;
static   int  mcascii_only           = 0;
static   int  mcsingle_file          = 0;
static   long mcstartdate            = 0;
static   int  mcdisable_output_files = 0;
mcstatic int  mcgravitation          = 0;
mcstatic int  mcdotrace              = 0;
/* mcstatic FILE *mcsiminfo_file        = NULL; */
static   char *mcdirname             = NULL;
static   char *mcsiminfo_name        = "mcstas";
int      mcallowbackprop             = 0;
int      mcMagnet                    = 0;
/*the magnet stack*/
double*  mcMagnetData                = NULL;
Coords   mcMagnetPos;
Rotation mcMagnetRot;
char*    mcDetectorCustomHeader      = NULL;
char*    mcopenedfiles               = "";
long     mcopenedfiles_size          = 0;
#endif

/* mcMagneticField(x, y, z, t, Bx, By, Bz) */
void (*mcMagneticField) (double, double, double, double,
			 double*, double*, double*) = NULL;
void (*mcMagnetPrecession) (double, double, double, double, double, double,
			    double, double*, double*, double*, double, Coords, Rotation) = NULL;

/* Number of neutron histories to simulate. */
#ifndef DANSE
mcstatic double mcncount             = 1e6;
mcstatic double mcrun_num            = 0;
#endif

/* parameters handling ====================================================== */

/* Instrument input parameter type handling. */
/* mcparm_double: extract double value from 's' into 'vptr' */
static int
mcparm_double(char *s, void *vptr)
{
  char *p;
  double *v = (double *)vptr;

  if (!s) { *v = 0; return(1); }
  *v = strtod(s, &p);
  if(*s == '\0' || (p != NULL && *p != '\0') || errno == ERANGE)
    return 0;                        /* Failed */
  else
    return 1;                        /* Success */
}

/* mcparminfo_double: display parameter type double */
static char *
mcparminfo_double(char *parmname)
{
  return "double";
}

/* mcparmerror_double: display error message when failed extract double */
static void
mcparmerror_double(char *parm, char *val)
{
  fprintf(stderr, "Error: Invalid value '%s' for floating point parameter %s (mcparmerror_double)\n",
          val, parm);
}

/* mcparmprinter_double: convert double to string */
static void
mcparmprinter_double(char *f, void *vptr)
{
  double *v = (double *)vptr;
  sprintf(f, "%g", *v);
}

/* mcparm_int: extract int value from 's' into 'vptr' */
static int
mcparm_int(char *s, void *vptr)
{
  char *p;
  int *v = (int *)vptr;
  long x;

  if (!s) { *v = 0; return(1); }
  *v = 0;
  x = strtol(s, &p, 10);
  if(x < INT_MIN || x > INT_MAX)
    return 0;                        /* Under/overflow */
  *v = x;
  if(*s == '\0' || (p != NULL && *p != '\0') || errno == ERANGE)
    return 0;                        /* Failed */
  else
    return 1;                        /* Success */
}

/* mcparminfo_int: display parameter type int */
static char *
mcparminfo_int(char *parmname)
{
  return "int";
}

/* mcparmerror_int: display error message when failed extract int */
static void
mcparmerror_int(char *parm, char *val)
{
  fprintf(stderr, "Error: Invalid value '%s' for integer parameter %s (mcparmerror_int)\n",
          val, parm);
}

/* mcparmprinter_int: convert int to string */
static void
mcparmprinter_int(char *f, void *vptr)
{
  int *v = (int *)vptr;
  sprintf(f, "%d", *v);
}

/* mcparm_string: extract char* value from 's' into 'vptr' (copy) */
static int
mcparm_string(char *s, void *vptr)
{
  char **v = (char **)vptr;
  if (!s) { *v = NULL; return(1); }
  *v = (char *)malloc(strlen(s) + 1);
  if(*v == NULL)
  {
    exit(fprintf(stderr, "Error: Out of memory %li (mcparm_string).\n", (long)strlen(s) + 1));
  }
  strcpy(*v, s);
  return 1;                        /* Success */
}

/* mcparminfo_string: display parameter type string */
static char *
mcparminfo_string(char *parmname)
{
  return "string";
}

/* mcparmerror_string: display error message when failed extract string */
static void
mcparmerror_string(char *parm, char *val)
{
  fprintf(stderr, "Error: Invalid value '%s' for string parameter %s (mcparmerror_string)\n",
          val, parm);
}

/* mcparmprinter_string: convert string to string (including esc chars) */
static void
mcparmprinter_string(char *f, void *vptr)
{
  char **v = (char **)vptr;
  char *p;

  if (!*v) { *f='\0'; return; }
  strcpy(f, "");
  for(p = *v; *p != '\0'; p++)
  {
    switch(*p)
    {
      case '\n':
        strcat(f, "\\n");
        break;
      case '\r':
        strcat(f, "\\r");
        break;
      case '"':
        strcat(f, "\\\"");
        break;
      case '\\':
        strcat(f, "\\\\");
        break;
      default:
        strncat(f, p, 1);
    }
  }
  /* strcat(f, "\""); */
}

/* now we may define the parameter structure, using previous functions */
static struct
  {
    int (*getparm)(char *, void *);
    char * (*parminfo)(char *);
    void (*error)(char *, char *);
    void (*printer)(char *, void *);
  } mcinputtypes[] =
      {
        mcparm_double, mcparminfo_double, mcparmerror_double,
                mcparmprinter_double,
        mcparm_int, mcparminfo_int, mcparmerror_int,
                mcparmprinter_int,
        mcparm_string, mcparminfo_string, mcparmerror_string,
                mcparmprinter_string
      };

/* mcestimate_error: compute sigma from N,p,p2 in Gaussian large numbers approx */
double mcestimate_error(double N, double p1, double p2)
{
  double pmean, n1;
  if(N <= 1)
    return p1;
  pmean = p1 / N;
  n1 = N - 1;
  /* Note: underflow may cause p2 to become zero; the fabs() below guards
     against this. */
  return sqrt((N/n1)*fabs(p2 - pmean*pmean));
}

/* mcset_ncount: set total number of neutrons to generate */
void mcset_ncount(double count)
{
  mcncount = count;
}

/* mcget_ncount: get total number of neutrons to generate */
double mcget_ncount(void)
{
  return mcncount;
}

/* mcget_run_num: get curent number of neutrons in TRACE */
double mcget_run_num(void)
{
  return mcrun_num;
}

#ifdef USE_MPI
/* MPI rank */
static int mpi_node_rank;
static int mpi_node_root = 0;

/*******************************************************************************
* mc_MPI_Reduce: Gathers arrays from MPI nodes using Reduce function.
*******************************************************************************/
int mc_MPI_Reduce(void *sbuf, void *rbuf,
                  int count, MPI_Datatype dtype,
                  MPI_Op op, int root, MPI_Comm comm)
{
  void *lrbuf;
  int dsize;
  int res= MPI_SUCCESS;
  
  if (!sbuf || count <= 0) return(-1);

  MPI_Type_size(dtype, &dsize);
  lrbuf = malloc(count*dsize);
  if (lrbuf == NULL)
    exit(fprintf(stderr, "Error: Out of memory %li (mc_MPI_Reduce).\n", (long)count*dsize));
  /* we must cut the buffer into blocks not exceeding the MPI max buffer size of 32000 */
  long offset=0;
  int  length=MPI_REDUCE_BLOCKSIZE; /* defined in mcstas.h */
  while (offset < count && res == MPI_SUCCESS) {
    if (!length || offset+length > count-1) length=count-offset; else length=MPI_REDUCE_BLOCKSIZE;
    res = MPI_Reduce((void*)(sbuf+offset*dsize), (void*)(lrbuf+offset*dsize), length, dtype, op, root, comm);
    offset += length;
  }

  if(res != MPI_SUCCESS)
    fprintf(stderr, "Warning: node %i: MPI_Reduce error (mc_MPI_Reduce) at offset=%i, count=%i\n", mpi_node_rank, offset, count);

  if(mpi_node_rank == root)
    memcpy(rbuf, lrbuf, count*dsize);

  free(lrbuf);
  return res;
}

/*******************************************************************************
* mc_MPI_Send: Send array to MPI node by blocks to avoid buffer limit
*******************************************************************************/
int mc_MPI_Send(void *sbuf, 
                  int count, MPI_Datatype dtype,
                  int dest, MPI_Comm comm)
{
  int dsize;
  int res= MPI_SUCCESS;
  
  if (!sbuf || count <= 0) return(-1);

  MPI_Type_size(dtype, &dsize);

  long offset=0;
  int  tag=1;
  int  length=MPI_REDUCE_BLOCKSIZE; /* defined in mcstas.h */
  while (offset < count && res == MPI_SUCCESS) {
    if (offset+length > count-1) length=count-offset; else length=MPI_REDUCE_BLOCKSIZE;
    res = MPI_Send((void*)(sbuf+offset*dsize), length, dtype, dest, tag++, comm);
    offset += length;
  }

  if(res != MPI_SUCCESS)
    fprintf(stderr, "Warning: node %i: MPI_Send error (mc_MPI_Send) at offset=%i, count=%i tag=%i\n", mpi_node_rank, offset, count, tag);

  return res;
}

/*******************************************************************************
* mc_MPI_Recv: Receives arrays from MPI nodes by blocks to avoid buffer limit
*             the buffer must have been allocated previously.
*******************************************************************************/
int mc_MPI_Recv(void *sbuf, 
                  int count, MPI_Datatype dtype,
                  int source, MPI_Comm comm)
{
  int dsize;
  int res= MPI_SUCCESS;
  
  if (!sbuf || count <= 0) return(-1);

  MPI_Type_size(dtype, &dsize);

  long offset=0;
  int  tag=1;
  int  length=MPI_REDUCE_BLOCKSIZE; /* defined in mcstas.h */
  while (offset < count && res == MPI_SUCCESS) {
    if (offset+length > count-1) length=count-offset; else length=MPI_REDUCE_BLOCKSIZE;
    res = MPI_Recv((void*)(sbuf+offset*dsize), length, dtype, source, tag++, comm, MPI_STATUS_IGNORE);
    offset += length;
  }

  if(res != MPI_SUCCESS)
    fprintf(stderr, "Warning: node %i: MPI_Send error (mc_MPI_Send) at offset=%i, count=%i tag=%i\n", mpi_node_rank, offset, count, tag);

  return res;
}

#endif /* USE_MPI */

/* Multiple output format support. ========================================== */
#ifdef USE_NEXUS
#define mcNUMFORMATS 9
#else
#define mcNUMFORMATS 8
#endif
#ifndef MCSTAS_FORMAT
#define MCSTAS_FORMAT "McStas"  /* default format */
#endif

#ifndef DANSE
mcstatic struct mcformats_struct mcformat;
mcstatic struct mcformats_struct mcformat_data;
#endif

/*******************************************************************************
* Definition of output formats. structure defined in mcstas-r.h
* Name aliases are defined in mcuse_format_* functions (below)
*******************************************************************************/

mcstatic struct mcformats_struct mcformats[mcNUMFORMATS] = {
  { "McStas", "sim",
    "%PREFormat: %FMT file. Use mcplot/PGPLOT to view.\n"
      "%PREURL:    http://www.mcstas.org/\n"
      "%PREEditor: %USR\n"
      "%PRECreator:%SRC simulation (McStas " MCSTAS_VERSION ")\n"
      "%PREDate:   Simulation started (%DATL) %DAT\n"
      "%PREFile:   %FIL\n",
    "%PREEndDate:%DAT\n",
    "%PREbegin %TYP\n",
    "%PREend %TYP\n",
    "%PRE%NAM: %VAL\n",
    "", "",
    "%PREErrors [%PAR/%FIL]: \n", "",
    "%PREEvents [%PAR/%FIL]: \n", "" },
  { "Scilab", "sci",
    "function mc_%VPA = get_%VPA(p)\n"
      "// %FMT function issued from McStas on %DAT\n"
      "// McStas simulation %SRC: %FIL %FMT\n"
      "// Import data using scilab> exec('%VPA.sci',-1); s=get_%VPA(); and s=get_%VPA('plot'); to plot\n"
      "mode(-1); //silent execution\n"
      "if argn(2) > 0, p=1; else p=0; end\n"
      "mc_%VPA = struct();\n"
      "mc_%VPA.Format ='%FMT';\n"
      "mc_%VPA.URL    ='http://www.mcstas.org';\n"
      "mc_%VPA.Editor ='%USR';\n"
      "mc_%VPA.Creator='%SRC McStas " MCSTAS_VERSION " simulation';\n"
      "mc_%VPA.Date   =%DATL; // for getdate\n"
      "mc_%VPA.File   ='%FIL';\n",
    "mc_%VPA.EndDate=%DATL; // for getdate\nendfunction\n"
    "function d=mcload_inline(d)\n"
      "// local inline func to load data\n"
      "execstr(['S=['+part(d.type,10:(length(d.type)-1))+'];']);\n"
      "if ~length(d.data)\n"
      " if ~length(strindex(d.format, 'binary'))\n"
      "  exec(d.filename,-1);p=d.parent;\n"
      "  if ~execstr('d2='+d.func+'();','errcatch'),d=d2; d.parent=p;end\n"
      " else\n"
      "  if length(strindex(d.format, 'float')), t='f';\n"
      "  elseif length(strindex(d.format, 'double')), t='d';\n"
      "  else return; end\n"
      "  fid=mopen(d.filename, 'rb');\n"
      "  pS = prod(S);\n"
      "  x = mget(3*pS, t, fid);\n"
      "  d.data  =matrix(x(1:pS), S);\n"
      "  if length(x) >= 3*pS,\n"
      "  d.errors=matrix(x((pS+1):(2*pS)), S);\n"
      "  d.events=matrix(x((2*pS+1):(3*pS)), S);end\n"
      "  mclose(fid);\n"
      "  return\n"
      " end\n"
      "end\n"
      "endfunction\n"
      "function d=mcplot_inline(d,p)\n"
      "// local inline func to plot data\n"
      "if ~length(strindex(d.type,'0d')), d=mcload_inline(d); end\n"
      "if ~p, return; end;\n"
      "execstr(['l=[',d.xylimits,'];']); S=size(d.data);\n"
      "t1=['['+d.parent+'] '+d.filename+': '+d.title];t = [t1;['  '+d.variables+'=['+d.values+']'];['  '+d.signal];['  '+d.statistics]];\n"
      "mprintf('%%s\\n',t(:));\n"
      "if length(strindex(d.type,'0d')),return; end\n"
      "w=winsid();if length(w),w=w($)+1; else w=0; end\n"
      "xbasr(w); xset('window',w);\n"
      "if length(strindex(d.type,'2d'))\n"
      " if S(2) > 1, d.stepx=abs(l(1)-l(2))/(S(2)-1); else d.stepx=0; end\n"
      " if S(1) > 1, d.stepy=abs(l(3)-l(4))/(S(1)-1); else d.stepy=0; end\n"
      " d.x=linspace(l(1)+d.stepx/2,l(2)-d.stepx/2,S(2));\n"
      " d.y=linspace(l(3)+d.stepy/2,l(4)-d.stepy/2,S(1)); z=d.data;\n"
      " xlab=d.xlabel; ylab=d.ylabel; x=d.x; y=d.y;\n"
      " fz=max(abs(z));fx=max(abs(d.x));fy=max(abs(d.y));\n"
      " if fx>0,fx=round(log10(fx)); x=x/10^fx; xlab=xlab+' [*10^'+string(fx)+']'; end\n"
      " if fy>0,fy=round(log10(fy)); y=y/10^fy; ylab=ylab+' [*10^'+string(fy)+']'; end\n"
      " if fz>0,fz=round(log10(fz)); z=z/10^fz; t1=t1+' [*10^'+string(fz)+']'; end\n"
      " xset('colormap',hotcolormap(64));\n"
      " plot3d1(x,y,z',90,0,xlab+'@'+ylab+'@'+d.zlabel,[-1,2,4]); xtitle(t);\n"
      "else\n"
      " if max(S) > 1, d.stepx=abs(l(1)-l(2))/(max(S)-1); else d.stepx=0; end\n"
      " d.x=linspace(l(1)+d.stepx/2,l(2)-d.stepx/2,max(S));\n"
      " plot2d(d.x,d.data);xtitle(t,d.xlabel,d.ylabel);\n"
      "end\n"
      "xname(t1);\nendfunction\n"
    "mc_%VPA=get_%VPA();\n",
    "// Section %TYP [%NAM] (level %LVL)\n"
      "%PREt=[]; execstr('t=mc_%VNA.class','errcatch'); if ~length(t), mc_%VNA = struct(); end; mc_%VNA.class = '%TYP';",
    "%PREmc_%VPA.mc_%VNA = 0; mc_%VPA.mc_%VNA = mc_%VNA;\n",
    "%PREmc_%SEC.%NAM = '%VAL';\n",
    "%PREmc_%VPA.func='get_%VPA';\n%PREmc_%VPA.data = [ \n",
    " ]; // end of data\n%PREif length(mc_%VPA.data) == 0, single_file=0; else single_file=1; end\n%PREmc_%VPA=mcplot_inline(mc_%VPA,p);\n",
    "%PREerrors = [ \n",
    " ]; // end of errors\n%PREif single_file == 1, mc_%VPA.errors=errors; end\n",
    "%PREevents = [ \n",
    " ]; // end of events\n%PREif single_file == 1, mc_%VPA.events=events; end\n"},
  { "Matlab", "m",
    "function mc_%VPA = get_%VPA(p)\n"
      "%% %FMT function issued from McStas on %DAT\n"
      "%% McStas simulation %SRC: %FIL\n"
      "%% Import data using matlab> s=%VPA; and s=%VPA('plot'); to plot\n"
      "if nargout == 0 | nargin > 0, p=1; else p=0; end\n"
      "mc_%VPA.Format ='%FMT';\n"
      "mc_%VPA.URL    ='http://www.mcstas.org';\n"
      "mc_%VPA.Editor ='%USR';\n"
      "mc_%VPA.Creator='%SRC McStas " MCSTAS_VERSION " simulation';\n"
      "mc_%VPA.Date   =%DATL; %% for datestr\n"
      "mc_%VPA.File   ='%FIL';\n",
    "mc_%VPA.EndDate=%DATL; %% for datestr\n"
      "function d=mcload_inline(d)\n"
      "%% local inline function to load data\n"
      "S=d.type; eval(['S=[ ' S(10:(length(S)-1)) ' ];']);\n"
      "if isempty(d.data)\n"
      " if ~length(findstr(d.format, 'binary'))\n"
      "  if ~strcmp(d.filename,[d.func,'.m']) copyfile(d.filename,[d.func,'.m']); end\n"
      "  p=d.parent;path(path);\n"
      "  eval(['d=',d.func,';']);d.parent=p;\n"
      "  if ~strcmp(d.filename,[d.func,'.m']) delete([d.func,'.m']); end\n"
      " else\n"
      "  if length(findstr(d.format, 'float')), t='single';\n"
      "  elseif length(findstr(d.format, 'double')), t='double';\n"
      "  else return; end\n"
      "  if length(S) == 1, S=[S 1]; end\n"
      "  fid=fopen(d.filename, 'r');\n"
      "  pS = prod(S);\n"
      "  x = fread(fid, 3*pS, t);\n"
      "  d.data  =reshape(x(1:pS), S);\n"
      "  if prod(size(x)) >= 3*pS,\n"
      "  d.errors=reshape(x((pS+1):(2*pS)), S);\n"
      "  d.events=reshape(x((2*pS+1):(3*pS)), S);end\n"
      "  fclose(fid);\n"
      "  return\n"
      " end\n"
      "end\n"
      "return;\n"
      "function d=mcplot_inline(d,p)\n"
      "%% local inline function to plot data\n"
      "if isempty(findstr(d.type,'0d')), d=mcload_inline(d); end\nif ~p, return; end;\n"
      "eval(['l=[',d.xylimits,'];']); S=size(d.data);\n"
      "t1=['[',d.parent,'] ',d.filename,': ',d.title];t = strvcat(t1,['  ',d.variables,'=[',d.values,']'],['  ',d.signal],['  ',d.statistics]);\n"
      "disp(t);\n"
      "if ~isempty(findstr(d.type,'0d')), return; end\n"
      "figure; if ~isempty(findstr(d.type,'2d'))\n"
      " if S(2) > 1, d.stepx=abs(l(1)-l(2))/(S(2)-1); else d.stepx=0; end\n"
      " if S(1) > 1, d.stepy=abs(l(3)-l(4))/(S(1)-1); else d.stepy=0; end\n"
      " d.x=linspace(l(1)+d.stepx/2,l(2)-d.stepx/2,S(2));\n"
      " d.y=linspace(l(3)+d.stepy/2,l(4)-d.stepy/2,S(1));\n"
      " surface(d.x,d.y,d.data); xlim([l(1) l(2)]); ylim([l(3) l(4)]); shading flat;\n"
      "else\n"
      " if max(S) > 1, d.stepx=abs(l(1)-l(2))/(max(S)-1); else d.stepx=0; end\n"
      " d.x=linspace(l(1)+d.stepx/2,l(2)-d.stepx/2,max(S));\n"
      " plot(d.x,d.data); xlim([l(1) l(2)]);\n"
      "end\n"
      "xlabel(d.xlabel); ylabel(d.ylabel); title(t); \n"
      "set(gca,'position',[.18,.18,.7,.65]); set(gcf,'name',t1);grid on;\n"
      "if ~isempty(findstr(d.type,'2d')), colorbar; end\n",
    "%% Section %TYP [%NAM] (level %LVL)\n"
      "mc_%VNA.class = '%TYP';",
    "mc_%VPA.mc_%VNA = mc_%VNA;\n",
    "%PREmc_%SEC.%NAM = '%VAL';\n",
    "%PREmc_%VPA.func='%VPA';\n%PREmc_%VPA.data = [ \n",
    " ]; %% end of data\nif length(mc_%VPA.data) == 0, single_file=0; else single_file=1; end\nmc_%VPA=mcplot_inline(mc_%VPA,p);\n",
    "%PREerrors = [ \n",
    " ]; %% end of errors\nif single_file, mc_%VPA.errors=errors; end\n",
    "%PREevents = [ \n",
    " ]; %% end of events\nif single_file, mc_%VPA.events=events; end\n"},
  { "IDL", "pro",
    "; McStas/IDL file. Import using idl> s=%VPA() and s=%VPA(/plot) to plot\n"
      "function mcload_inline,d\n"
      "; local inline function to load external data\n"
      "S=d.type & a=execute('S=long(['+strmid(S,9,strlen(S)-10)+'])')\n"
      "if strpos(d.format, 'binary') lt 0 then begin\n"
      " p=d.parent\n"
      " x=read_binary(d.filename)\n"
      " get_lun, lun\n"
      " openw,lun,d.func+'.pro'\n"
      " writeu, lun,x\n"
      " free_lun,lun\n"
      " resolve_routine, d.func, /is_func, /no\n"
      " d=call_function(d.func)\n"
      "endif else begin\n"
      " if strpos(d.format, 'float') ge 0 then t=4 $\n"
      " else if strpos(d.format, 'double') ge 0 then t=5 $\n"
      " else return,d\n"
      " x=read_binary(d.filename, data_type=t)\n"
      " pS=n_elements(S)\nif pS eq 1 then pS=long(S) $\n"
      " else if pS eq 2 then pS=long(S(0)*S(1)) $\n"
      " else pS=long(S(0)*S(1)*S(2))\n"
      " pS=pS(0)\nstv,d,'data',reform(x(0:(pS-1)),S)\n"
      " d.data=transpose(d.data)\n"
      " if n_elements(x) ge long(3*pS) then begin\n"
      "  stv,d,'errors',reform(x(pS:(2*pS-1)),S)\n"
      "  stv,d,'events',reform(x((2*pS):(3*pS-1)),S)\n"
      "  d.errors=transpose(d.errors)\n"
      "  d.events=transpose(d.events)\n"
      " endif\n"
      "endelse\n"
      "return,d\nend ; FUN load\n"
    "function mcplot_inline,d,p\n"
      "; local inline function to plot data\n"
      "if size(d.data,/typ) eq 7 and strpos(d.type,'0d') lt 0 then d=mcload_inline(d)\n"
      "if p eq 0 or strpos(d.type,'0d') ge 0 then return, d\n"
      "S=d.type & a=execute('S=long(['+strmid(S,9,strlen(S)-10)+'])')\n"
      "stv,d,'data',reform(d.data,S,/over)\n"
      "if total(strpos(tag_names(d),'ERRORS')+1) gt 0 then begin\n"
      " stv,d,'errors',reform(d.errors,S,/over)\n"
      " stv,d,'events',reform(d.events,S,/over)\n"
      "endif\n"
      "d.xylimits=strjoin(strsplit(d.xylimits,' ',/extract),',') & a=execute('l=['+d.xylimits+']')\n"
      "t1='['+d.parent+'] '+d.filename+': '+d.title\n"
      "t=[t1,'  '+d.variables+'=['+d.values+']','  '+d.signal,'  '+d.statistics]\n"
      "print,t\n"
      "if strpos(d.type,'0d') ge 0 then return,d\n"
      "d.xlabel=strjoin(strsplit(d.xlabel,'`!\"^&*()-+=|\\,.<>/?@''~#{[}]',/extract),'_')\n"
      "d.ylabel=strjoin(strsplit(d.ylabel,'`!\"^&*()-+=|\\,.<>/?@''~#{[}]',/extract),'_')\n"
      "stv,d,'x',l(0)+indgen(S(0))*(l(1)-l(0))/S(0)\n"
      "if strpos(d.type,'2d') ge 0 then begin\n"
      "  name={DATA:d.func,IX:d.xlabel,IY:d.ylabel}\n"
      "  stv,d,'y',l(2)+indgen(S(1))*(l(3)-l(2))/S(1)\n"
      "  live_surface,d.data,xindependent=d.x,yindependent=d.y,name=name,reference_out=Win\n"
      "endif else begin\n"
      "  name={DATA:d.func,I:d.xlabel}\n"
      "  live_plot,d.data,independent=d.x,name=name,reference_out=Win\n"
      "endelse\n"
      "live_text,t,Window_In=Win.Win,location=[0.3,0.9]\n"
      "return,d\nend ; FUN plot\n"
    "pro stv,S,T,V\n"
      "; procedure set-tag-value that does S.T=V\n"
      "sv=size(V)\n"
      "T=strupcase(T)\n"
      "TL=strupcase(tag_names(S))\n"
      "id=where(TL eq T)\n"
      "sz=[0,0,0]\n"
      "vd=n_elements(sv)-2\n"
      "type=sv[vd]\n"
      "if id(0) ge 0 then d=execute('sz=SIZE(S.'+T+')')\n"
      "if (sz(sz(0)+1) ne sv(sv(0)+1)) or (sz(0) ne sv(0)) $\n"
      "  or (sz(sz(0)+2) ne sv(sv(0)+2)) $\n"
      "  or type eq 8 then begin\n"
      " ES = ''\n"
      " for k=0,n_elements(TL)-1 do begin\n"
      "  case TL(k) of\n"
      "   T:\n"
      "   else: ES=ES+','+TL(k)+':S.'+TL(k)\n"
      "  endcase\n"
      " endfor\n"
      " d=execute('S={'+T+':V'+ES+'}')\n"
      "endif else d=execute('S.'+T+'=V')\n"
      "end ; PRO stv\n"
    "function %VPA,plot=plot\n"
      "; %FMT function issued from McStas on %DAT\n"
      "; McStas simulation %SRC: %FIL\n"
      "; import using s=%VPA() and s=%VPA(/plot) to plot\n"
      "if keyword_set(plot) then p=1 else p=0\n"
      "%7$s={Format:'%FMT',URL:'http://www.mcstas.org',"
      "Editor:'%USR',$\n"
      "Creator:'%SRC McStas " MCSTAS_VERSION " simulation',$\n"
      "Date:%DATL,"
      "File:'%FIL'}\n",
    "stv,%VPA,'EndDate',%DATL ; for systime\nreturn, %VPA\nend\n",
    "; Section %TYP [%NAM] (level %LVL)\n"
      "%PRE%VNA={class:'%TYP'}\n",
    "%PREstv,%VPA,'%VNA',%VNA\n",
    "%PREstv,%SEC,'%NAM','%VAL'\n",
    "%PREstv,%VPA,'func','%VPA' & data=[ $\n",
    " ]\n%PREif size(data,/type) eq 7 then single_file=0 else single_file=1\n"
    "%PREstv,%VPA,'data',data & data=0 & %VPA=mcplot_inline(%VPA,p)\n",
    "%PREif single_file ne 0 then begin errors=[ ",
    " ]\n%PREstv,%VPA,'errors',reform(errors,%MDIM,%NDIM,/over) & errors=0\n%PREendif\n",
    "%PREif single_file ne 0 then begin events=[ ",
    " ]\n%PREstv,%VPA,'events',reform(events,%MDIM,%NDIM,/over) & events=0\n%PREendif\n\n"},
  { "XML", "xml",
    "<?xml version=\"1.0\" ?>\n<!--\n"
      "URL:    http://www.nexusformat.org/\n"
      "Editor: %USR\n"
      "Creator:%SRC McStas " MCSTAS_VERSION " [www.mcstas.org].\n"
      "Date:   Simulation started (%DATL) %DAT\n"
      "File:   %FIL\n"
      "View with Mozilla, InternetExplorer, gxmlviewer, kxmleditor\n-->\n"
      "<NX%PAR file_name=\"%FIL\" file_time=\"%DAT\" user=\"%USR\">\n"
        "<NXentry name=\"McStas " MCSTAS_VERSION "\"><start_time>%DAT</start_time>\n",
    "<end_time>%DAT</end_time></NXentry></NX%PAR>\n<!-- EndDate:%DAT -->\n",
    "%PRE<NX%TYP name=\"%NAM\">\n",
    "%PRE</NX%TYP>\n",
    "%PRE<%NAM>%VAL</%NAM>\n",
    "%PRE<%XVL long_name=\"%XLA\" axis=\"1\" primary=\"1\" min=\"%XMIN\""
        " max=\"%XMAX\" dims=\"%MDIM\" range=\"1\"></%XVL>\n"
      "%PRE<%YVL long_name=\"%YLA\" axis=\"2\" primary=\"1\" min=\"%YMIN\""
        " max=\"%YMAX\" dims=\"%NDIM\" range=\"1\"></%YVL>\n"
      "%PRE<%ZVL long_name=\"%ZLA\" axis=\"3\" primary=\"1\" min=\"%ZMIN\""
        " max=\"%ZMAX\" dims=\"%PDIM\" range=\"1\"></%ZVL>\n"
      "%PRE<data long_name=\"%TITL\" signal=\"1\"  axis=\"[%XVL,%YVL,%ZVL]\" file_name=\"%FIL\">\n",
    "%PRE</data>\n",
    "%PRE<errors>\n", "%PRE</errors>\n",
    "%PRE<monitor>\n", "%PRE</monitor>\n"},
  { "HTML", "html",
    "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD %DAT//EN\"\n"
      "\"http://www.w3.org/TR/html4/strict.dtd\">\n"
      "<HTML><HEAD><META name=\"Author\" content=\"%PAR\">\n"
      "<META name=\"Creator\" content=\"%PAR (%SRC) McStas " MCSTAS_VERSION " [www.mcstas.org] simulation\">\n"
      "<META name=\"Date\" content=\"%DAT\">\n"
      "<TITLE>[McStas %PAR (%SRC)]%FIL</TITLE></HEAD>\n"
      "<BODY><center><h1><a name=\"%PAR\">"
        "McStas simulation %SRC (%SRC): Result file %FIL.html</a></h1></center><br>\n"
        "This simulation report was automatically created by"
        " <a href=\"http://www.mcstas.org/\"><i>McStas " MCSTAS_VERSION "</i></a><br>\n"
        "<pre>User:   %USR<br>\n"
        "%PRECreator: <a href=\"%SRC\">%SRC</a> %PAR McStas simulation<br>\n"
        "%PREFormat:  %FMT<br>\n"
        "%PREDate:    (%DATL) %DAT<br></pre>\n"
        "VRML viewers may be obtained at <a href=\"http://cic.nist.gov/vrml/vbdetect.html\">http://cic.nist.gov/vrml/vbdetect.html</a>\n",
    "<b>EndDate: </b>(%DATL) %DAT<br></BODY></HTML>\n",
    "%PRE<h%LVL><a name=\"%NAM\">%TYP %NAM</a></h%LVL> "
      "[child of <a href=\"#%PAR\">%PAR</a>]<br>\n",
    "[end of <a href=\"#%NAM\">%TYP %NAM</a>]<br>\n",
    "%PRE<b>%NAM: </b>%VAL<br>\n",
    "%PRE<b>DATA</b><br><center><embed src=\"%FIL\" type=\"model/vrml\" width=\"75%%\" height=\"50%%\"></embed><br>File <a href=\"%FIL\">%FIL [VRML format]</a></center><br>\n", "%PREEnd of DATA<br>\n",
    "%PRE<b>ERRORS</b><br>\n","%PREEnd of ERRORS<br>\n",
    "%PRE<b>EVENTS</b><br>\n", "%PREEnd of EVENTS<br>\n"},
  { "Octave", "m",
    "function mc_%VPA = get_%VPA(p)\n"
      "%% %FMT function issued from McStas on %DAT\n"
      "%% McStas simulation %SRC: %FIL\n"
      "%% Import data using octave> s=%VPA(); and plot with s=%VPA('plot');\n"
      "if nargin > 0, p=1; else p=0; end\n"
      "mc_%VPA.Format ='%FMT';\n"
      "mc_%VPA.URL    ='http://www.mcstas.org';\n"
      "mc_%VPA.Editor ='%USR';\n"
      "mc_%VPA.Creator='%SRC McStas " MCSTAS_VERSION " simulation';\n"
      "mc_%VPA.Date   =%DATL; %% for datestr\n"
      "mc_%VPA.File   ='%FIL';\n",
    "mc_%VPA.EndDate=%DATL; %% for datestr\nendfunction\n"
      "if exist('mcload_inline'), return; end\n"
      "function d=mcload_inline(d)\n"
      "%% local inline function to load data\n"
      "S=d.type; eval(['S=[ ' S(10:(length(S)-1)) ' ];']);\n"
      "if isempty(d.data)\n"
      " if ~length(findstr(d.format, 'binary'))\n"
      "  source(d.filename);p=d.parent;\n"
      "  eval(['d=get_',d.func,';']);d.parent=p;\n"
      " else\n"
      "  if length(findstr(d.format, 'float')), t='float';\n"
      "  elseif length(findstr(d.format, 'double')), t='double';\n"
      "  else return; end\n"
      "  if length(S) == 1, S=[S 1]; end\n"
      "  fid=fopen(d.filename, 'r');\n"
      "  pS = prod(S);\n"
      "  x = fread(fid, 3*pS, t);\n"
      "  d.data  =reshape(x(1:pS), S);\n"
      "  if prod(size(x)) >= 3*pS,\n"
      "  d.errors=reshape(x((pS+1):(2*pS)), S);\n"
      "  d.events=reshape(x((2*pS+1):(3*pS)), S);end\n"
      "  fclose(fid);\n"
      "  return\n"
      " end\n"
      "end\n"
      "return;\nendfunction\n\n"
      "function d=mcplot_inline(d,p)\n"
      "%% local inline function to plot data\n"
      "if isempty(findstr(d.type,'0d')), d=mcload_inline(d); end\nif ~p, return; end;\n"
      "eval(['l=[',d.xylimits,'];']); S=size(d.data);\n"
      "t1=['[',d.parent,'] ',d.filename,': ',d.title];t = strcat(t1,['  ',d.variables,'=[',d.values,']'],['  ',d.signal],['  ',d.statistics]);\n"
      "disp(t);\n"
      "if ~isempty(findstr(d.type,'0d')), return; end\n"
      "xlabel(d.xlabel); ylabel(d.ylabel); title(t);"
      "figure; if ~isempty(findstr(d.type,'2d'))\n"
      " if S(2) > 1, d.stepx=abs(l(1)-l(2))/(S(2)-1); else d.stepx=0; end\n"
      " if S(1) > 1, d.stepy=abs(l(3)-l(4))/(S(1)-1); else d.stepy=0; end\n"
      " d.x=linspace(l(1)+d.stepx/2,l(2)-d.stepx/2,S(2));\n"
      " d.y=linspace(l(3)+d.stepy/2,l(4)-d.stepy/2,S(1));\n"
      " mesh(d.x,d.y,d.data);\n"
      "else\n"
      " if max(S) > 1, d.stepx=abs(l(1)-l(2))/(max(S)-1); else d.stepx=0; end\n"
      " d.x=linspace(l(1)+d.stepx/2,l(2)-d.stepx/2,max(S));\n"
      " plot(d.x,d.data);\n"
      "end\nendfunction\n",
    "%% Section %TYP [%NAM] (level %LVL)\n"
      "mc_%VNA.class = '%TYP';",
    "mc_%VPA.mc_%VNA = mc_%VNA;\n",
    "%PREmc_%SEC.%NAM = '%VAL';\n",
    "%PREmc_%VPA.func='%VPA';\n%PREmc_%VPA.data = [ \n",
    " ]; %% end of data\nif length(mc_%VPA.data) == 0, single_file=0; else single_file=1; end\nmc_%VPA=mcplot_inline(mc_%VPA,p);\n",
    "%PREerrors = [ \n",
    " ]; %% end of errors\nif single_file, mc_%VPA.errors=errors; end\n",
    "%PREevents = [ \n",
    " ]; %% end of events\nif single_file, mc_%VPA.events=events; end\n"},
  { "VRML", "wrl",
    "#VRML V2.0 utf8\n%PREFormat: %FMT file\n"
      "%PREuse freeWRL, openvrml, vrmlview, CosmoPlayer, Cortona, Octaga... to view file\n"
      "WorldInfo {\n"
      "title \"%SRC/%FIL simulation Data\"\n"
      "info [ \"URL:    http://www.mcstas.org/\"\n"
      "       \"Editor: %USR\"\n"
      "       \"Creator:%SRC simulation (McStas)\"\n"
      "       \"Date:   Simulation started (%DATL) %DAT\"\n"
      "       \"File:   %FIL\" ]\n}\n"
      "Background { skyAngle [ 1.57 1.57] skyColor [0 0 1, 1 1 1, 0.1 0 0] }\n",
    "%PREEndDate:%DAT\n",
    "%PREbegin %TYP %PAR\n",
    "%PREend %TYP %PAR\n",
    "%PRE%SEC.%NAM= '%VAL'\n",
    "%PREThe Proto that contains data values and objects to plot these\n"
      "PROTO I_ERR_N_%VPA [\n"
      "%PREthe PROTO parameters\n"
      "  field MFFloat Data [ ]\n"
      "  field MFFloat Errors [ ]\n"
      "  field MFFloat Ncounts [ ]\n"
      "] { %PREThe plotting objects/methods in the Proto\n"
      "  %PREdraw a small sphere at the origin\n"
      "  DEF Data_%VPA Group {\n"
      "  children [\n"
      "    DEF CoordinateOrigin Group {\n"
      "      children [\n"
      "        Transform { translation  0 0 0 }\n"
      "        Shape { \n"
      "          appearance Appearance { \n"
      "            material Material {\n"
      "              diffuseColor 1.0 1.0 0.0\n"
      "              transparency 0.5 } }\n"
      "          geometry Sphere { radius .01 } \n"
      "    } ] }\n"
      "    %PREdefintion of the arrow allong Y axis\n"
      "    DEF ARROW Group {\n"
      "      children [\n"
      "        Transform {\n"
      "          translation 0 0.5 0\n"
      "          children [\n"
      "            Shape {\n"
      "              appearance DEF ARROW_APPEARANCE Appearance {\n"
      "                material Material {\n"
      "                  diffuseColor .3 .3 1\n"
      "                  emissiveColor .1 .1 .33\n"
      "                }\n"
      "              }\n"
      "              geometry Cylinder {\n"
      "                bottom FALSE\n"
      "                radius .005\n"
      "                height 1\n"
      "                top FALSE\n"
      "        } } ] }\n"
      "        Transform {\n"
      "          translation 0 1 0\n"
      "          children [\n"
      "            DEF ARROW_POINTER Shape {\n"
      "              geometry Cone {\n"
      "                bottomRadius .05\n"
      "                height .1\n"
      "              }\n"
      "              appearance USE ARROW_APPEARANCE\n"
      "    } ] } ] }\n"
      "    %PREthe arrow along X axis\n"
      "    Transform {\n"
      "      translation 0 0 0\n"
      "      rotation 1 0 0 1.57\n"
      "      children [\n"
      "        Group {\n"
      "          children [ \n"
      "            USE ARROW\n"
      "    ] } ] }\n"
      "    %PREthe arrow along Z axis\n"
      "    Transform {\n"
      "      translation 0 0 0\n"
      "      rotation 0 0 1 -1.57\n"
      "      children [\n"
      "        Group {\n"
      "          children [ \n"
      "            USE ARROW\n"
      "    ] } ] }\n"
      "    %PREthe Y label (which is vertical)\n"
      "    DEF Y_Label Group {\n"
      "      children [\n"
      "        Transform {\n"
      "          translation 0 1 0\n"
      "          children [\n"
      "            Billboard {\n"
      "              children [\n"
      "                Shape {\n"
      "                  appearance DEF LABEL_APPEARANCE Appearance {\n"
      "                    material Material {\n"
      "                      diffuseColor 1 1 .3\n"
      "                      emissiveColor .33 .33 .1\n"
      "                    } }\n"
      "                  geometry Text { \n"
      "                    string [ \"%ZVAR: %ZLA\", \"%ZMIN:%ZMAX - %PDIM points\" ] \n"
      "                    fontStyle FontStyle {  size .2 }\n"
      "    } } ] } ] } ] }\n"
      "    %PREthe X label\n"
      "    DEF X_Label Group {\n"
      "      children [\n"
      "        Transform {\n"
      "          translation 1 0 0\n"
      "          children [\n"
      "            Billboard {\n"
      "              children [\n"
      "                Shape {\n"
      "                  appearance DEF LABEL_APPEARANCE Appearance {\n"
      "                    material Material {\n"
      "                      diffuseColor 1 1 .3\n"
      "                      emissiveColor .33 .33 .1\n"
      "                    } }\n"
      "                  geometry Text { \n"
      "                    string [ \"%XVAR: %XLA\", \"%XMIN:%XMAX - %MDIM points\" ] \n"
      "                    fontStyle FontStyle {  size .2 }\n"
      "    } } ] } ] } ] }\n"
      "    %PREthe Z label\n"
      "    DEF Z_Label Group {\n"
      "      children [\n"
      "        Transform {\n"
      "          translation 0 0 1\n"
      "          children [\n"
      "            Billboard {\n"
      "              children [\n"
      "                Shape {\n"
      "                  appearance DEF LABEL_APPEARANCE Appearance {\n"
      "                    material Material {\n"
      "                      diffuseColor 1 1 .3\n"
      "                      emissiveColor .33 .33 .1\n"
      "                    } }\n"
      "                  geometry Text { \n"
      "                    string [ \"%YVAR: %YLA\", \"%YMIN:%YMAX - %NDIM points\" ] \n"
      "                    fontStyle FontStyle {  size .2 }\n"
      "    } } ] } ] } ] }\n"
      "    %PREThe text information (header data )\n"
      "    DEF Header Group {\n"
      "      children [\n"
      "        Transform {\n"
      "          translation 0 2 0\n"
      "          children [\n"
      "            Billboard {\n"
      "              children [\n"
      "                Shape {\n"
      "                  appearance Appearance {\n"
      "                    material Material { \n"
      "                      diffuseColor .9 0 0\n"
      "                      emissiveColor .9 0 0 }\n"
      "                  }\n"
      "                  geometry Text {\n"
      "                    string [ \"%PAR/%FIL\",\"%TITL\" ]\n"
      "                    fontStyle FontStyle {\n"
      "                        style \"BOLD\"\n"
      "                        size .2\n"
      "    } } } ] } ] } ] }\n"
      "    %PREThe Data plot\n"
      "    DEF MonitorData Group {\n"
      "      children [\n"
      "        DEF TransformData Transform {\n"
      "          children [\n"
      "            Shape {\n"
      "              appearance Appearance {\n"
      "                material Material { emissiveColor 0 0.2 0 }\n"
      "              }\n"
      "              geometry ElevationGrid {\n"
      "                xDimension  %MDIM\n"
      "                zDimension  %NDIM\n"
      "                xSpacing    1\n"
      "                zSpacing    1\n"
      "                solid       FALSE\n"
      "                height IS Data\n"
      "    } } ] } ] }\n"
      "    %PREThe VRMLScript that redimension x and z axis within 0:1\n"
      "    %PREand re-scale data within 0:1\n"
      "    DEF GetScale Script {\n"
      "      eventOut SFVec3f scale_vect\n"
      "      url \"javascript: \n"
      "        function initialize( ) {\n"
      "          scale_vect = new SFVec3f(1.0/%MDIM, 1.0/Math.abs(%ZMAX-%ZMIN), 1.0/%NDIM); }\" }\n"
      "  ] }\n"
      "ROUTE GetScale.scale_vect TO TransformData.scale\n} # end of PROTO\n"
      "%PREnow we call the proto with Data values\n"
      "I_ERR_N_%VPA {\nData [\n",
    "] # End of Data\n",
    "Errors [\n",
    "] # End of Errors\n",
    "Ncounts [\n",
    "] # End of Ncounts\n}" }
#ifdef USE_NEXUS
    ,
    { "NeXus", "nxs",
    "%PREFormat: %FMT file. Use hdfview to view.\n"
      "%PREURL:    http://www.mcstas.org/\n"
      "%PREEditor: %USR\n"
      "%PRECreator:%SRC simulation (McStas " MCSTAS_VERSION ")\n"
      "%PREDate:   Simulation started (%DATL) %DAT\n"
      "%PREFile:   %FIL\n",
    "%PREEndDate:%DAT\n",
    "%PREbegin %TYP\n",
    "%PREend %TYP\n",
    "%PRE%NAM: %VAL\n",
    "", "",
    "%PREErrors [%PAR/%FIL]: \n", "",
    "%PREEvents [%PAR/%FIL]: \n", "" }
#endif
};

/* file i/o handling ======================================================== */

/*******************************************************************************
* mcfull_file: allocates a full file name=mcdirname+file
*******************************************************************************/
char *mcfull_file(char *name, char *ext)
{
  int dirlen;
  char *mem;
  dirlen = mcdirname ? strlen(mcdirname) : 0;
  mem = malloc(dirlen + strlen(name) + 256);
  if(!mem)
  {
    exit(fprintf(stderr, "Error: Out of memory %li (mcfull_file)\n", (long)(dirlen + strlen(name) + 256)));
  }
  strcpy(mem, "");
  if(dirlen)
  {
    strcat(mem, mcdirname);
    if(mcdirname[dirlen - 1] != MC_PATHSEP_C &&
       name[0] != MC_PATHSEP_C)
      strcat(mem, MC_PATHSEP_S);
  }
  strcat(mem, name);
  if (!strchr(name, '.') && ext)
  { /* add extension if not in file name already */
    strcat(mem, ".");
    strcat(mem, ext);
  }
  return(mem);
}

/*******************************************************************************
* mcnew_file: opens a new file within mcdirname if non NULL
*             if mode is non 0, then mode is used, else mode is 'w'
*******************************************************************************/
FILE *mcnew_file(char *name, char *ext, char *mode)
{
  char *mem;
  FILE *file;

  if (!name || strlen(name) == 0) return(NULL);

  mem = mcfull_file(name, ext);
  file = fopen(mem, (mode ? mode : "w"));
  if(!file)
    fprintf(stderr, "Warning: could not open output file '%s' in mode '%s' (mcnew_file)\n", mem, mode);
  else {
    if (!mcopenedfiles || 
        (mcopenedfiles && mcopenedfiles_size <= strlen(mcopenedfiles)+strlen(mem))) {
      mcopenedfiles_size+=CHAR_BUF_LENGTH;
      if (!mcopenedfiles || !strlen(mcopenedfiles))
        mcopenedfiles = calloc(1, mcopenedfiles_size);
      else
        mcopenedfiles = realloc(mcopenedfiles, mcopenedfiles_size);
    } 
    strcat(mcopenedfiles, " ");
    strcat(mcopenedfiles, mem);
  }
  free(mem);
  
  return file;
} /* mcnew_file */

/*******************************************************************************
* str_rep: Replaces a token by an other (of SAME length) in a string
* This function modifies 'string'
*******************************************************************************/
char *str_rep(char *string, char *from, char *to)
{
  char *p;

  if (!string || !strlen(string)) return(string);
  if (strlen(from) != strlen(to)) return(string);

  p   = string;

  while (( p = strstr(p, from) ) != NULL) {
    long index;
    for (index=0; index<strlen(to); index++) p[index]=to[index];
  }
  return(string);
}

#define VALID_NAME_LENGTH 64
/*******************************************************************************
* mcvalid_name: makes a valid string for variable names.
*   copy 'original' into 'valid', replacing invalid characters by '_'
*   char arrays must be pre-allocated. n can be 0, or the maximum number of
*   chars to be copied/checked
*******************************************************************************/
static char *mcvalid_name(char *valid, char *original, int n)
{
  long i;


  if (original == NULL || strlen(original) == 0)
  { strcpy(valid, "noname"); return(valid); }
  if (n <= 0) n = strlen(valid);

  if (n > strlen(original)) n = strlen(original);
  else original += strlen(original)-n;
  strncpy(valid, original, n);

  for (i=0; i < n; i++)
  {
    if ( (valid[i] > 122)
      || (valid[i] < 32)
      || (strchr("!\"#$%&'()*+,-.:;<=>?@[\\]^`/ \n\r\t", valid[i]) != NULL) )
    {
      if (i) valid[i] = '_'; else valid[i] = 'm';
    }
  }
  valid[i] = '\0';

  return(valid);
} /* mcvalid_name */

#if defined(NL_ARGMAX) || defined(WIN32)
/*******************************************************************************
* pfprintf: just as fprintf, but with (char *)fmt_args being the list of arg type
*   Needed as the vfprintf is not correctly handled on some platforms.
*   1- look for the maximum %d$ field in fmt
*   2- look for all %d$ fields up to max in fmt and set their type (next alpha)
*   3- retrieve va_arg up to max, and save pointer to arg in local arg array
*   4- use strchr to split around '%' chars, until all pieces are written
*******************************************************************************/
static int pfprintf(FILE *f, char *fmt, char *fmt_args, ...)
{
  #define MyNL_ARGMAX 50
  char  *fmt_pos;

  char *arg_char[MyNL_ARGMAX];
  int   arg_int[MyNL_ARGMAX];
  long  arg_long[MyNL_ARGMAX];
  double arg_double[MyNL_ARGMAX];

  char *arg_posB[MyNL_ARGMAX];  /* position of '%' */
  char *arg_posE[MyNL_ARGMAX];  /* position of '$' */
  char *arg_posT[MyNL_ARGMAX];  /* position of type */

  int   arg_num[MyNL_ARGMAX];   /* number of argument (between % and $) */
  int   this_arg=0;
  int   arg_max=0;
  va_list ap;

  if (!f || !fmt_args || !fmt) return(-1);
  for (this_arg=0; this_arg<MyNL_ARGMAX;  arg_num[this_arg++] =0); this_arg = 0;
  fmt_pos = fmt;
  while(1)  /* analyse the format string 'fmt' */
  {
    char *tmp;

    arg_posB[this_arg] = (char *)strchr(fmt_pos, '%');
    tmp = arg_posB[this_arg];
    if (tmp)
    {
      arg_posE[this_arg] = (char *)strchr(tmp, '$');
      if (arg_posE[this_arg] && tmp[1] != '%')
      {
        char  this_arg_chr[10];
        char  printf_formats[]="dliouxXeEfgGcs\0";

        /* extract positional argument index %*$ in fmt */
        strncpy(this_arg_chr, arg_posB[this_arg]+1, arg_posE[this_arg]-arg_posB[this_arg]-1);
        this_arg_chr[arg_posE[this_arg]-arg_posB[this_arg]-1] = '\0';
        arg_num[this_arg] = atoi(this_arg_chr);
        if (arg_num[this_arg] <=0 || arg_num[this_arg] >= MyNL_ARGMAX)
          return(-fprintf(stderr,"pfprintf: invalid positional argument number (<=0 or >=%i) %s.\n", MyNL_ARGMAX, arg_posB[this_arg]));
        /* get type of positional argument: follows '%' -> arg_posE[this_arg]+1 */
        fmt_pos = arg_posE[this_arg]+1;
        if (!strchr(printf_formats, fmt_pos[0]))
          return(-fprintf(stderr,"pfprintf: invalid positional argument type (%c != expected %c).\n", fmt_pos[0], fmt_args[arg_num[this_arg]-1]));
        if (fmt_pos[0] == 'l' && fmt_pos[1] == 'i') fmt_pos++;
        arg_posT[this_arg] = fmt_pos;
        /* get next argument... */
        this_arg++;
      }
      else
      {
        if  (tmp[1] != '%')
          return(-fprintf(stderr,"pfprintf: must use only positional arguments (%s).\n", arg_posB[this_arg]));
        else fmt_pos = arg_posB[this_arg]+2;  /* found %% */
      }
    } else
      break;  /* no more % argument */
  }
  arg_max = this_arg;
  /* get arguments from va_arg list, according to their type */
  va_start(ap, fmt_args);
  for (this_arg=0; this_arg<strlen(fmt_args); this_arg++)
  {

    switch(fmt_args[this_arg])
    {
      case 's':                       /* string */
              arg_char[this_arg] = va_arg(ap, char *);
              break;
      case 'd':
      case 'i':
      case 'c':                     /* int */
              arg_int[this_arg] = va_arg(ap, int);
              break;
      case 'l':                       /* int */
              arg_long[this_arg] = va_arg(ap, long int);
              break;
      case 'f':
      case 'g':
      case 'G':                      /* double */
              arg_double[this_arg] = va_arg(ap, double);
              break;
      default: fprintf(stderr,"pfprintf: argument type is not implemented (arg %%%i$ type %c).\n", this_arg+1, fmt_args[this_arg]);
    }
  }
  va_end(ap);
  /* split fmt string into bits containing only 1 argument */
  fmt_pos = fmt;
  for (this_arg=0; this_arg<arg_max; this_arg++)
  {
    char *fmt_bit;
    int   arg_n;

    if (arg_posB[this_arg]-fmt_pos>0)
    {
      fmt_bit = (char*)malloc(arg_posB[this_arg]-fmt_pos+10);
      if (!fmt_bit) return(-fprintf(stderr,"pfprintf: not enough memory.\n"));
      strncpy(fmt_bit, fmt_pos, arg_posB[this_arg]-fmt_pos);
      fmt_bit[arg_posB[this_arg]-fmt_pos] = '\0';
      fprintf(f, fmt_bit); /* fmt part without argument */
    } else
    {
      fmt_bit = (char*)malloc(10);
      if (!fmt_bit) return(-fprintf(stderr,"pfprintf: not enough memory.\n"));
    }
    arg_n = arg_num[this_arg]-1; /* must be >= 0 */
    strcpy(fmt_bit, "%");
    strncat(fmt_bit, arg_posE[this_arg]+1, arg_posT[this_arg]-arg_posE[this_arg]);
    fmt_bit[arg_posT[this_arg]-arg_posE[this_arg]+1] = '\0';

    switch(fmt_args[arg_n])
    {
      case 's': fprintf(f, fmt_bit, arg_char[arg_n]);
                break;
      case 'd':
      case 'i':
      case 'c':                      /* int */
              fprintf(f, fmt_bit, arg_int[arg_n]);
              break;
      case 'l':                       /* long */
              fprintf(f, fmt_bit, arg_long[arg_n]);
              break;
      case 'f':
      case 'g':
      case 'G':                       /* double */
              fprintf(f, fmt_bit, arg_double[arg_n]);
              break;
    }
    fmt_pos = arg_posT[this_arg]+1;
    if (this_arg == arg_max-1)
    { /* add eventual leading characters for last parameter */
      if (fmt_pos < fmt+strlen(fmt))
        fprintf(f, "%s", fmt_pos);
    }
    if (fmt_bit) free(fmt_bit);

  }
  return(this_arg);
}
#else
static int pfprintf(FILE *f, char *fmt, char *fmt_args, ...)
{ /* wrapper to standard fprintf when the library function is OK (linux) */
  va_list ap;
  int tmp;

  va_start(ap, fmt_args);
  tmp=vfprintf(f, fmt, ap);
  va_end(ap);
  return(tmp);
}
#endif

/*******************************************************************************
* mcfile_header: output header/footer using specific file format.
*   outputs, in file 'name' having preallocated 'f' handle, the format Header
*   'part' may be 'header' or 'footer' depending on part to write
*   if name == NULL, ignore function (no header/footer output)
*******************************************************************************/
static int mcfile_header(FILE *f, struct mcformats_struct format, char *part, char *pre, char *name, char *parent)
{
  char user[64];
  char date[64];
  char *HeadFoot;
  long date_l; /* date as a long number */
  time_t t;
  char valid_parent[256];
  char instrname[256];
  char file[256];

  if(!f)
    return (-1);

  time(&t);

  if (part && !strcmp(part,"footer"))
  {
    HeadFoot = format.Footer;
    date_l = (long)t;
  }
  else
  {
    HeadFoot = format.Header;
    date_l = mcstartdate;
  }
  t = (time_t)date_l;

  if (!strlen(HeadFoot) || (!name)) return (-1);

  sprintf(file,"%s",name);
  sprintf(user,"%s on %s",
        getenv("USER") ? getenv("USER") : "mcstas",
        getenv("HOST") ? getenv("HOST") : "localhost");
  if (strstr(format.Name, "HTML")) {
    sprintf(instrname,"%s", mcinstrument_source);
    mcvalid_name(valid_parent, mcinstrument_name, VALID_NAME_LENGTH);
  } else {
    sprintf(instrname,"%s (%s)", mcinstrument_name, mcinstrument_source);
    if (parent && strlen(parent)) mcvalid_name(valid_parent, parent, VALID_NAME_LENGTH);
    else strcpy(valid_parent, "root");
  }
  strncpy(date, ctime(&t), 64);
  if (strlen(date)) date[strlen(date)-1] = '\0';

#ifdef USE_NEXUS
  if (strstr(format.Name, "NeXus")) {
    if(mcnxfile_header(mcnxHandle, part,
    pre,                  /* %1$s  PRE  */
    instrname,            /* %2$s  SRC  */
    file,                 /* %3$s  FIL  */
    format.Name,          /* %4$s  FMT  */
    date,                 /* %5$s  DAT  */
    user,                 /* %6$s  USR  */
    valid_parent,         /* %7$s  PAR  */
    date_l) == NX_ERROR) {
      fprintf(stderr, "Error: writing NeXus header file %s (mcfile_header)\n", file);
      return(-1);
    } else return(1); }
  else
#endif
  return(pfprintf(f, HeadFoot, "sssssssl",
    pre,                  /* %1$s  PRE  */
    instrname,            /* %2$s  SRC  */
    file,                 /* %3$s  FIL  */
    format.Name,          /* %4$s  FMT  */
    date,                 /* %5$s  DAT  */
    user,                 /* %6$s  USR  */
    valid_parent,         /* %7$s  PAR  */
    date_l));             /* %8$li DATL */
} /* mcfile_header */

/*******************************************************************************
* mcfile_tag: output tag/value using specific file format.
*   outputs, in file with 'f' handle, a tag/value pair.
*   if name == NULL, ignore function (no section definition)
*******************************************************************************/
static int mcfile_tag(FILE *f, struct mcformats_struct format, char *pre, char *section, char *name, char *value)
{
  char valid_section[256];
  char valid_name[256];
  int i;

  if (!strlen(format.AssignTag) || (!name) || (!f)) return(-1);

  mcvalid_name(valid_section, section, VALID_NAME_LENGTH);
  mcvalid_name(valid_name, name, VALID_NAME_LENGTH);

  /* remove quote chars in values */
  if (strstr(format.Name, "Scilab") || strstr(format.Name, "Matlab") || strstr(format.Name, "IDL"))
    for(i = 0; i < strlen(value); i++) {
      if (value[i] == '"' || value[i] == '\'')   value[i] = ' ';
      if (value[i] == '\n'  || value[i] == '\r') value[i] = ';';
    }
#ifdef USE_NEXUS
  if (strstr(format.Name, "NeXus")) {
    if(mcnxfile_tag(mcnxHandle, pre, valid_section, name, value) == NX_ERROR) {
      fprintf(stderr, "Error: writing NeXus tag file %s/%s=%s (mcfile_tag)\n", section, name, value);
      return(-1);
    } else return(1); }
  else
#endif
  return(pfprintf(f, format.AssignTag, "ssss",
    pre,          /* %1$s PRE */
    valid_section,/* %2$s SEC */
    valid_name,   /* %3$s NAM */
    value));      /* %4$s VAL */
} /* mcfile_tag */

/*******************************************************************************
* mcfile_section: output section start/end using specific file format.
*   outputs, in file 'name' having preallocated 'f' handle, the format Section.
*   'part' may be 'begin' or 'end' depending on section part to write
*   'type' may be e.g. 'instrument','simulation','component','data'
*   if name == NULL, ignore function (no section definition)
*   the prefix 'pre' is automatically indented/un-indented (pre-allocated !)
*******************************************************************************/
static int mcfile_section(FILE *f, struct mcformats_struct format, char *part, char *pre, char *name, char *type, char *parent, int level)
{
  char *Section;
  char valid_name[256];
  char valid_parent[256];
  int  ret;

  if(!f && !strstr(format.Name, "NeXus")) return (-1);

  if (part && !strcmp(part,"end")) Section = format.EndSection;
  else Section = format.BeginSection;

  if (!strlen(Section) || (!name)) return (-1);

  if (strcmp(part,"header") && strstr(format.Name, "no header")) return (-1);
  if (strcmp(part,"footer") && strstr(format.Name, "no footer")) return (-1);

  mcvalid_name(valid_name, name, VALID_NAME_LENGTH);
  if (parent && strlen(parent)) mcvalid_name(valid_parent, parent, VALID_NAME_LENGTH);
  else strcpy(valid_parent, "root");

  if (!strcmp(part,"end") && pre)       /* un-indent */
  {
    if (strlen(pre) > 2) pre[strlen(pre)-2]='\0';
  }
#ifdef USE_NEXUS
  if (strstr(format.Name, "NeXus")) {
    if (mcnxfile_section(mcnxHandle,part,
      pre, type, name, valid_name, parent, valid_parent, level) == NX_ERROR) {
      fprintf(stderr, "Error: writing NeXus section %s/%s=NX%s (mcfile_section)\n", parent, name, type);
      ret=-1;
    } else ret=1; }
  else
#endif
  ret = pfprintf(f, Section, "ssssssi",
    pre,          /* %1$s  PRE  */
    type,         /* %2$s  TYP  */
    name,         /* %3$s  NAM  */
    valid_name,   /* %4$s  VNA  */
    parent,       /* %5$s  PAR  */
    valid_parent, /* %6$s  VPA  */
    level);       /* %7$i  LVL */

  if (!strcmp(part,"begin"))
  {
    if (pre) strcat(pre,"  ");  /* indent */
    if (name && strlen(name))
      mcfile_tag(f, format, pre, name, "name", name);
    if (parent && strlen(parent))
      mcfile_tag(f, format, pre, name, "parent", parent);
  }

  return(ret);
} /* mcfile_section */

/*******************************************************************************
* mcinfo_instrument: output instrument info
*******************************************************************************/
static void mcinfo_instrument(FILE *f, struct mcformats_struct format,
  char *pre, char *name)
{
  char Value[1300] = "";
  int  i;

  if (!f) return;

  for(i = 0; i < mcnumipar; i++)
  {
    char ThisParam[256];
    if (strlen(mcinputtable[i].name) > 200) break;
    sprintf(ThisParam, " %s(%s)", mcinputtable[i].name,
            (*mcinputtypes[mcinputtable[i].type].parminfo)
                (mcinputtable[i].name));
    strcat(Value, ThisParam);
    if (strlen(Value) > CHAR_BUF_LENGTH) break;
  }
  mcfile_tag(f, format, pre, name, "Parameters", Value);
  mcfile_tag(f, format, pre, name, "Source", mcinstrument_source);
  mcfile_tag(f, format, pre, name, "Trace_enabled", mctraceenabled ? "yes" : "no");
  mcfile_tag(f, format, pre, name, "Default_main", mcdefaultmain ? "yes" : "no");
  mcfile_tag(f, format, pre, name, "Embedded_runtime",
#ifdef MC_EMBEDDED_RUNTIME
         "yes"
#else
         "no"
#endif
         );
} /* mcinfo_instrument */

/*******************************************************************************
* mcinfo_instrument: output simulation info
*******************************************************************************/
void mcinfo_simulation(FILE *f, struct mcformats_struct format,
  char *pre, char *name)
{
  int i;
  double run_num, ncount;
  char Value[256];

  if (!f) return;

  run_num = mcget_run_num();
  ncount  = 
#ifdef USE_MPI
    mpi_node_count * 
#endif
    mcget_ncount();
  
  if (run_num == 0 || run_num == ncount) sprintf(Value, "%g", ncount);
  else sprintf(Value, "%g/%g", run_num, ncount);
  mcfile_tag(f, format, pre, name, "Ncount", Value);
  mcfile_tag(f, format, pre, name, "Trace", mcdotrace ? "yes" : "no");
  mcfile_tag(f, format, pre, name, "Gravitation", mcgravitation ? "yes" : "no");
  if(mcseed)
  {
    sprintf(Value, "%ld", mcseed);
    mcfile_tag(f, format, pre, name, "Seed", Value);
  }
  if (strstr(format.Name, "McStas"))
  {
    for(i = 0; i < mcnumipar; i++)
    {
      if (mcrun_num || (mcinputtable[i].val && strlen(mcinputtable[i].val))) {
        if (mcinputtable[i].par == NULL) {
          strncpy(Value, (mcinputtable[i].val ? mcinputtable[i].val : ""), 256);
        } else (*mcinputtypes[mcinputtable[i].type].printer)(Value, mcinputtable[i].par);
        fprintf(f, "%sParam: %s=%s", pre, mcinputtable[i].name, Value);
        fprintf(f, "\n");
      }
    }
  }
  else
  {
    mcfile_section(f, format, "begin", pre, "parameters", "parameters", name, 3);
    for(i = 0; i < mcnumipar; i++)
    {
      if (mcinputtable[i].par == NULL)
        strncpy(Value, (mcinputtable[i].val ? mcinputtable[i].val : ""), 256);
      else (*mcinputtypes[mcinputtable[i].type].printer)(Value, mcinputtable[i].par);
      mcfile_tag(f, format, pre, "parameters", mcinputtable[i].name, Value);
    }
    mcfile_section(f, format, "end", pre, "parameters", "parameters", name, 3);
  }
} /* mcinfo_simulation */

/*******************************************************************************
* mcinfo_data: output data info, computes basic stats.
*******************************************************************************/
static void mcinfo_data(FILE *f, struct mcformats_struct format,
  char *pre, char *parent, char *title,
  int m, int n, int p,
  char *xlabel, char *ylabel, char *zlabel,
  char *xvar, char *yvar, char *zvar,
  double *x1, double *x2, double *y1, double *y2, double *z1, double *z2,
  char *filename,
  double *p0, double *p1, double *p2, char istransposed, Coords posa)
{
  char type[256];
  char stats[256];
  char vars[256];
  char signal[256];
  char values[256];
  char limits[256];
  char lim_field[10];
  char c[32];
  double run_num, ncount;
  char ratio[256];
  char pos[256];

  double sum_xz  = 0;
  double sum_yz  = 0;
  double sum_z   = 0;
  double sum_y   = 0;
  double sum_x   = 0;
  double sum_x2z = 0;
  double sum_y2z = 0;
  double min_z   = 0;
  double max_z   = 0;
  double fmon_x=0, smon_x=0, fmon_y=0, smon_y=0, mean_z=0;
  double Nsum=0;
  double P2sum=0;

  int    i,j;

  if (!f || m*n*p == 0) return;

  if (p1)
  {
    min_z   = p1[0];
    max_z   = min_z;
    for(j = 0; j < n*p; j++)
    {
      for(i = 0; i < m; i++)
      {
        double x,y,z;
        double N, E;
        long index;

        if (!istransposed) index = i*n*p + j;
        else index = i+j*m;
        if (p0) N = p0[index];
        if (p2) E = p2[index];

        if (m) x = *x1 + (i + 0.5)/m*(*x2 - *x1); else x = 0;
        if (n && p) y = *y1 + (j + 0.5)/n/p*(*y2 - *y1); else y = 0;
        z = p1[index];
        sum_xz += x*z;
        sum_yz += y*z;
        sum_x += x;
        sum_y += y;
        sum_z += z;
        sum_x2z += x*x*z;
        sum_y2z += y*y*z;
        if (z > max_z) max_z = z;
        if (z < min_z) min_z = z;

        Nsum += p0 ? N : 1;
        P2sum += p2 ? E : z*z;
      }
    }
    if (sum_z && n*m*p)
    {
      fmon_x = sum_xz/sum_z;
      fmon_y = sum_yz/sum_z;
      smon_x = sqrt(sum_x2z/sum_z-fmon_x*fmon_x);
      smon_y = sqrt(sum_y2z/sum_z-fmon_y*fmon_y);
      mean_z = sum_z/n/m/p;
    }
  }

  if (abs(m*n*p) == 1)
  { strcpy(type, "array_0d"); strcpy(stats, ""); }
  else if (n == 1 || m == 1)
  { if (m == 1) {m = n; n = 1; }
    sprintf(type, "array_1d(%d)", m);
    sprintf(stats, "X0=%g; dX=%g;", fmon_x, smon_x); }
  else
  { if (strstr(format.Name," scan ")) sprintf(type, "multiarray_1d(%d)", n);
    else if (p == 1) sprintf(type, "array_2d(%d, %d)", m, n);
    else sprintf(type, "array_3d(%d, %d, %d)", m, n, p);
    sprintf(stats, "X0=%g; dX=%g; Y0=%g; dY=%g;", fmon_x, smon_x, fmon_y, smon_y); }
  strcpy(c, "I ");
  if (zvar && strlen(zvar)) strncpy(c, zvar,32);
  else if (yvar && strlen(yvar)) strncpy(c, yvar,32);
  else if (xvar && strlen(xvar)) strncpy(c, xvar,32);
  else strncpy(c, xvar,32);
  if (m == 1 || n == 1) sprintf(vars, "%s %s %s_err N", xvar, c, c);
  else sprintf(vars, "%s %s_err N", c, c);

  run_num = mcget_run_num();
  ncount  = 
#ifdef USE_MPI
    mpi_node_count * 
#endif
    mcget_ncount();
  sprintf(ratio, "%g/%g", run_num, ncount);

  mcfile_tag(f, format, pre, parent, "type", type);
  mcfile_tag(f, format, pre, parent, "Source", mcinstrument_source);
  if (parent) mcfile_tag(f, format, pre, parent, (strstr(format.Name,"McStas") ? "component" : "parent"), parent);
  sprintf(pos, "%g %g %g", posa.x, posa.y, posa.z);
  mcfile_tag(f, format, pre, parent, "position", pos);

  if (title) mcfile_tag(f, format, pre, parent, "title", title);
  mcfile_tag(f, format, pre, parent, "ratio", ratio);
  if (filename) {
    mcfile_tag(f, format, pre, parent, "filename", filename);
    mcfile_tag(f, format, pre, parent, "format", format.Name);
  } else mcfile_tag(f, format, pre, parent, "filename", "");

  if (p1)
  {
    if (n*m*p > 1)
    {
      sprintf(signal, "Min=%g; Max=%g; Mean= %g;", min_z, max_z, mean_z);
      if (m > 1 && n == 1 && p == 1) { *y1 = min_z; *y2 = max_z; *z1=*y1; *z2=*y2; }
      else if (m > 1 && n > 1 && p == 1) { *z1 = min_z; *z2 = max_z;}
    } else strcpy(signal, "");

    mcfile_tag(f, format, pre, parent, "statistics", stats);
    mcfile_tag(f, format, pre, parent,
      strstr(format.Name, "NeXus") ? "Signal" : "signal", signal);

    sprintf(values, "%g %g %g", sum_z, mcestimate_error(Nsum, sum_z, P2sum), Nsum);
    mcfile_tag(f, format, pre, parent, "values", values);
  }
  strcpy(lim_field, "xylimits");
  if (n*m > 1)
  {
    mcfile_tag(f, format, pre, parent, (strstr(format.Name," scan ") ? "xvars" : "xvar"), xvar);
    mcfile_tag(f, format, pre, parent, (strstr(format.Name," scan ") ? "yvars" : "yvar"), yvar);
    mcfile_tag(f, format, pre, parent, "xlabel", xlabel);
    mcfile_tag(f, format, pre, parent, "ylabel", ylabel);
    if ((n == 1 || m == 1 || strstr(format.Name," scan ")) && strstr(format.Name, "McStas"))
    {
      sprintf(limits, "%g %g", *x1, *x2);
      strcpy(lim_field, "xlimits");
    }
    else
    {
      if (!strstr(format.Name," scan ")) {
        mcfile_tag(f, format, pre, parent, "zvar", zvar);
        mcfile_tag(f, format, pre, parent, "zlabel", zlabel);
      }
      sprintf(limits, "%g %g %g %g %g %g", *x1, *x2, *y1, *y2, *z1, *z2);
    }
  } else strcpy(limits, "0 0 0 0 0 0");
  mcfile_tag(f, format, pre, parent, lim_field, limits);
  mcfile_tag(f, format, pre, parent, "variables", strstr(format.Name," scan ") ? zvar : vars);
  /* add warning in case of low statistics or large number of bins in text format mode */
  if (mcestimate_error(Nsum, sum_z, P2sum) > sum_z/4) fprintf(stderr,
    "Warning: file '%s': Low Statistics\n",
    filename);
  else
  if (n*m*p > 1000 && Nsum < n*m*p && Nsum) fprintf(stderr,
    "Warning: file '%s':\n"
    "         Low Statistics (%g events in %dx%dx%d bins).\n",
    filename, Nsum, m,n,p);
  if ( !strstr(format.Name, "binary")
    && (strstr(format.Name, "Scilab") || strstr(format.Name, "Matlab"))
    && (n*m*p > 10000 || m > 1000) ) fprintf(stderr,
      "Warning: file '%s' (%s format)\n"
      "         Large matrices (%dx%dx%d) in text mode may be\n"
      "         slow or fail at import. Prefer binary mode.\n",
      filename, format.Name, m,n,p);
   if (mcDetectorCustomHeader && strlen(mcDetectorCustomHeader)) {
     mcfile_tag(f, format, pre, parent, "custom", mcDetectorCustomHeader);
   }
} /* mcinfo_data */

/*******************************************************************************
* mcsiminfo_init: writes simulation structured description file (mcstas.sim)
*******************************************************************************/
void mcsiminfo_init(FILE *f)
{
#ifdef USE_MPI
  if(mpi_node_rank != mpi_node_root) return;
#endif
  if (mcdisable_output_files) return;
  if (!f && (!mcsiminfo_name || !strlen(mcsiminfo_name))) return;
  /* clear list of opened files to start new save session */
  if (mcopenedfiles && strlen(mcopenedfiles) > 0) strcpy(mcopenedfiles, "");
#ifdef USE_NEXUS
  /* NeXus sim info is the NeXus root file */
  if(strstr(mcformat.Name, "NeXus")) {
    if (mcnxfile_init(mcsiminfo_name, mcformat.Extension,
      strstr(mcformat.Name, "append") || strstr(mcformat.Name, "catenate") ? "a":"w",
      &mcnxHandle) == NX_ERROR) {
      exit(fprintf(stderr, "Error: opening NeXus file %s (mcsiminfo_init)\n", mcsiminfo_name));
    } else mcsiminfo_file = (FILE *)mcsiminfo_name;
  } else
#endif
  if (!f) mcsiminfo_file = mcnew_file(mcsiminfo_name, mcformat.Extension,
    strstr(mcformat.Name, "append") 
      || strstr(mcformat.Name, "catenate")  
      || strstr(mcopenedfiles, mcsiminfo_name) 
    ? "a":"w");
  else mcsiminfo_file = f;
  if(!mcsiminfo_file)
    fprintf(stderr,
            "Warning: could not open simulation description file '%s' (mcsiminfo_init)\n",
            mcsiminfo_name);
  else
  {
    char *pre; /* allocate enough space for indentations */
    int  ismcstas_nx;
    char simname[CHAR_BUF_LENGTH];
    char root[10];

    pre = (char *)malloc(20);
    if (!pre) exit(fprintf(stderr, "Error: insufficient memory (mcsiminfo_init)\n"));
    strcpy(pre, strstr(mcformat.Name, "VRML")
               || strstr(mcformat.Name, "OpenGENIE") ? "# " : "  ");


    ismcstas_nx = (strstr(mcformat.Name, "McStas") || strstr(mcformat.Name, "NeXus"));
    strcpy(root, strstr(mcformat.Name, "XML") ? "root" : "mcstas");
    sprintf(simname, "%s%s%s",
      mcdirname ? mcdirname : ".", MC_PATHSEP_S, mcsiminfo_name);

#ifdef USE_NEXUS
    if (strstr(mcformat.Name, "NeXus")) {
      /* NXentry class */
      char file_time[CHAR_BUF_LENGTH];
      sprintf(file_time, "%s_%li", mcinstrument_name, mcstartdate);
      mcfile_section(mcsiminfo_file, mcformat, "begin", pre, file_time, "entry", root, 1);
    }
#endif

    mcfile_header(mcsiminfo_file, mcformat, "header", pre, simname, root);
#ifdef USE_NEXUS
    if (strstr(mcformat.Name, "NeXus"))
    mcnxfile_section(mcnxHandle,"end_data", NULL, NULL, NULL, NULL, NULL, NULL, 0);
#endif
    /* begin-end instrument */
    mcfile_section(mcsiminfo_file, mcformat, "begin", pre, mcinstrument_name, "instrument", root, 1);
    mcinfo_instrument(mcsiminfo_file, mcformat, pre, mcinstrument_name);
#ifdef USE_NEXUS
    if (strstr(mcformat.Name, "NeXus")) {
      mcnxfile_section(mcnxHandle,"end_data", NULL, NULL, NULL, NULL, NULL, NULL, 0);
      mcnxfile_section(mcnxHandle,"instr_code",
        pre, "instrument", mcinstrument_source, NULL, mcinstrument_name, NULL, 0);
    }
#endif
    if (ismcstas_nx) mcfile_section(mcsiminfo_file, mcformat, "end", pre, mcinstrument_name, "instrument", root, 1);

    /* begin-end simulation */
    mcfile_section(mcsiminfo_file, mcformat, "begin", pre, simname, "simulation", mcinstrument_name, 2);
    mcinfo_simulation(mcsiminfo_file, mcformat, pre, simname);
#ifdef USE_NEXUS
    if (strstr(mcformat.Name, "NeXus"))
    mcnxfile_section(mcnxHandle,"end_data", NULL, NULL, NULL, NULL, NULL, NULL, 0);
#endif
    if (ismcstas_nx) mcfile_section(mcsiminfo_file, mcformat, "end", pre, simname, "simulation", mcinstrument_name, 2);

    free(pre);
  }
} /* mcsiminfo_init */

/*******************************************************************************
* mcsiminfo_close: close simulation file (mcstas.sim)
*******************************************************************************/
void mcsiminfo_close(void)
{
#ifdef USE_MPI
  if(mpi_node_rank != mpi_node_root) return;
#endif
  if (mcdisable_output_files) return;
  if(mcsiminfo_file)
  {
    int  ismcstas_nx;
    char simname[CHAR_BUF_LENGTH];
    char root[10];
    char *pre;

    pre = (char *)malloc(20);
    if (!pre) exit(fprintf(stderr, "Error: insufficient memory (mcsiminfo_close)\n"));
    strcpy(pre, strstr(mcformat.Name, "VRML")
               || strstr(mcformat.Name, "OpenGENIE") ? "# " : "  ");

    ismcstas_nx = (strstr(mcformat.Name, "McStas") || strstr(mcformat.Name, "NeXus"));
    strcpy(root, strstr(mcformat.Name, "XML") ? "root" : "mcstas");
    sprintf(simname, "%s%s%s",
      mcdirname ? mcdirname : ".", MC_PATHSEP_S, mcsiminfo_name);

    if (!ismcstas_nx)
    {
      mcfile_section(mcsiminfo_file, mcformat, "end", pre, simname, "simulation", mcinstrument_name, 2);
      mcfile_section(mcsiminfo_file, mcformat, "end", pre, mcinstrument_name, "instrument", root, 1);
    }
#ifdef USE_NEXUS
    if (strstr(mcformat.Name, "NeXus")) mcfile_section(mcsiminfo_file, mcformat, "end", pre, mcinstrument_name, "entry", root, 1);
#endif
    mcfile_header(mcsiminfo_file, mcformat, "footer", pre, simname, root);
#ifdef USE_NEXUS
    if (strstr(mcformat.Name, "NeXus")) mcnxfile_close(&mcnxHandle);
#endif
    if (mcsiminfo_file != stdout && mcsiminfo_file && !strstr(mcformat.Name, "NeXus")) fclose(mcsiminfo_file);
    mcsiminfo_file = NULL;

    free(pre);
  }
} /* mcsiminfo_close */

/*******************************************************************************
* mcfile_datablock: output a single data block using specific file format.
*   'part' can be 'data','errors','ncount'
*   if y1 == y2 == 0 and McStas format, then stores as a 1D array with [I,E,N]
*   return value: 0=0d/2d, 1=1d
*   when !single_file, create independent data files, with header and data tags
*   if one of the dimensions m,n,p is negative, the data matrix will be written
*   after transposition of m/x and n/y dimensions
*******************************************************************************/
static int mcfile_datablock(FILE *f, struct mcformats_struct format,
  char *pre, char *parent, char *part,
  double *p0, double *p1, double *p2, int m, int n, int p,
  char *xlabel, char *ylabel, char *zlabel, char *title,
  char *xvar, char *yvar, char *zvar,
  double *x1, double *x2, double *y1, double *y2, double *z1, double *z2,
  char *filename, char istransposed, Coords posa)
{
  char *Begin;
  char *End;
  char valid_xlabel[64];
  char valid_ylabel[64];
  char valid_zlabel[64];
  char valid_parent[64];
  FILE *datafile= NULL;
  int  isdata=0;
  int  just_header=0;
  int  i,j, is1d;
  double Nsum=0, Psum=0, P2sum=0;
  char sec[256];
  char isdata_present;
  char israw_data=0; /* raw data=(N,p,p2) instead of (N,P,sigma) */
  struct mcformats_struct dataformat;

  if (strstr(part,"data"))
  { isdata = 1; Begin = format.BeginData; End = format.EndData; }
  if (strstr(part,"errors"))
  { isdata = 2; Begin = format.BeginErrors; End = format.EndErrors; }
  if (strstr(part,"ncount"))
  { isdata = 0; Begin = format.BeginNcount; End = format.EndNcount; }
  if (strstr(part, "begin")) just_header = 1;
  if (strstr(part, "end"))   just_header = 2;

  isdata_present=((isdata==1 && p1) || (isdata==2 && p2) || (isdata==0 && p0));

  is1d = ((m==1 || n==1) && strstr(format.Name,"McStas"));
  mcvalid_name(valid_xlabel, xlabel, 64);
  mcvalid_name(valid_ylabel, ylabel, 64);
  mcvalid_name(valid_zlabel, zlabel, 64);

  if (strstr(format.Name, "McStas") || !filename || strlen(filename) == 0)
    mcvalid_name(valid_parent, parent, VALID_NAME_LENGTH);
  else mcvalid_name(valid_parent, filename, VALID_NAME_LENGTH);

#ifdef USE_NEXUS
  if (strstr(format.Name, "NeXus")) {
    /* istransposed==1 : end NeXus data only with last output slab */
    if (strstr(part,"data") && !strstr(format.Name,"no header")) { /* writes attributes in information SDS */
      mcinfo_data(mcsiminfo_file, format, pre, valid_parent, title, m, n, p,
                  xlabel, ylabel, zlabel, xvar, yvar, zvar,
                  x1, x2, y1, y2, z1, z2, filename, p0, p1, p2,
                  0, posa);
      mcnxfile_section(mcnxHandle,"end_data", NULL, filename, NULL, NULL, NULL, NULL, 0);
    }
    if(mcnxfile_datablock(mcnxHandle, part,
      format.Name, valid_parent, filename, xlabel, valid_xlabel, ylabel, valid_ylabel, zlabel, valid_zlabel, title, xvar, yvar, zvar, abs(m), abs(n), abs(p), *x1, *x2, *y1, *y2, *z1, *z2, p0, p1, p2) == NX_ERROR) {
      fprintf(stderr, "Error: writing NeXus data %s/%s (mcfile_datablock)\n", parent, filename);
    }
    return(0); }
#endif

  if (strstr(format.Name, " raw")) israw_data = 1;

  /* if normal or begin and part == data: output info_data (sim/data_file) */
  if (isdata == 1 && just_header != 2 && f)
  {
    if(!strstr(format.Name, "no header")) {
      mcinfo_data(f, format, pre, valid_parent, title, m, n, p,
                  xlabel, ylabel, zlabel, xvar, yvar, zvar,
                  x1, x2, y1, y2, z1, z2, filename, p0, p1, p2,
                  istransposed, posa);
    }
  }

  /* if normal or begin: begin part (sim/data file) */
  if (strlen(Begin) && just_header != 2 && f) {
    pfprintf(f, Begin, "sssssssssssssiiigggggg",
      pre,          /* %1$s   PRE  */
      valid_parent, /* %2$s   PAR  */
      filename,     /* %3$s   FIL  */
      xlabel,       /* %4$s   XLA  */
      valid_xlabel, /* %5$s   XVL  */
      ylabel,       /* %6$s   YLA  */
      valid_ylabel, /* %7$s   YVL  */
      zlabel,       /* %8$s   ZLA  */
      valid_zlabel, /* %9$s   ZVL  */
      title,        /* %10$s  TITL */
      xvar,         /* %11$s  XVAR */
      yvar,         /* %12$s  YVAR */
      zvar,         /* %13$s  ZVAR */
      m,            /* %14$i  MDIM */
      n,            /* %15$i  NDIM */
      p,            /* %16$i  PDIM */
      *x1,           /* %17$g  XMIN */
      *x2,           /* %18$g  XMAX */
      *y1,           /* %19$g  YMIN */
      *y2,           /* %20$g  YMAX */
      *z1,           /* %21$g  ZMIN */
      *z2);          /* %22$g  ZMAX */
  }
 /* if normal, and !single:
  *   open datafile,
  *   if !ascii_only
  *     if data: write file header,
  *     call datablock part+header(begin)
  * else data file = f
  */
  dataformat=format;
  if (!mcsingle_file && just_header == 0)
  {
    /* if data: open new file for data else append for error/ncount */
    if (filename) {
      char mode[10];

      strcpy(mode,
             (isdata != 1 || strstr(format.Name, "no header")
              || strstr(format.Name, "append") 
              || strstr(format.Name, "catenate") 
              || strstr(mcopenedfiles, filename) ?
             "a" : "w"));
      if (strstr(format.Name, "binary")) strcat(mode, "b");
      if (mcformat_data.Name) dataformat = mcformat_data;
      datafile = mcnew_file(filename, dataformat.Extension, mode);
    } else datafile = NULL;
    /* special case of IDL: can not have empty vectors. Init to 'external' */
    if (strstr(format.Name, "IDL") && f) fprintf(f, "'external'");
    /* if data, start with root header plus tags of parent data */
    if (datafile && !mcascii_only)
    {
      char *new_pre;
      char *mode;
      new_pre = (char *)malloc(20);
      mode    = (char *)malloc(20);
      if (!new_pre || !mode) exit(fprintf(stderr, "Error: insufficient memory (mcfile_datablock)\n"));
      strcpy(new_pre, (strstr(dataformat.Name, "McStas")
               || strstr(dataformat.Name, "VRML")
               || strstr(dataformat.Name, "OpenGENIE") ? "# " : ""));

      if (isdata == 1) {
        if(!strstr(format.Name, "no header"))
          {
            mcfile_header(datafile, dataformat, "header", new_pre,
                          filename, valid_parent);
            mcinfo_simulation(datafile, dataformat,
                              new_pre, valid_parent);
          }
      }
      sprintf(mode, "%s begin", part);
      /* write header+data block begin tags into datafile */
      mcfile_datablock(datafile, dataformat, new_pre,
          valid_parent, mode,
          p0, p1, p2, m, n, p,
          xlabel,  ylabel, zlabel, title,
          xvar, yvar, zvar,
          x1, x2, y1, y2, z1, z2, filename, istransposed, posa);
      free(mode); free(new_pre);
    }
  }
  else if (just_header == 0)
  {
    if (strstr(format.Name, "McStas") && abs(m*n*p)>1 && f)
    {
      if (is1d) sprintf(sec,"array_1d(%d)", m);
      else if (p==1) sprintf(sec,"array_2d(%d,%d)", m,n);
      else sprintf(sec,"array_3d(%d,%d,%d)", m,n,p);
      fprintf(f,"%sbegin %s\n", pre, sec);
      datafile = f; dataformat=format;
    }
    if (mcsingle_file) { datafile = f; dataformat=format; }
  }

  /* if normal: [data] in data file */
  /* do loops: 2 loops on m,n. */
  if (just_header == 0)
  {
    char eol_char[3];
    int  isIDL, isPython;
    int  isBinary=0;

    if (strstr(format.Name, "binary")) isBinary=1;
    if (strstr(format.Name, "float"))  isBinary=1;
    else if (strstr(format.Name, "double")) isBinary=2;
    isIDL    = (strstr(format.Name, "IDL") != NULL);
    isPython = (strstr(format.Name, "Python") != NULL);
    if (isIDL) strcpy(eol_char,"$\n"); else strcpy(eol_char,"\n");

    if (datafile && !isBinary)
    for(j = 0; j < n*p; j++)  /* loop on rows(y) */
    {
      for(i = 0; i < m; i++)  /* write all columns (x) */
      {
        double I=0, E=0, N=0;
        double value=0;
        long index;

        if (!istransposed) index = i*n*p + j;
        else index = i+j*m;
        if (p0) N = p0[index];
        if (p1) I = p1[index];
        if (p2) E = p2[index];

        Nsum += p0 ? N : 1;
        Psum += I;
        P2sum += p2 ? E : I*I;

        if (p0 && p1 && p2 && !israw_data) E = mcestimate_error(N,I,E);
        if(isdata_present)
        {
          if (is1d)
          {
            double x;
            x = *x1+(*x2-*x1)*(index+0.5)/(abs(m*n*p));
            if (abs(m*n*p) > 1) fprintf(datafile, "%g %g %g %g\n", x, I, E, N);
          }
          else
          {
            if (isdata == 1) value = I;
            else if (isdata == 0) value = N;
            else if (isdata == 2) value = E;
            fprintf(datafile, "%g", value);
            if ((isIDL || isPython) && ((i+1)*(j+1) < abs(m*n*p))) fprintf(datafile, ",");
            else fprintf(datafile, " ");
          }
        }
      }
      if (isdata_present && !is1d) fprintf(datafile, "%s", eol_char);
    } /* end 2 loops if not Binary */
    if (datafile && isBinary)
    {
      double *d=NULL;
      if (isdata==1) d=p1;
      else if (isdata==2) d=p2;
      else if (isdata==0) d=p0;

      if (d && isBinary == 1)  /* float */
      {
        float *s;
        s = (float*)malloc(abs(m*n*p)*sizeof(float));
        if (s)
        {
          long    i, count;
          for (i=0; i<abs(m*n*p); i++)
            { if (isdata != 2 || israw_data) s[i] = (float)d[i];
              else s[i] = (float)mcestimate_error(p0[i],p1[i],p2[i]); }
            count = fwrite(s, sizeof(float), abs(m*n*p), datafile);
          if (count != abs(m*n*p)) fprintf(stderr, "McStas: error writing float binary file '%s' (%li instead of %li, mcfile_datablock)\n", filename,count, (long)abs(m*n*p));
          free(s);
        } else fprintf(stderr, "McStas: Out of memory for writing %li float binary file '%s' (mcfile_datablock)\n", (long)abs(m*n*p)*sizeof(float), filename);
      }
      else if (d && isBinary == 2)  /* double */
      {
        long count;
        double *s=NULL;
        if (isdata == 2 && !israw_data)
        {
          s = (double*)malloc(abs(m*n*p)*sizeof(double));
          if (s) { long i;
            for (i=0; i<abs(m*n*p); i++)
              s[i] = (double)mcestimate_error(p0[i],p1[i],p2[i]);
            d = s;
          }
          else fprintf(stderr, "McStas: Out of memory for writing %li 'errors' part of double binary file '%s' (mcfile_datablock)\n", (long)abs(m*n*p)*sizeof(double), filename);
        }
        count = fwrite(d, sizeof(double), abs(m*n*p), datafile);
        if (isdata == 2 && s) free(s);
        if (count != abs(m*n*p)) fprintf(stderr, "McStas: error writing double binary file '%s' (%li instead of %li, mcfile_datablock)\n", filename,count, (long)abs(m*n*p));
      }
    } /* end if Binary */
  }
  if (strstr(format.Name, "McStas") || !filename || strlen(filename) == 0)
    mcvalid_name(valid_parent, parent, VALID_NAME_LENGTH);
  else mcvalid_name(valid_parent, filename, VALID_NAME_LENGTH);
  /* if normal or end: end_data */
  if (strlen(End) && just_header != 1 && f) {
    pfprintf(f, End, "sssssssssssssiiigggggg",
      pre,          /* %1$s   PRE  */
      valid_parent, /* %2$s   PAR  */
      filename,     /* %3$s   FIL  */
      xlabel,       /* %4$s   XLA  */
      valid_xlabel, /* %5$s   XVL  */
      ylabel,       /* %6$s   YLA  */
      valid_ylabel, /* %7$s   YVL  */
      zlabel,       /* %8$s   ZLA  */
      valid_zlabel, /* %9$s   ZVL  */
      title,        /* %10$s  TITL */
      xvar,         /* %11$s  XVAR */
      yvar,         /* %12$s  YVAR */
      zvar,         /* %13$s  ZVAR */
      m,            /* %14$i  MDIM */
      n,            /* %15$i  NDIM */
      p,            /* %16$i  PDIM */
      *x1,           /* %17$g  XMIN */
      *x2,           /* %18$g  XMAX */
      *y1,           /* %19$g  YMIN */
      *y2,           /* %20$g  YMAX */
      *z1,           /* %21$g  ZMIN */
      *z2);          /* %22$g  ZMAX */
  }

 /* if normal and !single and datafile:
  *   datablock part+footer
  *   write file footer
  *   close datafile
  */
  if (!mcsingle_file && just_header == 0)
  {
    char *mode;
    char *new_pre;

    new_pre = (char *)malloc(20);
    mode    = (char *)malloc(20);
    if (!new_pre || !mode) exit(fprintf(stderr, "Error: insufficient memory (mcfile_datablock)\n"));

    strcpy(new_pre, (strstr(dataformat.Name, "McStas")
               || strstr(dataformat.Name, "VRML")
               || strstr(dataformat.Name, "OpenGENIE") ? "# " : ""));

    if (datafile && datafile != f && !mcascii_only)
    {
      sprintf(mode, "%s end", part);
      /* write header+data block end tags into datafile */
      mcfile_datablock(datafile, dataformat, new_pre,
          valid_parent, mode,
          p0, p1, p2, m, n, p,
          xlabel,  ylabel, zlabel, title,
          xvar, yvar, zvar,
          x1, x2, y1, y2, z1, z2, filename, istransposed, posa);
      if ((isdata == 1 && is1d) || strstr(part,"ncount") || !p0 || !p2) /* either ncount, or 1d */
        if(!strstr(format.Name, "no footer"))
          mcfile_header(datafile, dataformat, "footer", new_pre,
                        filename, valid_parent);
    }
    if (datafile && datafile != f) fclose(datafile);
    free(mode); free(new_pre);
  }
  else
  {
    if (strstr(format.Name, "McStas") && just_header == 0 && abs(m*n*p) > 1)
      fprintf(f,"%send %s\n", pre, sec);
  }

  /* set return value */
  return(is1d);
} /* mcfile_datablock */

/*******************************************************************************
* mcfile_data: output data/errors/ncounts using specified file format.
*   if McStas 1D then data is stored. f is the simfile handle or NULL.
*   as a long 1D array [p0, p1, p2] to reorder -> don't output err/ncount again.
*   if p1 or p2 is NULL then skip that part.
*******************************************************************************/
static int mcfile_data(FILE *f, struct mcformats_struct format,
  char *pre, char *parent,
  double *p0, double *p1, double *p2, int m, int n, int p,
  char *xlabel, char *ylabel, char *zlabel, char *title,
  char *xvar, char *yvar, char *zvar,
  double ox1, double ox2, double oy1, double oy2, double oz1, double oz2,
  char *filename, char istransposed, Coords posa)
{
  int is1d;
  double x2, x1, y2, y1, z2, z1;

  x1=ox1; y1=oy1; z1=oz1;
  x2=ox2; y2=oy2; z2=oz2;

  /* return if f,n,m,p1 NULL */
  if ((m*n*p == 0) || !p1) return (-1);
  /* output data block */
  is1d = mcfile_datablock(f, format, pre, parent, "data",
    p0, p1, p2, m, n, p,
    xlabel,  ylabel, zlabel, title,
    xvar, yvar, zvar,
    &x1, &x2, &y1, &y2, &z1, &z2, filename, istransposed, posa);
  /* return if 1D data */
  if (is1d) return(is1d);
  /* output error block and p2 non NULL */
  if (p0 && p2) mcfile_datablock(f, format, pre, parent, "errors",
    p0, p1, p2, m, n, p,
    xlabel,  ylabel, zlabel, title,
    xvar, yvar, zvar,
    &x1, &x2, &y1, &y2, &z1, &z2, filename, istransposed, posa);
  /* output ncount block and p0 non NULL */
  if (p0 && p2) mcfile_datablock(f, format, pre, parent, "ncount",
    p0, p1, p2, m, n, p,
    xlabel,  ylabel, zlabel, title,
    xvar, yvar, zvar,
    &x1, &x2, &y1, &y2, &z1, &z2, filename, istransposed, posa);

  return(is1d);
} /* mcfile_data */

double mcdetector_out(char *cname, double p0, double p1, double p2, char *filename)
{
  printf("Detector: %s_I=%g %s_ERR=%g %s_N=%g",
         cname, p1, cname, mcestimate_error(p0,p1,p2), cname, p0);
  if(filename && strlen(filename))
    printf(" \"%s\"", filename);
  printf("\n");
  return(p0);
}

/*******************************************************************************
* mcdetector_out_012D: main output function, works for 0d, 1d, 2d data
*   parent is the component name. Handles MPI stuff.
*******************************************************************************/
static double mcdetector_out_012D(struct mcformats_struct format,
  char *parent, char *title,
  int m, int n,  int p,
  char *xlabel, char *ylabel, char *zlabel,
  char *xvar, char *yvar, char *zvar,
  double x1, double x2, double y1, double y2, double z1, double z2,
  char *filename_orig,
  double *p0, double *p1, double *p2,
  Coords posa)
{
  char simname[512];
  int i,j;
  double Nsum=0, Psum=0, P2sum=0;
  FILE *simfile_f=NULL;
  char istransposed=0;
  char *pre;
  char *filename=NULL;

#ifdef USE_MPI
  int mpi_event_list;
#endif /* !USE_MPI */

  if (!p1 || (p1 && abs(m*n*p) > 1 && (!filename_orig || !strlen(filename_orig)))) return(0);

  pre = (char *)malloc(20);
  if (!pre) exit(fprintf(stderr, "Error: insufficient memory (mcdetector_out_012D)\n"));
  strcpy(pre, strstr(format.Name, "VRML")
           || strstr(format.Name, "OpenGENIE") ? "# " : "");
  if (filename_orig && abs(m*n*p) > 1) {
    filename = (char *)malloc(CHAR_BUF_LENGTH);
    if (!filename) exit(fprintf(stderr, "Error: insufficient memory (mcdetector_out_012D)\n"));
    strcpy(filename, filename_orig);
    if (!strchr(filename, '.') && !strstr(format.Name, "NeXus"))
    { /* add extension to file name if it is missing and not NeXus  */
      strcat(filename,".");
      if (mcformat_data.Extension) strcat(filename,mcformat_data.Extension);
      else strcat(filename,mcformat.Extension);
    }
  }
  fflush(NULL);

#ifdef USE_MPI
  mpi_event_list = (strstr(format.Name," list ") != NULL);

  if (!mpi_event_list && mpi_node_count > 1) {
    /* we save additive data: reduce everything */
    if (p0) mc_MPI_Reduce(p0, p0, abs(m*n*p), MPI_DOUBLE, MPI_SUM, mpi_node_root, MPI_COMM_WORLD);
    if (p1) mc_MPI_Reduce(p1, p1, abs(m*n*p), MPI_DOUBLE, MPI_SUM, mpi_node_root, MPI_COMM_WORLD);
    if (p2) mc_MPI_Reduce(p2, p2, abs(m*n*p), MPI_DOUBLE, MPI_SUM, mpi_node_root, MPI_COMM_WORLD);

    /* slaves are done */
    if(mpi_node_rank != mpi_node_root) return 0;
  }
#endif /* USE_MPI */

  if (!strstr(format.Name, "NeXus")) {
    if (m<0 || n<0 || p<0)                istransposed = !istransposed;
    if (strstr(format.Name, "binary"))    istransposed = !istransposed;
    if (strstr(format.Name, "transpose")) istransposed = !istransposed;
    if (istransposed)
    { /* do the swap once for all */
      i=m; m=abs(n); n=abs(i); p=abs(p);
    }
  } else m=abs(m); n=abs(n); p=abs(p);

  if (!strstr(format.Name," list ")) simfile_f = mcsiminfo_file; /* use sim file */
  if (mcdirname)
    sprintf(simname, "%s%s%s", mcdirname, MC_PATHSEP_S, mcsiminfo_name);
  else
    sprintf(simname, "%s%s%s", ".", MC_PATHSEP_S, mcsiminfo_name);

  if (!mcdisable_output_files) {
    MPI_MASTER (
      if (!strstr(format.Name,"NeXus"))
      mcfile_section(simfile_f, format, "begin", pre, parent, "component", simname, 3);
      mcfile_section(simfile_f, format, "begin", pre, filename, "data", parent, 4);
      );
  }

  if (mcDetectorCustomHeader && strlen(mcDetectorCustomHeader)) {
     if (strstr(format.Name, "Octave") || strstr(format.Name, "Matlab"))
       str_rep(mcDetectorCustomHeader, "%PRE", "%   ");
     else if (strstr(format.Name, "IDL"))    str_rep(mcDetectorCustomHeader, "%PRE", ";   ");
     else if (strstr(format.Name, "Scilab")) str_rep(mcDetectorCustomHeader, "%PRE", "//  ");
     else if (strstr(format.Name, "McStas")) str_rep(mcDetectorCustomHeader, "%PRE", "#   ");
     else str_rep(mcDetectorCustomHeader, "%PRE", "    ");
   }

#ifdef USE_MPI
  if (mpi_event_list && mpi_node_count > 1) {
    if (mpi_node_rank != mpi_node_root) {
      /* we save an event list: all slaves send their data to master */
      /* m, n, p must be sent too, since all slaves do not have the same number of events */
      int mnp[3];
      mnp[0] = m; mnp[1] = n; mnp[2] = p;
        
      if (MPI_Send(mnp, 3, MPI_INT, mpi_node_root, 0, MPI_COMM_WORLD)!= MPI_SUCCESS)
        fprintf(stderr, "Warning: node %i to master: MPI_Send mnp list error (mcdetector_out_012D)", mpi_node_rank);
      if (!p1 || mc_MPI_Send(p1, abs(mnp[0]*mnp[1]*mnp[2]), MPI_DOUBLE, mpi_node_root, MPI_COMM_WORLD)!= MPI_SUCCESS)
        fprintf(stderr, "Warning: node %i to master: MPI_Send p1 list error (mcdetector_out_012D)", mpi_node_rank);
      /* slaves are done */
      return 0;
    } else { /* master node list */
      int node_i;
      /* get, then save master and slaves event lists */
      for(node_i=0; node_i<mpi_node_count; node_i++) {
        double *this_p1=NULL; /* buffer to hold the list to save */
        int    mnp[3]={0,0,0};        /* size of this buffer */
        if (node_i != mpi_node_root) { /* get data from slaves */
          if (MPI_Recv(mnp, 3, MPI_INT, node_i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE)!= MPI_SUCCESS)
            fprintf(stderr, "Warning: master from node %i: MPI_Recv mnp list error (mcdetector_out_012D)", node_i);
          this_p1 = (double *)calloc(abs(mnp[0]*mnp[1]*mnp[2]), sizeof(double));
          if (!this_p1 || mc_MPI_Recv(this_p1, abs(mnp[0]*mnp[1]*mnp[2]), MPI_DOUBLE, node_i, MPI_COMM_WORLD)!= MPI_SUCCESS)
            fprintf(stderr, "Warning: master from node %i: MPI_Recv p1 list error (mcdetector_out_012D)", node_i);
        } else {
          this_p1 = p1; 
          mnp[0] = m; mnp[1] = n; mnp[2] = p;
        }
        if (!strstr(format.Name, "NeXus")) { /* not MPI+NeXus format */
          char *formatName_orig = mcformat.Name;  /* copy the pointer position */
          char  formatName[256];
          strcpy(formatName, mcformat.Name);
          if (!strstr(formatName, "append")) strcat(formatName, " append ");
          if (node_i == 1) { /* first slave */
            /* disables header: it has been written by master */
            if (!strstr(formatName, "no header")) strcat(formatName, " no header ");
          }
          char *no_footer = strstr(formatName, "no footer");
          if (node_i == mpi_node_count-1) { /* last node */
            /* we write the last data block: request a footer */
            if (no_footer) strncpy(no_footer, "         ", 9);
          } else if (node_i == mpi_node_root) {
            /* master does not need footer (followed by slaves) */
            if (!no_footer) strcat(formatName, " no footer "); /* slaves do not need footer */
          }
          if (!mcdisable_output_files && this_p1) {
            mcformat.Name = formatName; /* use special customized format for list MPI */
            mcfile_data(simfile_f, format,
                        pre, parent,
                        NULL, this_p1, NULL, mnp[0], mnp[1], mnp[2],
                        xlabel, ylabel, zlabel, title,
                        xvar, yvar, zvar,
                        x1, x2, y1, y2, z1, z2, filename, istransposed, posa);
            mcformat.Name= formatName_orig; /* restore original format */
          }
        }
#ifdef USE_NEXUS
        else {
          /* MPI+NeXus: write one SDS per node list */
          char part[256];
          sprintf(part, "data_node_%i", node_i);
          if(mcnxfile_datablock(mcnxHandle, part,
              format.Name, parent, filename, xlabel, xlabel, ylabel, ylabel, zlabel, zlabel, title,
              xvar, yvar, zvar, abs(mnp[0]), abs(mnp[1]), abs(mnp[2]), x1, x2, y1, y2, z1, z2, NULL, this_p1, NULL)
              == NX_ERROR) {
            fprintf(stderr, "Error: writing NeXus data %s/%s (mcfile_datablock)\n", parent, filename);
          }
        }
#endif /* USE_NEXUS */
        if (node_i != mpi_node_root && this_p1) free(this_p1);
      } /* end for node_i */
    } /* end list for master node */
  } else
#endif /* USE_MPI */
  if (!mcdisable_output_files) { /* normal output */
    mcfile_data(simfile_f, format,
                pre, parent,
                p0, p1, p2, m, n, p,
                xlabel, ylabel, zlabel, title,
                xvar, yvar, zvar,
                x1, x2, y1, y2, z1, z2, filename, istransposed, posa);
  }

  if (!mcdisable_output_files) {
    mcfile_section(simfile_f, format, "end", pre, filename, "data", parent, 4);
    if (!strstr(format.Name,"NeXus"))
    mcfile_section(simfile_f, format, "end", pre, parent, "component", simname, 3);
  }

  if (simfile_f || mcdisable_output_files) {
    for(j = 0; j < n*p; j++) {
      for(i = 0; i < m; i++) {
        double N,I,E;
        int index;
        if (!istransposed) index = i*n*p + j;
        else index = i+j*m;
        if (p0) N = p0[index];
        if (p1) I = p1[index];
        if (p2) E = p2[index];

        Nsum += p0 ? N : 1;
        Psum += I;
        P2sum += p2 ? E : I*I;
      }
    }
    /* give 0D detector output. */
    if ((!filename || !strlen(filename)) && title && strlen(title)) filename = title;
    mcdetector_out(parent, Nsum, Psum, P2sum, filename);
  }
  free(pre); if (filename && filename_orig) free(filename);
  if (mcDetectorCustomHeader && strlen(mcDetectorCustomHeader)) {
     free(mcDetectorCustomHeader); mcDetectorCustomHeader=NULL;
  }
  fflush(NULL);
  return(Psum);
} /* mcdetector_out_012D */

/*******************************************************************************
* mcdetector_out_0D: wrapper to mcdetector_out_012D for 0D (single value).
*******************************************************************************/
double mcdetector_out_0D(char *t, double p0, double p1, double p2,
                         char *c, Coords posa)
{
  return(mcdetector_out_012D(mcformat,
    (c ? c : "McStas component"), (t ? t : "McStas data"),
    1, 1, 1,
    "I", "", "",
    "I", "", "",
    0, 0, 0, 0, 0, 0, NULL,
    &p0, &p1, &p2, posa));
}

/*******************************************************************************
* mcdetector_out_1D: wrapper to mcdetector_out_012D for 1D.
*******************************************************************************/
double mcdetector_out_1D(char *t, char *xl, char *yl,
                  char *xvar, double x1, double x2, int n,
                  double *p0, double *p1, double *p2, char *f,
                  char *c, Coords posa)
{
  return(mcdetector_out_012D(mcformat,
    (c ? c : "McStas component"), (t ? t : "McStas 1D data"),
    n, 1, 1,
    (xl ? xl : "X"), (yl ? yl : "Y"), (n > 1 ? "Signal per bin" : " Signal"),
    (xvar ? xvar : "x"), "(I,I_err)", "I",
    x1, x2, 0, 0, 0, 0, f,
    p0, p1, p2, posa));
}

/*******************************************************************************
* mcdetector_out_2D: wrapper to mcdetector_out_012D for 2D.
*******************************************************************************/
double mcdetector_out_2D(char *t, char *xl, char *yl,
                  double x1, double x2, double y1, double y2, int m,
                  int n, double *p0, double *p1, double *p2, char *f,
                  char *c, Coords posa)
{
  char xvar[3];
  char yvar[3];

  strcpy(xvar, "x "); strcpy(yvar, "y ");
  if (xl && strlen(xl)) strncpy(xvar, xl, 2);
  if (yl && strlen(yl)) strncpy(yvar, yl, 2);

  /* is it in fact a 1D call ? */
  if (m == 1)      return(mcdetector_out_1D(
                    t, yl, "I", yvar, y1, y2, n, p0, p1, p2, f, c, posa));
  else if (n == 1) return(mcdetector_out_1D(
                    t, xl, "I", xvar, x1, x2, m, p0, p1, p2, f, c, posa));

  return(mcdetector_out_012D(mcformat,
    (c ? c : "McStas component"), (t ? t : "McStas 2D data"),
    m, n, 1,
    (xl ? xl : "X"), (yl ? yl : "Y"), (n*m > 1 ? "Signal per bin" : " Signal"),
    xvar, yvar, "I",
    x1, x2, y1, y2, 0, 0, f,
    p0, p1, p2, posa));
}

/*******************************************************************************
* mcdetector_out_3D: wrapper to mcdetector_out_012D for 3D.
*   exported as a large 2D array, but the " dims are given in the header
*******************************************************************************/
double mcdetector_out_3D(char *t, char *xl, char *yl, char *zl,
      char *xvar, char *yvar, char *zvar,
                  double x1, double x2, double y1, double y2, double z1, double z2, int m,
                  int n, int p, double *p0, double *p1, double *p2, char *f,
                  char *c, Coords posa)
{
  return(mcdetector_out_012D(mcformat,
    (c ? c : "McStas component"), (t ? t : "McStas 3D data"),
    m, n, p,
    (xl ? xl : "X"), (yl ? yl : "Y"), (zl ? zl : "Z"),
    (xvar ? xvar : "x"), (yvar ? yvar : "y"), (zvar ? zvar : "z"),
    x1, x2, y1, y2, z1, z2, f,
    p0, p1, p2, posa));
}

/* end of file i/o functions ================================================ */

/* mcuse_format_header: Replaces aliases names in format fields (header part) */
char *mcuse_format_header(char *format_const)
{ /* Header Footer */
  char *format=NULL;

  if (!format_const) return(NULL);
  format = (char *)malloc(strlen(format_const)+1);
  if (!format) exit(fprintf(stderr, "Error: insufficient memory (mcuse_format_header)\n"));
  strcpy(format, format_const);
  str_rep(format, "%PRE", "%1$s"); /* prefix */
  str_rep(format, "%SRC", "%2$s"); /* name of instrument source file */
  str_rep(format, "%FIL", "%3$s"); /* output file name (data) */
  str_rep(format, "%FMT", "%4$s"); /* format name */
  str_rep(format, "%DATL","%8$li");/* Time elapsed since Jan 1st 1970, in seconds */
  str_rep(format, "%DAT", "%5$s"); /* Date as a string */
  str_rep(format, "%USR", "%6$s"); /* User/machine name */
  str_rep(format, "%PAR", "%7$s"); /* Parent name (root/mcstas) valid_parent */
  str_rep(format, "%VPA", "%7$s");
  return(format);
}

/* mcuse_format_tag: Replaces aliases names in format fields (tag part) */
char *mcuse_format_tag(char *format_const)
{ /* AssignTag */
  char *format=NULL;

  if (!format_const) return(NULL);
  format = (char *)malloc(strlen(format_const)+1);
  if (!format) exit(fprintf(stderr, "Error: insufficient memory (mcuse_format_tag)\n"));
  strcpy(format, format_const);
  str_rep(format, "%PRE", "%1$s"); /* prefix */
  str_rep(format, "%SEC", "%2$s"); /* section/parent name valid_parent/section */
  str_rep(format, "%PAR", "%2$s");
  str_rep(format, "%VPA", "%2$s");
  str_rep(format, "%NAM", "%3$s"); /* name of field valid_name */
  str_rep(format, "%VNA", "%3$s");
  str_rep(format, "%VAL", "%4$s"); /* value of field */
  return(format);
}

/* mcuse_format_section: Replaces aliases names in format fields (section part) */
char *mcuse_format_section(char *format_const)
{ /* BeginSection EndSection */
  char *format=NULL;

  if (!format_const) return(NULL);
  format = (char *)malloc(strlen(format_const)+1);
  if (!format) exit(fprintf(stderr, "Error: insufficient memory (mcuse_format_section)\n"));
  strcpy(format, format_const);
  str_rep(format, "%PRE", "%1$s"); /* prefix */
  str_rep(format, "%TYP", "%2$s"); /* type/class of section */
  str_rep(format, "%NAM", "%3$s"); /* name of section */
  str_rep(format, "%SEC", "%3$s");
  str_rep(format, "%VNA", "%4$s"); /* valid name (letters/digits) of section */
  str_rep(format, "%PAR", "%5$s"); /* parent name (simulation) */
  str_rep(format, "%VPA", "%6$s"); /* valid parent name (letters/digits) */
  str_rep(format, "%LVL", "%7$i"); /* level index */
  return(format);
}

/* mcuse_format_data: Replaces aliases names in format fields (data part) */
char *mcuse_format_data(char *format_const)
{ /* BeginData EndData BeginErrors EndErrors BeginNcount EndNcount */
  char *format=NULL;

  if (!format_const) return(NULL);
  format = (char *)malloc(strlen(format_const)+1);
  if (!format) exit(fprintf(stderr, "Error: insufficient memory (mcuse_format_data)\n"));
  strcpy(format, format_const);
  str_rep(format, "%PRE", "%1$s"); /* prefix */
  str_rep(format, "%PAR", "%2$s"); /* parent name (component instance name) valid_parent */
  str_rep(format, "%VPA", "%2$s");
  str_rep(format, "%FIL", "%3$s"); /* output file name (data) */
  str_rep(format, "%XLA", "%4$s"); /* x axis label */
  str_rep(format, "%XVL", "%5$s"); /* x axis valid label (letters/digits) */
  str_rep(format, "%YLA", "%6$s"); /* y axis label */
  str_rep(format, "%YVL", "%7$s"); /* y axis valid label (letters/digits) */
  str_rep(format, "%ZLA", "%8$s"); /* z axis label */
  str_rep(format, "%ZVL", "%9$s"); /* z axis valid label (letters/digits) */
  str_rep(format, "%TITL", "%10$s"); /* data title */
  str_rep(format, "%XVAR", "%11$s"); /* x variables */
  str_rep(format, "%YVAR", "%12$s"); /* y variables */
  str_rep(format, "%ZVAR", "%13$s"); /* z variables */
  str_rep(format, "%MDIM", "%14$i"); /* m dimension of x axis */
  str_rep(format, "%NDIM", "%15$i"); /* n dimension of y axis */
  str_rep(format, "%PDIM", "%16$i"); /* p dimension of z axis */
  str_rep(format, "%XMIN", "%17$g"); /* x min axis value (m bins) */
  str_rep(format, "%XMAX", "%18$g"); /* x max axis value (m bins) */
  str_rep(format, "%YMIN", "%19$g"); /* y min axis value (n bins) */
  str_rep(format, "%YMAX", "%20$g"); /* y max axis value (n bins) */
  str_rep(format, "%ZMIN", "%21$g"); /* z min axis value (usually min of signal, p bins) */
  str_rep(format, "%ZMAX", "%22$g"); /* z max axis value (usually max of signal, p bins) */
  return(format);
}

/*******************************************************************************
* mcuse_format: selects an output format for sim and data files. returns format
*******************************************************************************/
struct mcformats_struct mcuse_format(char *format)
{
  int i,j;
  int i_format=-1;
  char *tmp;
  char low_format[256];
  struct mcformats_struct usedformat;

  usedformat.Name = NULL;
  /* get the format to lower case */
  if (!format) exit(fprintf(stderr, "Error: Invalid NULL format. Exiting (mcuse_format)\n"));
  strcpy(low_format, format);
  for (i=0; i<strlen(low_format); i++) low_format[i]=tolower(format[i]);
  /* handle format aliases */
  if (!strcmp(low_format, "pgplot")) strcpy(low_format, "mcstas");
  if (!strcmp(low_format, "hdf"))    strcpy(low_format, "nexus");
#ifndef USE_NEXUS
  if (!strcmp(low_format, "nexus"))
    fprintf(stderr, "WARNING: to enable NeXus format you must have the NeXus libs installed.\n"
                    "         You should then re-compile with the -DUSE_NEXUS define.\n");
#endif

  tmp = (char *)malloc(256);
  if(!tmp) exit(fprintf(stderr, "Error: insufficient memory (mcuse_format)\n"));

  /* look for a specific format in mcformats.Name table */
  for (i=0; i < mcNUMFORMATS; i++)
  {
    strcpy(tmp, mcformats[i].Name);
    for (j=0; j<strlen(tmp); j++) tmp[j] = tolower(tmp[j]);
    if (strstr(low_format, tmp))  i_format = i;
  }
  if (i_format < 0)
  {
    i_format = 0; /* default format is #0 McStas */
    fprintf(stderr, "Warning: unknown output format '%s'. Using default (%s, mcuse_format).\n", format, mcformats[i_format].Name);
  }

  usedformat = mcformats[i_format];
  strcpy(tmp, usedformat.Name);
  usedformat.Name = tmp;
  if (strstr(low_format,"raw")) strcat(usedformat.Name," raw");
  if (strstr(low_format,"binary"))
  {
    if (strstr(low_format,"double")) strcat(usedformat.Name," binary double data");
    else strcat(usedformat.Name," binary float data");
    mcascii_only = 1;
  }

  /* Replaces vfprintf parameter name aliases */
  /* Header Footer */
  usedformat.Header       = mcuse_format_header(usedformat.Header);
  usedformat.Footer       = mcuse_format_header(usedformat.Footer);
  /* AssignTag */
  usedformat.AssignTag    = mcuse_format_tag(usedformat.AssignTag);
  /* BeginSection EndSection */
  usedformat.BeginSection = mcuse_format_section(usedformat.BeginSection);
  usedformat.EndSection   = mcuse_format_section(usedformat.EndSection);
  /*  BeginData  EndData  BeginErrors  EndErrors  BeginNcount  EndNcount  */
  usedformat.BeginData    = mcuse_format_data(usedformat.BeginData  );
  usedformat.EndData      = mcuse_format_data(usedformat.EndData    );
  usedformat.BeginErrors  = mcuse_format_data(usedformat.BeginErrors);
  usedformat.EndErrors    = mcuse_format_data(usedformat.EndErrors  );
  usedformat.BeginNcount  = mcuse_format_data(usedformat.BeginNcount);
  usedformat.EndNcount    = mcuse_format_data(usedformat.EndNcount  );

  return(usedformat);
} /* mcuse_format */

/* mcclear_format: free format structure */
void mcclear_format(struct mcformats_struct usedformat)
{
/* free format specification strings */
  if (usedformat.Name        ) free(usedformat.Name        );
  else return;
  if (usedformat.Header      ) free(usedformat.Header      );
  if (usedformat.Footer      ) free(usedformat.Footer      );
  if (usedformat.AssignTag   ) free(usedformat.AssignTag   );
  if (usedformat.BeginSection) free(usedformat.BeginSection);
  if (usedformat.EndSection  ) free(usedformat.EndSection  );
  if (usedformat.BeginData   ) free(usedformat.BeginData   );
  if (usedformat.EndData     ) free(usedformat.EndData     );
  if (usedformat.BeginErrors ) free(usedformat.BeginErrors );
  if (usedformat.EndErrors   ) free(usedformat.EndErrors   );
  if (usedformat.BeginNcount ) free(usedformat.BeginNcount );
  if (usedformat.EndNcount   ) free(usedformat.EndNcount   );
} /* mcclear_format */

/* mcuse_file: will save data/sim files */
static void mcuse_file(char *file)
{
  if (file && strcmp(file, "NULL"))
    mcsiminfo_name = file;
  else {
    char *filename=(char*)malloc(CHAR_BUF_LENGTH);
    sprintf(filename, "%s_%li", mcinstrument_name, mcstartdate);
    mcsiminfo_name = filename;
  }
  mcsingle_file  = 1;
}

/* Following part is only embedded when not redundent with mcstas.h ========= */

#ifndef MCSTAS_H

/* MCDISPLAY support. ======================================================= */

/*******************************************************************************
* Just output MCDISPLAY keywords to be caught by an external plotter client.
*******************************************************************************/

void mcdis_magnify(char *what){
  printf("MCDISPLAY: magnify('%s')\n", what);
}

void mcdis_line(double x1, double y1, double z1,
                double x2, double y2, double z2){
  printf("MCDISPLAY: multiline(2,%g,%g,%g,%g,%g,%g)\n",
         x1,y1,z1,x2,y2,z2);
}

void mcdis_dashed_line(double x1, double y1, double z1,
		       double x2, double y2, double z2, int n){
  int i;
  const double dx = (x2-x1)/(2*n+1);
  const double dy = (y2-y1)/(2*n+1);
  const double dz = (z2-z1)/(2*n+1);

  for(i = 0; i < n+1; i++)
    mcdis_line(x1 + 2*i*dx,     y1 + 2*i*dy,     z1 + 2*i*dz,
	       x1 + (2*i+1)*dx, y1 + (2*i+1)*dy, z1 + (2*i+1)*dz);
}

void mcdis_multiline(int count, ...){
  va_list ap;
  double x,y,z;

  printf("MCDISPLAY: multiline(%d", count);
  va_start(ap, count);
  while(count--)
    {
    x = va_arg(ap, double);
    y = va_arg(ap, double);
    z = va_arg(ap, double);
    printf(",%g,%g,%g", x, y, z);
    }
  va_end(ap);
  printf(")\n");
}

void mcdis_rectangle(char* plane, double x, double y, double z,
		     double width, double height){
  /* draws a rectangle in the plane           */
  /* x is ALWAYS width and y is ALWAYS height */
  if (strcmp("xy", plane)==0) {
    mcdis_multiline(5,
		    x - width/2, y - height/2, z,
		    x + width/2, y - height/2, z,
		    x + width/2, y + height/2, z,
		    x - width/2, y + height/2, z,
		    x - width/2, y - height/2, z);
  } else if (strcmp("xz", plane)==0) {
    mcdis_multiline(5,
		    x - width/2, y, z - height/2,
		    x + width/2, y, z - height/2,
		    x + width/2, y, z + height/2,
		    x - width/2, y, z + height/2,
		    x - width/2, y, z - height/2);
  } else if (strcmp("yz", plane)==0) {
    mcdis_multiline(5,
		    x, y - height/2, z - width/2,
		    x, y - height/2, z + width/2,
		    x, y + height/2, z + width/2,
		    x, y + height/2, z - width/2,
		    x, y - height/2, z - width/2);
  } else {

    fprintf(stderr, "Error: Definition of plane %s unknown\n", plane);
    exit(1);
  }
}

/*  draws a box with center at (x, y, z) and
    width (deltax), height (deltay), length (deltaz) */
void mcdis_box(double x, double y, double z,
	       double width, double height, double length){

  mcdis_rectangle("xy", x, y, z-length/2, width, height);
  mcdis_rectangle("xy", x, y, z+length/2, width, height);
  mcdis_line(x-width/2, y-height/2, z-length/2,
	     x-width/2, y-height/2, z+length/2);
  mcdis_line(x-width/2, y+height/2, z-length/2,
	     x-width/2, y+height/2, z+length/2);
  mcdis_line(x+width/2, y-height/2, z-length/2,
	     x+width/2, y-height/2, z+length/2);
  mcdis_line(x+width/2, y+height/2, z-length/2,
	     x+width/2, y+height/2, z+length/2);
}

void mcdis_circle(char *plane, double x, double y, double z, double r){
  printf("MCDISPLAY: circle('%s',%g,%g,%g,%g)\n", plane, x, y, z, r);
}

/* coordinates handling ===================================================== */

/*******************************************************************************
* Since we use a lot of geometric calculations using Cartesian coordinates,
* we collect some useful routines here. However, it is also permissible to
* work directly on the underlying struct coords whenever that is most
* convenient (that is, the type Coords is not abstract).
*
* Coordinates are also used to store rotation angles around x/y/z axis.
*
* Since coordinates are used much like a basic type (such as double), the
* structure itself is passed and returned, rather than a pointer.
*
* At compile-time, the values of the coordinates may be unknown (for example
* a motor position). Hence coordinates are general expressions and not simple
* numbers. For this we used the type Coords_exp which has three CExp
* fields. For runtime (or calculations possible at compile time), we use
* Coords which contains three double fields.
*******************************************************************************/

/* coords_set: Assign coordinates. */
Coords
coords_set(MCNUM x, MCNUM y, MCNUM z)
{
  Coords a;

  a.x = x;
  a.y = y;
  a.z = z;
  return a;
}

/* coords_get: get coordinates. Required when 'x','y','z' are #defined as neutron pars */
Coords
coords_get(Coords a, MCNUM *x, MCNUM *y, MCNUM *z)
{
  *x = a.x;
  *y = a.y;
  *z = a.z;
  return a;
}

/* coords_add: Add two coordinates. */
Coords
coords_add(Coords a, Coords b)
{
  Coords c;

  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
  if (fabs(c.z) < 1e-14) c.z=0.0;
  return c;
}

/* coords_sub: Subtract two coordinates. */
Coords
coords_sub(Coords a, Coords b)
{
  Coords c;

  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
  if (fabs(c.z) < 1e-14) c.z=0.0;
  return c;
}

/* coords_neg: Negate coordinates. */
Coords
coords_neg(Coords a)
{
  Coords b;

  b.x = -a.x;
  b.y = -a.y;
  b.z = -a.z;
  return b;
}

/* coords_scale: Scale a vector. */
Coords coords_scale(Coords b, double scale) {
  Coords a;

  a.x = b.x*scale;
  a.y = b.y*scale;
  a.z = b.z*scale;
  return a;
}

/* coords_sp: Scalar product: a . b */
double coords_sp(Coords a, Coords b) {
  double value;

  value = a.x*b.x + a.y*b.y + a.z*b.z;
  return value;
}

/* coords_xp: Cross product: a = b x c. */
Coords coords_xp(Coords b, Coords c) {
  Coords a;

  a.x = b.y*c.z - c.y*b.z;
  a.y = b.z*c.x - c.z*b.x;
  a.z = b.x*c.y - c.x*b.y;
  return a;
}

/* coords_mirror: Mirror a in plane (through the origin) defined by normal n*/
Coords coords_mirror(Coords a, Coords n) {
  double t;
  Coords b;
  if ((t=scalar_prod(n.x,n.y,n.z, n.x,n.y,n.z))!=1)
    n.x/=sqrt(t);n.y/=sqrt(t);n.z/=sqrt(t);
  t=scalar_prod(a.x,a.y,a.z,n.x,n.y,n.z);
  b.x=a.x-2*t*n.x;
  b.y=a.y-2*t*n.y;
  b.z=a.z-2*t*n.z;
  return b;
}

/* coords_print: Print out vector values. */
void coords_print(Coords a) {

  fprintf(stdout, "(%f, %f, %f)\n", a.x, a.y, a.z);
  return;
}

/*******************************************************************************
* The Rotation type implements a rotation transformation of a coordinate
* system in the form of a double[3][3] matrix.
*
* Contrary to the Coords type in coords.c, rotations are passed by
* reference. Functions that yield new rotations do so by writing to an
* explicit result parameter; rotations are not returned from functions. The
* reason for this is that arrays cannot by returned from functions (though
* structures can; thus an alternative would have been to wrap the
* double[3][3] array up in a struct). Such are the ways of C programming.
*
* A rotation represents the tranformation of the coordinates of a vector when
* changing between coordinate systems that are rotated with respect to each
* other. For example, suppose that coordinate system Q is rotated 45 degrees
* around the Z axis with respect to coordinate system P. Let T be the
* rotation transformation representing a 45 degree rotation around Z. Then to
* get the coordinates of a vector r in system Q, apply T to the coordinates
* of r in P. If r=(1,0,0) in P, it will be (sqrt(1/2),-sqrt(1/2),0) in
* Q. Thus we should be careful when interpreting the sign of rotation angles:
* they represent the rotation of the coordinate systems, not of the
* coordinates (which has opposite sign).
*******************************************************************************/

/*******************************************************************************
* rot_set_rotation: Get transformation for rotation first phx around x axis,
* then phy around y, then phz around z.
*******************************************************************************/
void
rot_set_rotation(Rotation t, double phx, double phy, double phz)
{
  if ((phx == 0) && (phy == 0) && (phz == 0)) {
    t[0][0] = 1.0;
    t[0][1] = 0.0;
    t[0][2] = 0.0;
    t[1][0] = 0.0;
    t[1][1] = 1.0;
    t[1][2] = 0.0;
    t[2][0] = 0.0;
    t[2][1] = 0.0;
    t[2][2] = 1.0;
  } else {
    double cx = cos(phx);
    double sx = sin(phx);
    double cy = cos(phy);
    double sy = sin(phy);
    double cz = cos(phz);
    double sz = sin(phz);
    
    t[0][0] = cy*cz;
    t[0][1] = sx*sy*cz + cx*sz;
    t[0][2] = sx*sz - cx*sy*cz;
    t[1][0] = -cy*sz;
    t[1][1] = cx*cz - sx*sy*sz;
    t[1][2] = sx*cz + cx*sy*sz;
    t[2][0] = sy;
    t[2][1] = -sx*cy;
    t[2][2] = cx*cy;
  } 
}

/*******************************************************************************
* rot_test_identity: Test if rotation is identity
*******************************************************************************/
int 
rot_test_identity(Rotation t)
{
  return (t[0][0] + t[1][1] + t[2][2] == 3);
}

/*******************************************************************************
* rot_mul: Matrix multiplication of transformations (this corresponds to
* combining transformations). After rot_mul(T1, T2, T3), doing T3 is
* equal to doing first T2, then T1.
* Note that T3 must not alias (use the same array as) T1 or T2.
*******************************************************************************/
void
rot_mul(Rotation t1, Rotation t2, Rotation t3)
{
  int i,j;
  if (rot_test_identity(t1)) {
    memcpy(t3, t2, 9 * sizeof (double));
  } else if (rot_test_identity(t2)) {
    memcpy(t3, t1, 9 * sizeof (double));
  } else {
    for(i = 0; i < 3; i++)
      for(j = 0; j < 3; j++)
	t3[i][j] = t1[i][0]*t2[0][j] + t1[i][1]*t2[1][j] + t1[i][2]*t2[2][j];
  }
}

/*******************************************************************************
* rot_copy: Copy a rotation transformation (arrays cannot be assigned in C).
*******************************************************************************/
void
rot_copy(Rotation dest, Rotation src)
{
	memcpy(dest, src, 9 * sizeof (double));
}

/*******************************************************************************
* rot_transpose: Matrix transposition, which is inversion for Rotation matrices
*******************************************************************************/
void
rot_transpose(Rotation src, Rotation dst)
{
  dst[0][0] = src[0][0];
  dst[0][1] = src[1][0];
  dst[0][2] = src[2][0];
  dst[1][0] = src[0][1];
  dst[1][1] = src[1][1];
  dst[1][2] = src[2][1];
  dst[2][0] = src[0][2];
  dst[2][1] = src[1][2];
  dst[2][2] = src[2][2];
}

/*******************************************************************************
* rot_apply: returns t*a
*******************************************************************************/
Coords
rot_apply(Rotation t, Coords a)
{
  Coords b;
  if (rot_test_identity(t)) { 
    return a;
  } else {
    b.x = t[0][0]*a.x + t[0][1]*a.y + t[0][2]*a.z;
    b.y = t[1][0]*a.x + t[1][1]*a.y + t[1][2]*a.z;
    b.z = t[2][0]*a.x + t[2][1]*a.y + t[2][2]*a.z;
    return b;
  }
}

/*******************************************************************************
* mccoordschange: applies rotation to (x y z) and (vx vy vz). Spin unchanged
*******************************************************************************/
void
mccoordschange(Coords a, Rotation t, double *x, double *y, double *z,
               double *vx, double *vy, double *vz, double *time,
               double *s1, double *s2)
{
  Coords b, c;

  b.x = *x;
  b.y = *y;
  b.z = *z;
  c = rot_apply(t, b);
  b = coords_add(c, a);
  *x = b.x;
  *y = b.y;
  *z = b.z;

  b.x = *vx;
  b.y = *vy;
  b.z = *vz;
  c = rot_apply(t, b);
  *vx = c.x;
  *vy = c.y;
  *vz = c.z;
  /* spin handled with mccoordschange_polarisation */
}

/*******************************************************************************
* mccoordschange_polarisation: applies rotation to (sx sy sz)
*******************************************************************************/
void
mccoordschange_polarisation(Rotation t, double *sx, double *sy, double *sz)
{
  Coords b, c;

  b.x = *sx;
  b.y = *sy;
  b.z = *sz;
  c = rot_apply(t, b);
  *sx = c.x;
  *sy = c.y;
  *sz = c.z;
}

/*******************************************************************************
* mcstore_neutron: stores neutron coodinates into global array (per component)
*******************************************************************************/
void
mcstore_neutron(MCNUM *s, int index, double x, double y, double z,
               double vx, double vy, double vz, double t,
               double sx, double sy, double sz, double p)
{
    double *dptr = &s[11*index];
    *dptr++  = x;
    *dptr++  = y ;
    *dptr++  = z ;
    *dptr++  = vx;
    *dptr++  = vy;
    *dptr++  = vz;
    *dptr++  = t ;
    *dptr++  = sx;
    *dptr++  = sy;
    *dptr++  = sz;
    *dptr    = p ;
}

/*******************************************************************************
* mcrestore_neutron: restores neutron coodinates from global array
*******************************************************************************/
void
mcrestore_neutron(MCNUM *s, int index, double *x, double *y, double *z,
               double *vx, double *vy, double *vz, double *t,
               double *sx, double *sy, double *sz, double *p)
{
    double *dptr = &s[11*index];
    *x  =  *dptr++;
    *y  =  *dptr++;
    *z  =  *dptr++;
    *vx =  *dptr++;
    *vy =  *dptr++;
    *vz =  *dptr++;
    *t  =  *dptr++;
    *sx =  *dptr++;
    *sy =  *dptr++;
    *sz =  *dptr++;
    *p  =  *dptr;
}

/* init/run/rand handling =================================================== */

/* mcreadparams: request parameters from the prompt (or use default) */
void
mcreadparams(void)
{
  int i,j,status;
  static char buf[CHAR_BUF_LENGTH];
  char *p;
  int len;

  MPI_MASTER(printf("Instrument parameters for %s (%s)\n",
                    mcinstrument_name, mcinstrument_source));

  for(i = 0; mcinputtable[i].name != 0; i++)
  {
    do
    {
      MPI_MASTER(
                 if (mcinputtable[i].val && strlen(mcinputtable[i].val))
                   printf("Set value of instrument parameter %s (%s) [default='%s']:\n",
                          mcinputtable[i].name,
                          (*mcinputtypes[mcinputtable[i].type].parminfo)
                          (mcinputtable[i].name), mcinputtable[i].val);
                 else
                   printf("Set value of instrument parameter %s (%s):\n",
                          mcinputtable[i].name,
                          (*mcinputtypes[mcinputtable[i].type].parminfo)
                          (mcinputtable[i].name));
                 fflush(stdout);
                 );
#ifdef USE_MPI
      if(mpi_node_rank == mpi_node_root)
        {
          p = fgets(buf, CHAR_BUF_LENGTH, stdin);
          if(p == NULL)
            {
              fprintf(stderr, "Error: empty input for paramater %s (mcreadparams)\n", mcinputtable[i].name);
              exit(1);
            }
        }
      else
        p = buf;
      MPI_Bcast(buf, CHAR_BUF_LENGTH, MPI_CHAR, mpi_node_root, MPI_COMM_WORLD);
#else /* !USE_MPI */
      p = fgets(buf, CHAR_BUF_LENGTH, stdin);
      if(p == NULL)
        {
          fprintf(stderr, "Error: empty input for paramater %s (mcreadparams)\n", mcinputtable[i].name);
          exit(1);
        }
#endif /* USE_MPI */
      len = strlen(buf);
      if (!len || (len == 1 && (buf[0] == '\n' || buf[0] == '\r')))
      {
        if (mcinputtable[i].val && strlen(mcinputtable[i].val)) {
          strncpy(buf, mcinputtable[i].val, CHAR_BUF_LENGTH);  /* use default value */
          len = strlen(buf);
        }
      }
      for(j = 0; j < 2; j++)
      {
        if(len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r'))
        {
          len--;
          buf[len] = '\0';
        }
      }

      status = (*mcinputtypes[mcinputtable[i].type].getparm)
                   (buf, mcinputtable[i].par);
      if(!status)
      {
        (*mcinputtypes[mcinputtable[i].type].error)(mcinputtable[i].name, buf);
        if (!mcinputtable[i].val || strlen(mcinputtable[i].val)) {
          fprintf(stderr, "       Change %s default value in instrument definition.\n", mcinputtable[i].name);
          exit(1);
        }
      }
    } while(!status);
  }
}

/* mcsetstate: transfert parameters into global McStas variables */
void
mcsetstate(double x, double y, double z, double vx, double vy, double vz,
           double t, double sx, double sy, double sz, double p)
{
  extern double mcnx, mcny, mcnz, mcnvx, mcnvy, mcnvz;
  extern double mcnt, mcnsx, mcnsy, mcnsz, mcnp;

  mcnx = x;
  mcny = y;
  mcnz = z;
  mcnvx = vx;
  mcnvy = vy;
  mcnvz = vz;
  mcnt = t;
  mcnsx = sx;
  mcnsy = sy;
  mcnsz = sz;
  mcnp = p;
}

/* mcgenstate: set default neutron parameters */
void
mcgenstate(void)
{
  mcsetstate(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  /* old initialisation: mcsetstate(0, 0, 0, 0, 0, 1, 0, sx=0, sy=1, sz=0, 1); */
}

/* McStas random number routine. */

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * This is derived from the Berkeley source:
 *        @(#)random.c        5.5 (Berkeley) 7/6/88
 * It was reworked for the GNU C Library by Roland McGrath.
 * Rewritten to use reentrant functions by Ulrich Drepper, 1995.
 */

/*******************************************************************************
* Modified for McStas from glibc 2.0.7pre1 stdlib/random.c and
* stdlib/random_r.c.
*
* This way random() is more than four times faster compared to calling
* standard glibc random() on ix86 Linux, probably due to multithread support,
* ELF shared library overhead, etc. It also makes McStas generated
* simulations more portable (more likely to behave identically across
* platforms, important for parrallel computations).
*******************************************************************************/


#define        TYPE_3                3
#define        BREAK_3                128
#define        DEG_3                31
#define        SEP_3                3

static mc_int32_t randtbl[DEG_3 + 1] =
  {
    TYPE_3,

    -1726662223, 379960547, 1735697613, 1040273694, 1313901226,
    1627687941, -179304937, -2073333483, 1780058412, -1989503057,
    -615974602, 344556628, 939512070, -1249116260, 1507946756,
    -812545463, 154635395, 1388815473, -1926676823, 525320961,
    -1009028674, 968117788, -123449607, 1284210865, 435012392,
    -2017506339, -911064859, -370259173, 1132637927, 1398500161,
    -205601318,
  };

static mc_int32_t *fptr = &randtbl[SEP_3 + 1];
static mc_int32_t *rptr = &randtbl[1];
static mc_int32_t *state = &randtbl[1];
#define rand_deg DEG_3
#define rand_sep SEP_3
static mc_int32_t *end_ptr = &randtbl[sizeof (randtbl) / sizeof (randtbl[0])];

mc_int32_t
mc_random (void)
{
  mc_int32_t result;

  *fptr += *rptr;
  /* Chucking least random bit.  */
  result = (*fptr >> 1) & 0x7fffffff;
  ++fptr;
  if (fptr >= end_ptr)
  {
    fptr = state;
    ++rptr;
  }
  else
  {
    ++rptr;
    if (rptr >= end_ptr)
      rptr = state;
  }
  return result;
}

void
mc_srandom (unsigned int x)
{
  /* We must make sure the seed is not 0.  Take arbitrarily 1 in this case.  */
  state[0] = x ? x : 1;
  {
    long int i;
    for (i = 1; i < rand_deg; ++i)
    {
      /* This does:
         state[i] = (16807 * state[i - 1]) % 2147483647;
         but avoids overflowing 31 bits.  */
      long int hi = state[i - 1] / 127773;
      long int lo = state[i - 1] % 127773;
      long int test = 16807 * lo - 2836 * hi;
      state[i] = test + (test < 0 ? 2147483647 : 0);
    }
    fptr = &state[rand_sep];
    rptr = &state[0];
    for (i = 0; i < 10 * rand_deg; ++i)
      random ();
  }
}

/* "Mersenne Twister", by Makoto Matsumoto and Takuji Nishimura. */
/* See http://www.math.keio.ac.jp/~matumoto/emt.html for original source. */


/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using mt_srandom(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.keio.ac.jp/matumoto/emt.html
   email: matumoto@math.keio.ac.jp
*/

#include <stdio.h>

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void mt_srandom(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
            (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void init_by_array(init_key, key_length)
unsigned long init_key[], key_length;
{
    int i, j, k;
    mt_srandom(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long mt_random(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if mt_srandom() has not been called, */
            mt_srandom(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

#undef N
#undef M
#undef MATRIX_A
#undef UPPER_MASK
#undef LOWER_MASK

/* End of "Mersenne Twister". */

/* End of McStas random number routine. */

/* randnorm: generate a random number from normal law */
double
randnorm(void)
{
  static double v1, v2, s;
  static int phase = 0;
  double X, u1, u2;

  if(phase == 0)
  {
    do
    {
      u1 = rand01();
      u2 = rand01();
      v1 = 2*u1 - 1;
      v2 = 2*u2 - 1;
      s = v1*v1 + v2*v2;
    } while(s >= 1 || s == 0);

    X = v1*sqrt(-2*log(s)/s);
  }
  else
  {
    X = v2*sqrt(-2*log(s)/s);
  }

  phase = 1 - phase;
  return X;
}

/* generate a random number from -1 to 1 with triangle distribution */
double randtriangle(void) {
  double randnum=rand01();
  if (randnum>0.5) return(1-sqrt(2*(randnum-0.5)));
  else return(sqrt(2*randnum)-1);
}

/* intersect handling ======================================================= */

/* normal_vec: Compute normal vector to (x,y,z). */
void normal_vec(double *nx, double *ny, double *nz,
                double x, double y, double z)
{
  double ax = fabs(x);
  double ay = fabs(y);
  double az = fabs(z);
  double l;
  if(x == 0 && y == 0 && z == 0)
  {
    *nx = 0;
    *ny = 0;
    *nz = 0;
    return;
  }
  if(ax < ay)
  {
    if(ax < az)
    {                           /* Use X axis */
      l = sqrt(z*z + y*y);
      *nx = 0;
      *ny = z/l;
      *nz = -y/l;
      return;
    }
  }
  else
  {
    if(ay < az)
    {                           /* Use Y axis */
      l = sqrt(z*z + x*x);
      *nx = z/l;
      *ny = 0;
      *nz = -x/l;
      return;
    }
  }
  /* Use Z axis */
  l = sqrt(y*y + x*x);
  *nx = y/l;
  *ny = -x/l;
  *nz = 0;
}

/* inside_rectangle: Check if (x,y) is inside rectangle (xwidth, yheight) */
/* return 0 if outside and 1 if inside */
int inside_rectangle(double x, double y, double xwidth, double yheight)
{
  if (x>-xwidth/2 && x<xwidth/2 && y>-yheight/2 && y<yheight/2)
    return 1;
  else
    return 0;
}

/* box_intersect: compute time intersection with a box
 * returns 0 when no intersection is found
 *      or 1 in case of intersection with resulting times dt_in and dt_out
 * This function written by Stine Nyborg, 1999. */
int box_intersect(double *dt_in, double *dt_out,
                  double x, double y, double z,
                  double vx, double vy, double vz,
                  double dx, double dy, double dz)
{
  double x_in, y_in, z_in, tt, t[6], a, b;
  int i, count, s;

      /* Calculate intersection time for each of the six box surface planes
       *  If the box surface plane is not hit, the result is zero.*/

  if(vx != 0)
   {
    tt = -(dx/2 + x)/vx;
    y_in = y + tt*vy;
    z_in = z + tt*vz;
    if( y_in > -dy/2 && y_in < dy/2 && z_in > -dz/2 && z_in < dz/2)
      t[0] = tt;
    else
      t[0] = 0;

    tt = (dx/2 - x)/vx;
    y_in = y + tt*vy;
    z_in = z + tt*vz;
    if( y_in > -dy/2 && y_in < dy/2 && z_in > -dz/2 && z_in < dz/2)
      t[1] = tt;
    else
      t[1] = 0;
   }
  else
    t[0] = t[1] = 0;

  if(vy != 0)
   {
    tt = -(dy/2 + y)/vy;
    x_in = x + tt*vx;
    z_in = z + tt*vz;
    if( x_in > -dx/2 && x_in < dx/2 && z_in > -dz/2 && z_in < dz/2)
      t[2] = tt;
    else
      t[2] = 0;

    tt = (dy/2 - y)/vy;
    x_in = x + tt*vx;
    z_in = z + tt*vz;
    if( x_in > -dx/2 && x_in < dx/2 && z_in > -dz/2 && z_in < dz/2)
      t[3] = tt;
    else
      t[3] = 0;
   }
  else
    t[2] = t[3] = 0;

  if(vz != 0)
   {
    tt = -(dz/2 + z)/vz;
    x_in = x + tt*vx;
    y_in = y + tt*vy;
    if( x_in > -dx/2 && x_in < dx/2 && y_in > -dy/2 && y_in < dy/2)
      t[4] = tt;
    else
      t[4] = 0;

    tt = (dz/2 - z)/vz;
    x_in = x + tt*vx;
    y_in = y + tt*vy;
    if( x_in > -dx/2 && x_in < dx/2 && y_in > -dy/2 && y_in < dy/2)
      t[5] = tt;
    else
      t[5] = 0;
   }
  else
    t[4] = t[5] = 0;

  /* The intersection is evaluated and *dt_in and *dt_out are assigned */

  a = b = s = 0;
  count = 0;

  for( i = 0; i < 6; i = i + 1 )
    if( t[i] == 0 )
      s = s+1;
    else if( count == 0 )
    {
      a = t[i];
      count = 1;
    }
    else
    {
      b = t[i];
      count = 2;
    }

  if ( a == 0 && b == 0 )
    return 0;
  else if( a < b )
  {
    *dt_in = a;
    *dt_out = b;
    return 1;
  }
  else
  {
    *dt_in = b;
    *dt_out = a;
    return 1;
  }

}

/* cylinder_intersect: compute intersction with a cylinder
 * returns 0 when no intersection is found
 *      or 2/4/8/16 bits depending on intersection,
 *     and resulting times t0 and tdt_out1
 * Written by: EM,NB,ABA 4.2.98 */
int
cylinder_intersect(double *t0, double *t1, double x, double y, double z,
                   double vx, double vy, double vz, double r, double h)
{
  double D, t_in, t_out, y_in, y_out;
  int ret=1;

  D = (2*vx*x + 2*vz*z)*(2*vx*x + 2*vz*z)
    - 4*(vx*vx + vz*vz)*(x*x + z*z - r*r);

  if (D>=0)
  {
    if (vz*vz + vx*vx) {
      t_in  = (-(2*vz*z + 2*vx*x) - sqrt(D))/(2*(vz*vz + vx*vx));
      t_out = (-(2*vz*z + 2*vx*x) + sqrt(D))/(2*(vz*vz + vx*vx));
    } else if (vy) { /* trajectory parallel to cylinder axis */
      t_in = (y + h/2)/vy;
      t_out = (y - h/2)/vy;
    } else return 0;
    y_in = vy*t_in + y;
    y_out =vy*t_out + y;

    if ( (y_in > h/2 && y_out > h/2) || (y_in < -h/2 && y_out < -h/2) )
      return 0;
    else
    {
      if (y_in > h/2)
        { t_in = ((h/2)-y)/vy; ret += 2; }
      else if (y_in < -h/2)
        { t_in = ((-h/2)-y)/vy; ret += 4; }
      if (y_out > h/2)
        { t_out = ((h/2)-y)/vy; ret += 8; }
      else if (y_out < -h/2)
        { t_out = ((-h/2)-y)/vy; ret += 16; }
    }
    *t0 = t_in;
    *t1 = t_out;
    return ret;
  }
  else
  {
    *t0 = *t1 = 0;
    return 0;
  }
}


/* sphere_intersect: Calculate intersection between a line and a sphere.
 * returns 0 when no intersection is found
 *      or 1 in case of intersection with resulting times t0 and t1 */
int
sphere_intersect(double *t0, double *t1, double x, double y, double z,
                 double vx, double vy, double vz, double r)
{
  double A, B, C, D, v;

  v = sqrt(vx*vx + vy*vy + vz*vz);
  A = v*v;
  B = 2*(x*vx + y*vy + z*vz);
  C = x*x + y*y + z*z - r*r;
  D = B*B - 4*A*C;
  if(D < 0)
    return 0;
  D = sqrt(D);
  *t0 = (-B - D) / (2*A);
  *t1 = (-B + D) / (2*A);
  return 1;
}

/* solve_2nd_order: second order equation solve: A*t^2 + B*t + C = 0
 * returns 0 if no solution was found, or set 't' to the smallest positive
 * solution.
 * EXAMPLE usage for intersection of a trajectory with a plane in gravitation
 * field (gx,gy,gz):
 * The neutron starts at point r=(x,y,z) with velocityv=(vx vy vz). The plane
 * has a normal vector n=(nx,ny,nz) and contains the point W=(wx,wy,wz).
 * The problem consists in solving the 2nd order equation:
 *      1/2.n.g.t^2 + n.v.t + n.(r-W) = 0
 * so that A = 0.5 n.g; B = n.v; C = n.(r-W);
 * Without acceleration, t=-n.(r-W)/n.v
 */
int solve_2nd_order(double *Idt,
                  double A,  double B,  double C)
{
  int ret=0;

  *Idt = 0;

  if (fabs(A) < 1E-10) /* this plane is parallel to the acceleration: A ~ 0 */
  {
    if (B) {  *Idt = -C/B; ret=3; }
    /* else the speed is parallel to the plane, no intersection: A=B=0 ret=0 */
  }
  else
  {
    double D;
    D = B*B - 4*A*C;
    if (D >= 0) /* Delta > 0: neutron trajectory hits the mirror */
    {
      double sD, dt1, dt2;
      sD = sqrt(D);
      dt1 = (-B + sD)/2/A;
      dt2 = (-B - sD)/2/A;
      /* we identify very small values with zero */
      if (fabs(dt1) < 1e-10) dt1=0.0;
      if (fabs(dt2) < 1e-10) dt2=0.0;

      /* now we choose the smallest positive solution */
      if      (dt1<=0.0 && dt2>0.0) ret=2; /* dt2 positive */
      else if (dt2<=0.0 && dt1>0.0) ret=1; /* dt1 positive */
      else if (dt1> 0.0 && dt2>0.0)
      {  if (dt1 < dt2) ret=1; else ret=2; } /* all positive: min(dt1,dt2) */
      /* else two solutions are negative. ret=0 */
      if (ret==1) *Idt = dt1; else if (ret==2) *Idt=dt2;
    } /* else Delta <0: no intersection.  ret=0 */
  }
  return(ret);
}

/* plane_intersect: Calculate intersection between a plane and a line.
 * returns 0 when no intersection is found (i.e. line is parallel to the plane)
 * returns 1 or -1 when intersection time is positive and negative respectively
 */  
int
plane_intersect(double *t, double x, double y, double z,
                 double vx, double vy, double vz, double nx, double ny, double nz, double wx, double wy, double wz)
{
  double s;
  if (fabs(s=scalar_prod(nx,ny,nz,vx,vy,vz))<FLT_EPSILON) return 0;
  *t = - scalar_prod(nx,ny,nz,x-wx,y-wy,z-wz)/s;
  if (t<0) return -1;
  else return 1;
}

/* randvec_target_circle: Choose random direction towards target at (x,y,z)
 * with given radius.
 * If radius is zero, choose random direction in full 4PI, no target. */
void
randvec_target_circle(double *xo, double *yo, double *zo, double *solid_angle,
               double xi, double yi, double zi, double radius)
{
  double l2, phi, theta, nx, ny, nz, xt, yt, zt, xu, yu, zu;

  if(radius == 0.0)
  {
    /* No target, choose uniformly a direction in full 4PI solid angle. */
    theta = acos (1 - rand0max(2));
    phi = rand0max(2 * PI);
    if(solid_angle)
      *solid_angle = 4*PI;
    nx = 1;
    ny = 0;
    nz = 0;
    yi = sqrt(xi*xi+yi*yi+zi*zi);
    zi = 0;
    xi = 0;
  }
  else
  {
    double costheta0;
    l2 = xi*xi + yi*yi + zi*zi; /* sqr Distance to target. */
    costheta0 = sqrt(l2/(radius*radius+l2));
    if (radius < 0) costheta0 *= -1;
    if(solid_angle)
    {
      /* Compute solid angle of target as seen from origin. */
        *solid_angle = 2*PI*(1 - costheta0);
    }

    /* Now choose point uniformly on circle surface within angle theta0 */
    theta = acos (1 - rand0max(1 - costheta0)); /* radius on circle */
    phi = rand0max(2 * PI); /* rotation on circle at given radius */
    /* Now, to obtain the desired vector rotate (xi,yi,zi) angle theta around a
       perpendicular axis u=i x n and then angle phi around i. */
    if(xi == 0 && zi == 0)
    {
      nx = 1;
      ny = 0;
      nz = 0;
    }
    else
    {
      nx = -zi;
      nz = xi;
      ny = 0;
    }
  }

  /* [xyz]u = [xyz]i x n[xyz] (usually vertical) */
  vec_prod(xu,  yu,  zu, xi, yi, zi,        nx, ny, nz);
  /* [xyz]t = [xyz]i rotated theta around [xyz]u */
  rotate  (xt,  yt,  zt, xi, yi, zi, theta, xu, yu, zu);
  /* [xyz]o = [xyz]t rotated phi around n[xyz] */
  rotate (*xo, *yo, *zo, xt, yt, zt, phi, xi, yi, zi);
}


/* randvec_target_rect_angular: Choose random direction towards target at
 * (xi,yi,zi) with given ANGULAR dimension height x width. height=phi_x,
 * width=phi_y (radians)
 * If height or width is zero, choose random direction in full 4PI, no target. */
void
randvec_target_rect_angular(double *xo, double *yo, double *zo, double *solid_angle,
               double xi, double yi, double zi, double width, double height, Rotation A)
{
  double theta, phi, nx, ny, nz, xt, yt, zt, xu, yu, zu;
  Coords tmp;
  Rotation Ainverse;

  rot_transpose(A, Ainverse);

  if(height == 0.0 || width == 0.0)
  {
    randvec_target_circle(xo, yo, zo, solid_angle,
               xi, yi, zi, 0);
    return;
  }
  else
  {
    if(solid_angle)
    {
      /* Compute solid angle of target as seen from origin. */
      *solid_angle = 2*fabs(width*sin(height/2));
    }

    /* Go to global coordinate system */

    tmp = coords_set(xi, yi, zi);
    tmp = rot_apply(Ainverse, tmp);
    coords_get(tmp, &xi, &yi, &zi);

    /* Now choose point uniformly on quadrant within angle theta0/phi0 */
    theta = width*randpm1()/2.0;
    phi   = height*randpm1()/2.0;
    /* Now, to obtain the desired vector rotate (xi,yi,zi) angle phi around
       n, and then theta around u. */
    if(xi == 0 && zi == 0)
    {
      nx = 1;
      ny = 0;
      nz = 0;
    }
    else
    {
      nx = -zi;
      nz = xi;
      ny = 0;
    }
  }

  /* [xyz]u = [xyz]i x n[xyz] (usually vertical) */
  vec_prod(xu,  yu,  zu, xi, yi, zi,        nx, ny, nz);
  /* [xyz]t = [xyz]i rotated theta around [xyz]u */
  rotate  (xt,  yt,  zt, xi, yi, zi, phi, nx, ny, nz);
  /* [xyz]o = [xyz]t rotated phi around n[xyz] */
  rotate (*xo, *yo, *zo, xt, yt, zt, theta, xu,  yu,  zu);

  /* Go back to local coordinate system */
  tmp = coords_set(*xo, *yo, *zo);
  tmp = rot_apply(A, tmp);
  coords_get(tmp, &*xo, &*yo, &*zo);

}

/* randvec_target_rect_real: Choose random direction towards target at (xi,yi,zi)
 * with given dimension height x width (in meters !).
 *
 * Local emission coordinate is taken into account and corrected for 'order' times.
 * (See remarks posted to mcstas-users by George Apostolopoulus <gapost@ipta.demokritos.gr>)
 *
 * If height or width is zero, choose random direction in full 4PI, no target. 
 * 
 * Traditionally, this routine had the name randvec_target_rect - this is now a
 * a define (see mcstas-r.h) pointing here. If you use the old rouine, you are NOT
 * taking the local emmission coordinate into account. 
*/

void
randvec_target_rect_real(double *xo, double *yo, double *zo, double *solid_angle,
               double xi, double yi, double zi, double width, double height, Rotation A, double lx, double ly, double lz, int order)
{
  double dx, dy, dist, dist_p, nx, ny, nz, mx, my, mz, n_norm, m_norm;
  double cos_theta;
  Coords tmp;
  Rotation Ainverse;

  rot_transpose(A, Ainverse);

  if(height == 0.0 || width == 0.0)
  {
    randvec_target_circle(xo, yo, zo, solid_angle,
               xi, yi, zi, 0);
    return;
  }
  else
  {

    /* Now choose point uniformly on rectangle within width x height */
    dx = width*randpm1()/2.0;
    dy = height*randpm1()/2.0;

    /* Determine distance to target plane*/
    dist = sqrt(xi*xi + yi*yi + zi*zi);
    /* Go to global coordinate system */

    tmp = coords_set(xi, yi, zi);
    tmp = rot_apply(Ainverse, tmp);
    coords_get(tmp, &xi, &yi, &zi);

    /* Determine vector normal to neutron axis (z) and gravity [0 1 0] */
    vec_prod(nx, ny, nz, xi, yi, zi, 0, 1, 0);

    /* This now defines the x-axis, normalize: */
    n_norm=sqrt(nx*nx + ny*ny + nz*nz);
    nx = nx/n_norm;
    ny = ny/n_norm;
    nz = nz/n_norm;

    /* Now, determine our y-axis (vertical in many cases...) */
    vec_prod(mx, my, mz, xi, yi, zi, nx, ny, nz);
    m_norm=sqrt(mx*mx + my*my + mz*mz);
    mx = mx/m_norm;
    my = my/m_norm;
    mz = mz/m_norm;

    /* Our output, random vector can now be defined by linear combination: */

    *xo = xi + dx * nx + dy * mx;
    *yo = yi + dx * ny + dy * my;
    *zo = zi + dx * nz + dy * mz;

    /* Go back to local coordinate system */
    tmp = coords_set(*xo, *yo, *zo);
    tmp = rot_apply(A, tmp);
    coords_get(tmp, &*xo, &*yo, &*zo);

    if (solid_angle) {
      /* Calculate vector from local point to remote random point */
      lx = *xo - lx;
      ly = *yo - ly;
      lz = *zo - lz;
      dist_p = sqrt(lx*lx + ly*ly + lz*lz);
      
      /* Adjust the 'solid angle' */
      /* 1/r^2 to the chosen point times cos(\theta) between the normal */
      /* vector of the target rectangle and direction vector of the chosen point. */
      cos_theta = (xi * lx + yi * ly + zi * lz) / (dist * dist_p);
      *solid_angle = width * height / (dist_p * dist_p); 
      int counter;
      for (counter = 0; counter < order; counter++) {
	*solid_angle = *solid_angle * cos_theta;
      }
    }
  }
}


/* extend_list: Make sure a list is big enough to hold element COUNT.
*
* The list is an array, and the argument 'list' is a pointer to a pointer to
* the array start. The argument 'size' is a pointer to the number of elements
* in the array. The argument 'elemsize' is the sizeof() an element. The
* argument 'count' is the minimum number of elements needed in the list.
*
* If the old array is to small (or if *list is NULL or *size is 0), a
* sufficuently big new array is allocated, and *list and *size are updated.
*/
void extend_list(int count, void **list, int *size, size_t elemsize)
{
  if(count >= *size)
  {
    void *oldlist = *list;
    if(*size > 0)
      *size *= 2;
    else
      *size = 32;
    *list = malloc(*size*elemsize);
    if(!*list)
    {
      exit(fprintf(stderr, "\nError: Out of memory %li (extend_list).\n", (long)*size*elemsize));
    }
    if(oldlist)
    {
      memcpy(*list, oldlist, count*elemsize);
      free(oldlist);
    }
  }
}

/* mcsetn_arg: get ncount from a string argument */
static void
mcsetn_arg(char *arg)
{
  mcset_ncount(strtod(arg, NULL));
}

/* mcsetseed: set the random generator seed from a string argument */
static void
mcsetseed(char *arg)
{
  mcseed = atol(arg);
  if(mcseed) {
#ifdef USE_MPI
    if (mpi_node_count > 1) srandom(mcseed+mpi_node_rank);
    else
#endif
    srandom(mcseed);
  } else {
    fprintf(stderr, "Error: seed must not be zero (mcsetseed)\n");
    exit(1);
  }
}

/* mchelp: displays instrument executable help with possible options */
static void
mchelp(char *pgmname)
{
  int i;

  fprintf(stderr, "Usage: %s [options] [parm=value ...]\n", pgmname);
  fprintf(stderr,
"Options are:\n"
"  -s SEED   --seed=SEED      Set random seed (must be != 0)\n"
"  -n COUNT  --ncount=COUNT   Set number of neutrons to simulate.\n"
"  -d DIR    --dir=DIR        Put all data files in directory DIR.\n"
"  -f FILE   --file=FILE      Put all data in a single file.\n"
"  -t        --trace          Enable trace of neutron through instrument.\n"
"  -g        --gravitation    Enable gravitation for all trajectories.\n"
"  -a        --data-only      Do not put any headers in the data files.\n"
"  --no-output-files          Do not write any data files.\n"
"  -h        --help           Show this help message.\n"
"  -i        --info           Detailed instrument information.\n"
"  --format=FORMAT            Output data files using format FORMAT\n"
"                             (use option +a to include text header in files\n"
#ifdef USE_MPI
"This instrument has been compiled with MPI support. Use 'mpirun'.\n"
#endif
"\n"
);
  if(mcnumipar > 0)
  {
    fprintf(stderr, "Instrument parameters are:\n");
    for(i = 0; i < mcnumipar; i++)
      if (mcinputtable[i].val && strlen(mcinputtable[i].val))
        fprintf(stderr, "  %-16s(%s) [default='%s']\n", mcinputtable[i].name,
        (*mcinputtypes[mcinputtable[i].type].parminfo)(mcinputtable[i].name),
        mcinputtable[i].val);
      else
        fprintf(stderr, "  %-16s(%s)\n", mcinputtable[i].name,
        (*mcinputtypes[mcinputtable[i].type].parminfo)(mcinputtable[i].name));
  }
  fprintf(stderr, "Available output formats are (default is %s):\n  ", mcformat.Name);
  for (i=0; i < mcNUMFORMATS; fprintf(stderr,"\"%s\" " , mcformats[i++].Name) );
  fprintf(stderr, "\n  Format modifiers: FORMAT may be followed by 'binary float' or \n");
  fprintf(stderr, "  'binary double' to save data blocks as binary. This removes text headers.\n");
  fprintf(stderr, "  The MCSTAS_FORMAT environment variable may set the default FORMAT to use.\n");
#ifndef NOSIGNALS
  fprintf(stderr, "Known signals are: "
#ifdef SIGUSR1
  "USR1 (status) "
#endif
#ifdef SIGUSR2
  "USR2 (save) "
#endif
#ifdef SIGBREAK
  "BREAK (save) "
#endif
#ifdef SIGTERM
  "TERM (save and exit)"
#endif
  "\n");
#endif /* !NOSIGNALS */
}

/* mcshowhelp: show help and exit with 0 */
static void
mcshowhelp(char *pgmname)
{
  mchelp(pgmname);
#ifdef USE_MPI
#undef exit
#endif
  exit(0);
#ifdef USE_MPI
#define exit(code) MPI_Abort(MPI_COMM_WORLD, code)
#endif
}

/* mcusage: display usage when error in input arguments and exit with 1 */
static void
mcusage(char *pgmname)
{
  fprintf(stderr, "Error: incorrect command line arguments\n");
  mchelp(pgmname);
  exit(1);
}

/* mcenabletrace: enable trace/mcdisplay or error if requires recompile */
static void
mcenabletrace(void)
{
 if(mctraceenabled)
  mcdotrace = 1;
 else
 {
   fprintf(stderr,
           "Error: trace not enabled (mcenabletrace)\n"
           "Please re-run the McStas compiler "
                   "with the --trace option, or rerun the\n"
           "C compiler with the MC_TRACE_ENABLED macro defined.\n");
   exit(1);
 }
}

/* mcuse_dir: set data/sim storage directory and create it,
 * or exit with error if exists */
static void
mcuse_dir(char *dir)
{
#ifdef MC_PORTABLE
  fprintf(stderr, "Error: "
          "Directory output cannot be used with portable simulation (mcuse_dir)\n");
  exit(1);
#else  /* !MC_PORTABLE */
#ifdef USE_MPI  
    if(mpi_node_rank == mpi_node_root)
    {
#endif
     if(mkdir(dir, 0777)) {
#ifndef DANSE
         fprintf(stderr, "Error: unable to create directory '%s' (mcuse_dir)\n", dir);
         fprintf(stderr, "(Maybe the directory already exists?)\n");       
         exit(1);
#endif
     }
#ifdef USE_MPI
   }
#endif
   mcdirname = dir;
#endif /* !MC_PORTABLE */
}

/* mcinfo: display instrument simulation info to stdout and exit */
static void
mcinfo(void)
{
  if(strstr(mcformat.Name,"NeXus"))
    exit(fprintf(stderr,"Error: Can not display instrument informtion in NeXus binary format\n"));
  mcsiminfo_init(stdout);
  mcsiminfo_close();
#ifdef USE_MPI
#undef exit
#endif
  exit(0);
#ifdef USE_MPI
#define exit(code) MPI_Abort(MPI_COMM_WORLD, code)
#endif
}

/* mcparseoptions: parse command line arguments (options, parameters) */
void
mcparseoptions(int argc, char *argv[])
{
  int i, j;
  char *p;
  int paramset = 0, *paramsetarray;

  /* Add one to mcnumipar to avoid allocating zero size memory block. */
  paramsetarray = malloc((mcnumipar + 1)*sizeof(*paramsetarray));
  if(paramsetarray == NULL)
  {
    fprintf(stderr, "Error: insufficient memory (mcparseoptions)\n");
    exit(1);
  }
  for(j = 0; j < mcnumipar; j++)
    {
      paramsetarray[j] = 0;
      if (mcinputtable[j].val != NULL && strlen(mcinputtable[j].val))
      {
        int  status;
        char buf[CHAR_BUF_LENGTH];
        strncpy(buf, mcinputtable[j].val, CHAR_BUF_LENGTH);
        status = (*mcinputtypes[mcinputtable[j].type].getparm)
                   (buf, mcinputtable[j].par);
        if(!status) fprintf(stderr, "Invalid '%s' default value %s in instrument definition (mcparseoptions)\n", mcinputtable[j].name, buf);
        else paramsetarray[j] = 1;
      } else {
        (*mcinputtypes[mcinputtable[j].type].getparm)
          (NULL, mcinputtable[j].par);
        paramsetarray[j] = 0;
      }
    }
  for(i = 1; i < argc; i++)
  {
    if(!strcmp("-s", argv[i]) && (i + 1) < argc)
      mcsetseed(argv[++i]);
    else if(!strncmp("-s", argv[i], 2))
      mcsetseed(&argv[i][2]);
    else if(!strcmp("--seed", argv[i]) && (i + 1) < argc)
      mcsetseed(argv[++i]);
    else if(!strncmp("--seed=", argv[i], 7))
      mcsetseed(&argv[i][7]);
    else if(!strcmp("-n", argv[i]) && (i + 1) < argc)
      mcsetn_arg(argv[++i]);
    else if(!strncmp("-n", argv[i], 2))
      mcsetn_arg(&argv[i][2]);
    else if(!strcmp("--ncount", argv[i]) && (i + 1) < argc)
      mcsetn_arg(argv[++i]);
    else if(!strncmp("--ncount=", argv[i], 9))
      mcsetn_arg(&argv[i][9]);
    else if(!strcmp("-d", argv[i]) && (i + 1) < argc)
      mcuse_dir(argv[++i]);
    else if(!strncmp("-d", argv[i], 2))
      mcuse_dir(&argv[i][2]);
    else if(!strcmp("--dir", argv[i]) && (i + 1) < argc)
      mcuse_dir(argv[++i]);
    else if(!strncmp("--dir=", argv[i], 6))
      mcuse_dir(&argv[i][6]);
    else if(!strcmp("-f", argv[i]) && (i + 1) < argc)
      mcuse_file(argv[++i]);
    else if(!strncmp("-f", argv[i], 2))
      mcuse_file(&argv[i][2]);
    else if(!strcmp("--file", argv[i]) && (i + 1) < argc)
      mcuse_file(argv[++i]);
    else if(!strncmp("--file=", argv[i], 7))
      mcuse_file(&argv[i][7]);
    else if(!strcmp("-h", argv[i]))
      mcshowhelp(argv[0]);
    else if(!strcmp("--help", argv[i]))
      mcshowhelp(argv[0]);
    else if(!strcmp("-i", argv[i])) {
      mcformat=mcuse_format(MCSTAS_FORMAT);
      mcinfo();
    }
    else if(!strcmp("--info", argv[i]))
      mcinfo();
    else if(!strcmp("-t", argv[i]))
      mcenabletrace();
    else if(!strcmp("--trace", argv[i]))
      mcenabletrace();
    else if(!strcmp("-a", argv[i]))
      mcascii_only = 1;
    else if(!strcmp("+a", argv[i]))
      mcascii_only = 0;
    else if(!strcmp("--data-only", argv[i]))
      mcascii_only = 1;
    else if(!strcmp("--gravitation", argv[i]))
      mcgravitation = 1;
    else if(!strcmp("-g", argv[i]))
      mcgravitation = 1;
    else if(!strncmp("--format=", argv[i], 9)) {
      mcascii_only = 0;
      mcformat=mcuse_format(&argv[i][9]);
    }
    else if(!strcmp("--format", argv[i]) && (i + 1) < argc) {
      mcascii_only = 0;
      mcformat=mcuse_format(argv[++i]);
    }
    else if(!strncmp("--format_data=", argv[i], 14) || !strncmp("--format-data=", argv[i], 14)) {
      mcascii_only = 0;
      mcformat_data=mcuse_format(&argv[i][14]);
    }
    else if((!strcmp("--format_data", argv[i]) || !strcmp("--format-data", argv[i])) && (i + 1) < argc) {
      mcascii_only = 0;
      mcformat_data=mcuse_format(argv[++i]);
    }
    else if(!strcmp("--no-output-files", argv[i]))
      mcdisable_output_files = 1;   
    else if(argv[i][0] != '-' && (p = strchr(argv[i], '=')) != NULL)
    {
      *p++ = '\0';

      for(j = 0; j < mcnumipar; j++)
        if(!strcmp(mcinputtable[j].name, argv[i]))
        {
          int status;
          status = (*mcinputtypes[mcinputtable[j].type].getparm)(p,
                        mcinputtable[j].par);
          if(!status || !strlen(p))
          {
            (*mcinputtypes[mcinputtable[j].type].error)
              (mcinputtable[j].name, p);
            exit(1);
          }
          paramsetarray[j] = 1;
          paramset = 1;
          break;
        }
      if(j == mcnumipar)
      {                                /* Unrecognized parameter name */
        fprintf(stderr, "Error: unrecognized parameter %s (mcparseoptions)\n", argv[i]);
        exit(1);
      }
    }
    else if(argv[i][0] == '-') {
      fprintf(stderr, "Error: unrecognized option argument %s (mcparseoptions). Ignored.\n", argv[i++]);
    }
    else
      mcusage(argv[0]);
  }
  if (!mcascii_only) {
    if (strstr(mcformat.Name,"binary")) fprintf(stderr, "Warning: %s files will contain text headers.\n         Use -a option to clean up.\n", mcformat.Name);
    strcat(mcformat.Name, " with text headers");
  }
  if(!paramset)
    mcreadparams();                /* Prompt for parameters if not specified. */
  else
  {
    for(j = 0; j < mcnumipar; j++)
      if(!paramsetarray[j])
      {
        fprintf(stderr, "Error: Instrument parameter %s left unset (mcparseoptions)\n",
                mcinputtable[j].name);
        exit(1);
      }
  }
  free(paramsetarray);
#ifdef USE_MPI
  if (mcdotrace) mpi_node_count=1; /* disable threading when in trace mode */
#endif
} /* mcparseoptions */

#ifndef NOSIGNALS
mcstatic char  mcsig_message[256];  /* ADD: E. Farhi, Sep 20th 2001 */


/* sighandler: signal handler that makes simulation stop, and save results */
void sighandler(int sig)
{
  /* MOD: E. Farhi, Sep 20th 2001: give more info */
  time_t t1, t0;
#define SIG_SAVE 0
#define SIG_TERM 1
#define SIG_STAT 2
#define SIG_ABRT 3

  printf("\n# McStas: [pid %i] Signal %i detected", getpid(), sig);
#if defined(SIGUSR1) && defined(SIGUSR2) && defined(SIGKILL)
  if (!strcmp(mcsig_message, "sighandler") && (sig != SIGUSR1) && (sig != SIGUSR2))
  {
    printf("\n# Fatal : unrecoverable loop ! Suicide (naughty boy).\n");
    kill(0, SIGKILL); /* kill myself if error occurs within sighandler: loops */
  }
#endif
  switch (sig) {
#ifdef SIGINT
    case SIGINT : printf(" SIGINT (interrupt from terminal, Ctrl-C)"); sig = SIG_TERM; break;
#endif
#ifdef SIGILL
    case SIGILL  : printf(" SIGILL (Illegal instruction)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGFPE
    case SIGFPE  : printf(" SIGFPE (Math Error)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGSEGV
    case SIGSEGV : printf(" SIGSEGV (Mem Error)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGTERM
    case SIGTERM : printf(" SIGTERM (Termination)"); sig = SIG_TERM; break;
#endif
#ifdef SIGABRT
    case SIGABRT : printf(" SIGABRT (Abort)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGQUIT
    case SIGQUIT : printf(" SIGQUIT (Quit from terminal)"); sig = SIG_TERM; break;
#endif
#ifdef SIGTRAP
    case SIGTRAP : printf(" SIGTRAP (Trace trap)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGPIPE
    case SIGPIPE : printf(" SIGPIPE (Broken pipe)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGUSR1
    case SIGUSR1 : printf(" SIGUSR1 (Display info)"); sig = SIG_STAT; break;
#endif
#ifdef SIGUSR2
    case SIGUSR2 : printf(" SIGUSR2 (Save simulation)"); sig = SIG_SAVE; break;
#endif
#ifdef SIGHUP
    case SIGHUP  : printf(" SIGHUP (Hangup/update)"); sig = SIG_SAVE; break;
#endif
#ifdef SIGBUS
    case SIGBUS  : printf(" SIGBUS (Bus error)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGURG
    case SIGURG  : printf(" SIGURG (Urgent socket condition)"); sig = SIG_ABRT; break;
#endif
#ifdef SIGBREAK
    case SIGBREAK: printf(" SIGBREAK (Break signal, Ctrl-Break)"); sig = SIG_SAVE; break;
#endif
    default : printf(" (look at signal list for signification)"); sig = SIG_ABRT; break;
  }
  printf("\n");
  printf("# Simulation: %s (%s) \n", mcinstrument_name, mcinstrument_source);
  printf("# Breakpoint: %s ", mcsig_message);
  if (strstr(mcsig_message, "Save") && (sig == SIG_SAVE))
    sig = SIG_STAT;
  SIG_MESSAGE("sighandler");
  if (mcget_ncount() == 0)
    printf("(0 %%)\n" );
  else
  {
    printf("%.2f %% (%10.1f/%10.1f)\n", 100*mcget_run_num()/mcget_ncount(), mcget_run_num(), mcget_ncount());
  }
  t0 = (time_t)mcstartdate;
  t1 = time(NULL);
  printf("# Date:      %s", ctime(&t1));
  printf("# Started:   %s", ctime(&t0));

  if (sig == SIG_STAT)
  {
    printf("# McStas: Resuming simulation (continue)\n");
    fflush(stdout);
    return;
  }
  else
  if (sig == SIG_SAVE)
  {
    printf("# McStas: Saving data and resume simulation (continue)\n");
    mcsave(NULL);
    fflush(stdout);
    return;
  }
  else
  if (sig == SIG_TERM)
  {
    printf("# McStas: Finishing simulation (save results and exit)\n");
    mcfinally();
    exit(0);
  }
  else
  {
    fflush(stdout);
    perror("# Last I/O Error");
    printf("# McStas: Simulation stop (abort)\n");
    exit(-1);
  }
#undef SIG_SAVE
#undef SIG_TERM
#undef SIG_STAT
#undef SIG_ABRT

}
#endif /* !NOSIGNALS */

/* main raytrace loop */
void *mcstas_raytrace(void *p_node_ncount)
{
  double node_ncount = *((double*)p_node_ncount);
  
  while(mcrun_num < node_ncount || mcrun_num < mcget_ncount())
  {
    mcsetstate(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    /* old init: mcsetstate(0, 0, 0, 0, 0, 1, 0, sx=0, sy=1, sz=0, 1); */
    mcraytrace();
    mcrun_num++;
  }
  return (NULL);
}

/* mcstas_main: McStas main() function. */
int mcstas_main(int argc, char *argv[])
{
/*  double run_num = 0; */
  time_t t;
#ifdef USE_MPI
  char mpi_node_name[MPI_MAX_PROCESSOR_NAME];
  int  mpi_node_name_len;
#endif /* USE_MPI */
#if defined (USE_MPI)
  double mpi_mcncount;
#endif /* USE_MPI */

#ifdef MAC
  argc = ccommand(&argv);
#endif

#ifdef USE_MPI
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_node_count); /* get number of nodes */
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_node_rank);
  MPI_Get_processor_name(mpi_node_name, &mpi_node_name_len);
#endif /* USE_MPI */

/* *** print number of nodes *********************************************** */
  t = (time_t)mcstartdate;
#ifdef USE_MPI
  if (mpi_node_count > 1) {
    MPI_MASTER(
    printf("Simulation %s (%s) running on %i nodes (master is %s, MPI version %i.%i).\n", 
      mcinstrument_name, mcinstrument_source, mpi_node_count, mpi_node_name, MPI_VERSION, MPI_SUBVERSION);
    );
    /* adapt random seed for each node */
    srandom(time(&t) + mpi_node_rank);
    t += mpi_node_rank;
  }
#else /* !USE_MPI */
  srandom(time(&t));
#endif /* !USE_MPI */
  mcstartdate = t;  /* set start date before parsing options and creating sim file */

/* *** parse options ******************************************************* */
  SIG_MESSAGE("main (Start)");
  mcformat=mcuse_format(getenv("MCSTAS_FORMAT") ? getenv("MCSTAS_FORMAT") : MCSTAS_FORMAT);
  /* default is to output as McStas format */
  mcformat_data.Name=NULL;
  /* read simulation parameters and options */
  mcparseoptions(argc, argv); /* sets output dir and format */
  if (strstr(mcformat.Name, "NeXus")) {
    if (mcformat_data.Name) mcclear_format(mcformat_data);
    mcformat_data.Name=NULL;
  }
  if (!mcformat_data.Name && strstr(mcformat.Name, "HTML"))
    mcformat_data = mcuse_format("VRML");

/* *** install sig handler, but only once !! after parameters parsing ******* */
#ifndef NOSIGNALS
#ifdef SIGQUIT
  signal( SIGQUIT ,sighandler);   /* quit (ASCII FS) */
#endif
#ifdef SIGABRT
  signal( SIGABRT ,sighandler);   /* used by abort, replace SIGIOT in the future */
#endif
#ifdef SIGTERM
  signal( SIGTERM ,sighandler);   /* software termination signal from kill */
#endif
#ifdef SIGUSR1
  signal( SIGUSR1 ,sighandler);   /* display simulation status */
#endif
#ifdef SIGUSR2
  signal( SIGUSR2 ,sighandler);
#endif
#ifdef SIGHUP
  signal( SIGHUP ,sighandler);
#endif
#ifdef SIGILL
  signal( SIGILL ,sighandler);    /* illegal instruction (not reset when caught) */
#endif
#ifdef SIGFPE
  signal( SIGFPE ,sighandler);    /* floating point exception */
#endif
#ifdef SIGBUS
  signal( SIGBUS ,sighandler);    /* bus error */
#endif
#ifdef SIGSEGV
  signal( SIGSEGV ,sighandler);   /* segmentation violation */
#endif
#endif /* !NOSIGNALS */
  if (!strstr(mcformat.Name,"NeXus")) {
    mcsiminfo_init(NULL); mcsiminfo_close();  /* makes sure we can do that */
  }
  SIG_MESSAGE("main (Init)");
  mcinit();
#ifndef NOSIGNALS
#ifdef SIGINT
  signal( SIGINT ,sighandler);    /* interrupt (rubout) only after INIT */
#endif
#endif /* !NOSIGNALS */

/* ================ main neutron generation/propagation loop ================ */
#if defined (USE_MPI)
  mpi_mcncount = mpi_node_count > 1 ?
    floor(mcncount / mpi_node_count) :
    mcncount; /* number of neutrons per node */
  mcncount = mpi_mcncount;  /* sliced Ncount on each MPI node */
#endif

/* main neutron event loop */
mcstas_raytrace(&mcncount);

#ifdef USE_MPI
 /* merge data from MPI nodes */
  if (mpi_node_count > 1) {
  MPI_Barrier(MPI_COMM_WORLD);
  mc_MPI_Reduce(&mcrun_num, &mcrun_num, 1, MPI_DOUBLE, MPI_SUM, mpi_node_root, MPI_COMM_WORLD);
  }
#endif

/* save/finally executed by master node/thread */
  mcfinally();
  mcclear_format(mcformat);
  if (mcformat_data.Name) mcclear_format(mcformat_data);

#ifdef USE_MPI
  MPI_Finalize();
#endif /* USE_MPI */

  return 0;
} /* mcstas_main */

#endif /* !MCSTAS_H */
/* End of file "mcstas-r.c". */

#line 6941 "SEQ_11_09_2009.c"
#ifdef MC_TRACE_ENABLED
int mctraceenabled = 1;
#else
int mctraceenabled = 0;
#endif
#define MCSTAS "/usr/local/lib/mcstas/"
int mcdefaultmain = 1;
char mcinstrument_name[] = "Fermi_T0";
char mcinstrument_source[] = "SEQ_11_09_2009.instr";
int main(int argc, char *argv[]){return mcstas_main(argc, argv);}
void mcinit(void);
void mcraytrace(void);
void mcsave(FILE *);
void mcfinally(void);
void mcdisplay(void);

/* Shared user declarations for all components 'Vertical_T0a'. */
#line 36 "Vertical_T0a.comp"
#ifndef FERMI_CHOP_DEFS
#define FERMI_CHOP_DEFS   
    /* routine to calculate acos in proper quadrant  range = 0 to 2PI*/ 
    double acos0_2pi(double x,double y)
     {
       if (y>0.0){ 
         return acos(x);
       }
         return 2.0*PI-acos(x);
     }
   /*routine to calculate x and y positions of a neutron in a fermi chopper */
   void neutxypos(double *x, double *y, double phi, double inrad,double c[])
    {      
        *x=c[0]+inrad*cos(phi);
        *y=c[1]+inrad*sin(phi);
    }
    /* routine to calculate the origin of a circle that describes the neutron path through the chopper */  
    void calccenter(double c[],double zr[], double xr[]){
      double denom, A,B,C,D,a,b;
      denom=2*(-zr[0]*xr[2] +zr[0]*xr[1]+ zr[1]*xr[2]+xr[0]*zr[2]-xr[0]*zr[1] - xr[1]*zr[2]);
       A=xr[1]-xr[2];B=xr[0]-xr[1];C=zr[2]-zr[1];D=zr[1]-zr[0];
       a=zr[0]*zr[0]-zr[1]*zr[1]+xr[0]*xr[0]-xr[1]*xr[1];
       b=zr[2]*zr[2]-zr[1]*zr[1]+xr[2]*xr[2]-xr[1]*xr[1];
       c[0]=1.0/denom*(A*a+B*b);
       c[1]=1.0/denom*(C*a+D*b);  
    }
#endif
#line 6987 "SEQ_11_09_2009.c"

/* Shared user declarations for all components 'Fermi_chop2a'. */
#line 39 "Fermi_chop2a.comp"
#ifndef FERMI_CHOP_DEFS
#define FERMI_CHOP_DEFS   
    /* routine to calculate acos in proper quadrant  range = 0 to 2PI*/ 
    double acos0_2pi(double x,double y)
     {
       if (y>0.0){ 
         return acos(x);
       }
         return 2.0*PI-acos(x);
     }
   /*routine to calculate x and y positions of a neutron in a fermi chopper */
   void neutxypos(double *x, double *y, double phi, double inrad,double c[])
    {      
        *x=c[0]+inrad*cos(phi);
        *y=c[1]+inrad*sin(phi);
    }
    /* routine to calculate the origin of a circle that describes the neutron path through the chopper */  
    void calccenter(double c[],double zr[], double xr[]){
      double denom, A,B,C,D,a,b;
      denom=2*(-zr[0]*xr[2] +zr[0]*xr[1]+ zr[1]*xr[2]+xr[0]*zr[2]-xr[0]*zr[1] - xr[1]*zr[2]);
       A=xr[1]-xr[2];B=xr[0]-xr[1];C=zr[2]-zr[1];D=zr[1]-zr[0];
       a=zr[0]*zr[0]-zr[1]*zr[1]+xr[0]*xr[0]-xr[1]*xr[1];
       b=zr[2]*zr[2]-zr[1]*zr[1]+xr[2]*xr[2]-xr[1]*xr[1];
       c[0]=1.0/denom*(A*a+B*b);
       c[1]=1.0/denom*(C*a+D*b);  
    }

#endif
#line 7019 "SEQ_11_09_2009.c"

/* Shared user declarations for all components 'Monitor_nD'. */
#line 215 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/monitor_nd-lib.h
*
* %Identification
* Written by: EF
* Date: Aug 28, 2002
* Origin: ILL
* Release: McStas 1.12a
* Version: $Revision: 1.17 $
*
* This file is to be imported by the monitor_nd related components
* It handles some shared functions.
*
* Usage: within SHARE
* %include "monitor_nd-lib"
*
* $Id: monitor_nd-lib.h,v 1.17 2008/04/01 09:15:04 farhi Exp $
*
* $Log: monitor_nd-lib.h,v $
* Revision 1.17  2008/04/01 09:15:04  farhi
* Monitor_nD now accepts up to 3 user variables, e.g. for coordinates
* to be stored into "list".
*
* Revision 1.16  2006/07/21 14:09:07  farhi
* Fix wrong structure member
*
* Revision 1.15  2006/07/21 09:03:23  farhi
* Added in options'per steradian' flux estimate, and possibility to glue the
* monitor to the shape of the 'previous' component (unactivate propagation), so
* that we can mnonitor what's going on at the output surface of the previous comp.
*
* Revision 1.14  2005/08/24 13:14:40  lieutenant
* new option 'exclusive'
*
* Revision 1.13  2005/07/25 14:55:08  farhi
* DOC update:
* checked all parameter [unit] + text to be OK
* set all versions to CVS Revision
*
* Revision 1.12  2005/07/04 08:20:16  farhi
* added support for radial distributions vxy kxy and xy=radius
*
* Revision 1.11  2005/02/22 16:11:03  farhi
* Now saving absolute position of monitors as "position" field in header
* Useful for plotting e.g. flux vs distance
*
* Revision 1.10  2005/01/18 10:35:56  farhi
* Intall new MACROs for easy User Variable usage in Monitor_nD
* MONND_DECLARE(comp)
* MONND_USER_TITLE(comp, num, title)
* MONND_USER_VALUE(comp, num, value)
* comp is the name of a Monitor_nD component; num is 1 or 2 for UserVariable
*
* Revision 1.9  2004/11/30 16:11:37  farhi
* defined some macros for an easier User variable handling. Should be updated in the header and Comp doc
*
* Revision 1.8  2003/02/11 12:28:46  farhi
* Variouxs bug fixes after tests in the lib directory
* mcstas_r  : disable output with --no-out.. flag. Fix 1D McStas output
* read_table:corrected MC_SYS_DIR -> MCSTAS define
* monitor_nd-lib: fix Log(signal) log(coord)
* HOPG.trm: reduce 4000 points -> 400 which is enough and faster to resample
* Progress_bar: precent -> percent parameter
* CS: ----------------------------------------------------------------------
*
* Revision 1.1 2002/08/28 11:39:00 ef
* Initial revision extracted from lib/monitors/Monitor_nD.comp
*******************************************************************************/

#ifndef MONITOR_ND_LIB_H

#define MONITOR_ND_LIB_H "1.1.1"
#define MONnD_COORD_NMAX  30  /* max number of variables to record */

  typedef struct MonitornD_Defines
  {
    char COORD_NONE  ;
    char COORD_X     ;
    char COORD_Y     ;
    char COORD_Z     ;
    char COORD_VX    ;
    char COORD_VY    ;
    char COORD_VZ    ;
    char COORD_T     ;
    char COORD_P     ;
    char COORD_SX    ;
    char COORD_SY    ;
    char COORD_SZ    ;
    char COORD_KX    ;
    char COORD_KY    ;
    char COORD_KZ    ;
    char COORD_K     ;
    char COORD_V     ;
    char COORD_ENERGY;
    char COORD_LAMBDA;
    char COORD_RADIUS;
    char COORD_KXY   ;
    char COORD_VXY   ;
    char COORD_HDIV  ;
    char COORD_VDIV  ;
    char COORD_ANGLE ;
    char COORD_NCOUNT;
    char COORD_THETA ;
    char COORD_PHI   ;
    char COORD_USER1 ;
    char COORD_USER2 ;
    char COORD_USER3 ;

    /* token modifiers */
    char COORD_VAR   ; /* next token should be a variable or normal option */
    char COORD_MIN   ; /* next token is a min value */
    char COORD_MAX   ; /* next token is a max value */
    char COORD_DIM   ; /* next token is a bin value */
    char COORD_FIL   ; /* next token is a filename */
    char COORD_EVNT  ; /* next token is a buffer size value */
    char COORD_3HE   ; /* next token is a 3He pressure value */
    char COORD_INTERM; /* next token is an intermediate save value (percent) */
    char COORD_LOG   ; /* next variable will be in log scale */
    char COORD_ABS   ; /* next variable will be in abs scale */
    char COORD_SIGNAL; /* next variable will be the signal var */
    int  COORD_AUTO  ; /* set auto limits */

    char TOKEN_DEL[32]; /* token separators */

    char SHAPE_SQUARE; /* shape of the monitor */
    char SHAPE_DISK  ;
    char SHAPE_SPHERE;
    char SHAPE_CYLIND;
    char SHAPE_BANANA; /* cylinder without top/bottom, on restricted angular area */
    char SHAPE_BOX   ;
    char SHAPE_PREVIOUS;

  } MonitornD_Defines_type;

  typedef struct MonitornD_Variables
  {
    double area, steradian;
    double Sphere_Radius     ;
    double Cylinder_Height   ;
    char   Flag_With_Borders ;   /* 2 means xy borders too */
    char   Flag_List         ;   /* 1 store 1 buffer, 2 is list all, 3 list all+append */
    char   Flag_Multiple     ;   /* 1 when n1D, 0 for 2D */
    char   Flag_Verbose      ;
    int    Flag_Shape        ;
    char   Flag_Auto_Limits  ;   /* get limits from first Buffer */
    char   Flag_Absorb       ;   /* monitor is also a slit */
    char   Flag_Exclusive    ;   /* absorb neutrons out of monitor limits */
    char   Flag_per_cm2      ;   /* flux is per cm2 */
    char   Flag_per_st       ;   /* flux is per steradian */
    char   Flag_log          ;   /* log10 of the flux */
    char   Flag_parallel     ;   /* set neutron state back after detection (parallel components) */
    char   Flag_Binary_List  ;
    char   Flag_capture      ;   /* lambda monitor with lambda/lambda(2200m/s = 1.7985 Angs) weightening */
    int    Flag_signal       ;   /* 0:monitor p, else monitor a mean value */

    long   Coord_Number      ;   /* total number of variables to monitor, plus intensity (0) */
    long   Buffer_Block      ;   /* Buffer size for list or auto limits */
    long   Neutron_Counter   ;   /* event counter, simulation total counts is mcget_ncount() */
    long   Buffer_Counter    ;   /* index in Buffer size (for realloc) */
    long   Buffer_Size       ;
    int    Coord_Type[MONnD_COORD_NMAX];    /* type of variable */
    char   Coord_Label[MONnD_COORD_NMAX][30];       /* label of variable */
    char   Coord_Var[MONnD_COORD_NMAX][30]; /* short id of variable */
    long   Coord_Bin[MONnD_COORD_NMAX];             /* bins of variable array */
    double Coord_Min[MONnD_COORD_NMAX];
    double Coord_Max[MONnD_COORD_NMAX];
    char   Monitor_Label[MONnD_COORD_NMAX*30];      /* Label for monitor */
    char   Mon_File[128];    /* output file name */

    double cx,cy,cz;
    double cvx, cvy, cvz;
    double csx, csy, csz;
    double cs1, cs2, ct, cp;
    double He3_pressure;
    char   Flag_UsePreMonitor    ;   /* use a previously stored neutron parameter set */
    char   UserName1[128];
    char   UserName2[128];
    char   UserName3[128];
    double UserVariable1;
    double UserVariable2;
    double UserVariable3;
    double Intermediate;
    double IntermediateCnts;
    char   option[1024];

    double Nsum;
    double psum, p2sum;
    double **Mon2D_N;
    double **Mon2D_p;
    double **Mon2D_p2;
    double *Mon2D_Buffer;

    double mxmin,mxmax,mymin,mymax,mzmin,mzmax;
    double mean_dx, mean_dy, min_x, min_y, max_x, max_y, mean_p;

    char   compcurname[128];
    Coords compcurpos;

  } MonitornD_Variables_type;

/* monitor_nd-lib function prototypes */
/* ========================================================================= */

void Monitor_nD_Init(MonitornD_Defines_type *, MonitornD_Variables_type *, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM, MCNUM);
double Monitor_nD_Trace(MonitornD_Defines_type *, MonitornD_Variables_type *);
void Monitor_nD_Save(MonitornD_Defines_type *, MonitornD_Variables_type *);
void Monitor_nD_Finally(MonitornD_Defines_type *, MonitornD_Variables_type *);
void Monitor_nD_McDisplay(MonitornD_Defines_type *,
 MonitornD_Variables_type *);

#define MONND_DECLARE(monname) \
  struct MonitornD_Variables *mcmonnd ## monname;
#define MONND_USER_TITLE(monname, num, title) \
  { mcmonnd ## monname = &(MC_GETPAR(monname, Vars)); \
    strcpy(mcmonnd ## monname->UserName ## num, title); }
#define MONND_USER_VALUE(monname, num, value) \
  { mcmonnd ## monname = &(MC_GETPAR(monname, Vars)); \
    mcmonnd ## monname->UserVariable ## num = (value); }

#endif

/* end of monitor_nd-lib.h */
/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Library: share/monitor_nd-lib.c
*
* %Identification
* Written by: EF
* Date: Aug 28, 2002
* Origin: ILL
* Release: McStas 1.12a
* Version: $Revision: 1.41 $
*
* This file is to be imported by the monitor_nd related components
* It handles some shared functions. Embedded within instrument in runtime mode.
* Variable names have prefix 'mc_mn_' for 'McStas Monitor' to avoid conflicts
*
* Usage: within SHARE
* %include "monitor_nd-lib"
*
* $Id: monitor_nd-lib.c,v 1.41 2008/07/01 20:28:13 farhi Exp $
*
* $Log: monitor_nd-lib.c,v $
* Revision 1.41  2008/07/01 20:28:13  farhi
* Fixed zthick -> zdepth
*
* Revision 1.40  2008/07/01 19:50:23  farhi
* Common naming convention for components:
*   xwidth, yheight, zdepth, radius, thickness
*   sigma_abs, sigma_inc
*
* Revision 1.39  2008/04/06 14:02:41  pkwi
* Intel C compiler version 10.1 series fail with Monitor_nD (All events absorbed)....
* The inserted empty printf seems to solve this?!
*
* I will try to file a support request at Intel on this problem...
*
* Revision 1.38  2008/04/01 09:15:04  farhi
* Monitor_nD now accepts up to 3 user variables, e.g. for coordinates
* to be stored into "list".
*
* Revision 1.37  2007/04/02 12:13:13  farhi
* Fixed length of username1|2 to avoid buffer overflow.
*
* Revision 1.36  2006/11/16 10:14:21  farhi
* Correct mcdisplay section with restricted banana/sphere (skipped last monitored variable)
*
* Revision 1.35  2006/07/21 09:03:23  farhi
* Added in options'per steradian' flux estimate, and possibility to glue the
* monitor to the shape of the 'previous' component (unactivate propagation), so
* that we can mnonitor what's going on at the output surface of the previous comp.
*
* Revision 1.34  2006/03/15 16:01:43  farhi
* 'keyword ignored' warning only in verbose mode
*
* Revision 1.33  2005/12/12 13:42:11  farhi
* Corrected bug on multiple limits specifications (K. Lieutenant)
*
* Revision 1.32  2005/09/19 15:13:53  farhi
* using 'y' variable also sets limits to detector dimensions, to enable 'banana' view without troubles.
*
* Revision 1.31  2005/09/16 08:43:19  farhi
* Removed floor+0.5 in Monitor_nD
* Take care of ploting with bin centers in mcplot stuff (inline+matlab+scilab+octave...)
*
* Revision 1.30  2005/08/24 13:14:00  lieutenant
* new option 'exclusive'
*
* Revision 1.29  2005/07/25 14:55:08  farhi
* DOC update:
* checked all parameter [unit] + text to be OK
* set all versions to CVS Revision
*
* Revision 1.28  2005/07/18 14:38:00  farhi
* Added 0.5 top all floor's so that bin are centered (at last)
*
* Revision 1.27  2005/07/06 08:16:28  farhi
* Misprint for Kxy/Vxy. Better Variable name as well.
*
* Revision 1.26  2005/07/04 08:19:50  farhi
* added support for kxy and vxy radial distributions
*
* Revision 1.25  2005/04/11 11:40:44  farhi
* Added missing n-dims argument to printf for capture flux warning
*
* Revision 1.24  2005/03/14 10:48:54  farhi
* Added warning when setting capture flux (meaningful with integral flux) for
* more than 1 bin.
*
* Revision 1.23  2005/02/25 15:26:02  farhi
* Removed usage of round function
* made Guide_honeycomb work with gravitation
*
* Revision 1.22  2005/02/22 16:11:03  farhi
* Now saving absolute position of monitors as "position" field in header
* Useful for plotting e.g. flux vs distance
*
* Revision 1.21  2005/02/21 16:05:13  farhi
* Misprint correction
*
* Revision 1.20  2005/02/21 12:38:03  farhi
* Removed warning in Monitor_nD for global scope keywords in options
*
* Revision 1.19  2005/02/17 16:06:32  farhi
* Added 'per bin' to labels if more than 1 bin, and a message for unknow keywords found in options parameter. Requested by R. Cubitt.
*
* Revision 1.18  2004/11/16 13:36:35  farhi
* Paging update
*
* Revision 1.17  2004/09/01 13:54:18  farhi
* Corrected bug when using list=EVNTS large values written as float, read as int.
* E.g. 1e6 gave 1 as number of events to save !
*
* Revision 1.16  2004/06/30 12:13:47  farhi
* For lists (and Res_monitor), uses 'list' 'no header' and 'no footer' options
* in mcformat.Name so that catenated file does contain only one instance of
* footer and header.
*
* Revision 1.15  2004/02/26 12:55:41  farhi
* Handles 0d monitor outputs for bins=0, and limits are restrictive (i.e. neutron must be within all limits to be stored in monitor)
*
* Revision 1.14  2004/02/04 18:01:12  farhi
* Use hdiv=theta and vdiv=phi for banana.
*
* Revision 1.13  2003/08/26 12:33:27  farhi
* Corrected computation of angle PHI (was projected on vertical plane)
*
* Revision 1.12  2003/04/15 16:01:28  farhi
* incoming/outgoing syntax mismatch correction
*
* Revision 1.11  2003/04/15 15:45:56  farhi
* outgoing time is default (vs. incoming)
*
* Revision 1.10  2003/04/09 15:49:25  farhi
* corrected bug when no signal and auto limits requested
*
* Revision 1.9  2003/02/18 09:11:36  farhi
* Corrected binary format for lists
*
* Revision 1.1 2002/08/28 11:39:00 ef
* Initial revision extracted from lib/monitors/Monitor_nD.comp
*******************************************************************************/

#ifndef MONITOR_ND_LIB_H
#error McStas : please import this library with %include "monitor_nd-lib"
#endif

/* ========================================================================= */
/* ADD: E.Farhi, Aug 6th, 2001: Monitor_nD section */
/* this routine is used to parse options */
/* ========================================================================= */

void Monitor_nD_Init(MonitornD_Defines_type *mc_mn_DEFS,
  MonitornD_Variables_type *mc_mn_Vars,
  MCNUM mc_mn_xwidth,
  MCNUM mc_mn_yheight,
  MCNUM mc_mn_zdepth,
  MCNUM mc_mn_xmin,
  MCNUM mc_mn_xmax,
  MCNUM mc_mn_ymin,
  MCNUM mc_mn_ymax,
  MCNUM mc_mn_zmin,
  MCNUM mc_mn_zmax)
  {
    long mc_mn_carg = 1;
    char *mc_mn_option_copy, *mc_mn_token;
    char mc_mn_Flag_New_token = 1;
    char mc_mn_Flag_End       = 1;
    char mc_mn_Flag_All       = 0;
    char mc_mn_Flag_No        = 0;
    char mc_mn_Flag_abs       = 0;
    int  mc_mn_Flag_auto      = 0;  /* -1: all, 1: the current variable */
    int  mc_mn_Set_Vars_Coord_Type;
    char mc_mn_Set_Vars_Coord_Label[64];
    char mc_mn_Set_Vars_Coord_Var[64];
    char mc_mn_Short_Label[MONnD_COORD_NMAX][64];
    int  mc_mn_Set_Coord_Mode;
    long mc_mn_i=0, mc_mn_j=0;
    double mc_mn_lmin, mc_mn_lmax, mc_mn_XY;
    long mc_mn_t;


    mc_mn_t = (long)time(NULL);

    mc_mn_DEFS->COORD_NONE   =0;
    mc_mn_DEFS->COORD_X      =1;
    mc_mn_DEFS->COORD_Y      =2;
    mc_mn_DEFS->COORD_Z      =3;
    mc_mn_DEFS->COORD_VX     =4;
    mc_mn_DEFS->COORD_VY     =5;
    mc_mn_DEFS->COORD_VZ     =6;
    mc_mn_DEFS->COORD_T      =7;
    mc_mn_DEFS->COORD_P      =8;
    mc_mn_DEFS->COORD_SX     =9;
    mc_mn_DEFS->COORD_SY     =10;
    mc_mn_DEFS->COORD_SZ     =11;
    mc_mn_DEFS->COORD_KX     =12;
    mc_mn_DEFS->COORD_KY     =13;
    mc_mn_DEFS->COORD_KZ     =14;
    mc_mn_DEFS->COORD_K      =15;
    mc_mn_DEFS->COORD_V      =16;
    mc_mn_DEFS->COORD_ENERGY =17;
    mc_mn_DEFS->COORD_LAMBDA =18;
    mc_mn_DEFS->COORD_RADIUS =19;
    mc_mn_DEFS->COORD_HDIV   =20;
    mc_mn_DEFS->COORD_VDIV   =21;
    mc_mn_DEFS->COORD_ANGLE  =22;
    mc_mn_DEFS->COORD_NCOUNT =23;
    mc_mn_DEFS->COORD_THETA  =24;
    mc_mn_DEFS->COORD_PHI    =25;
    mc_mn_DEFS->COORD_USER1  =26;
    mc_mn_DEFS->COORD_USER2  =27;
    mc_mn_DEFS->COORD_USER3  =28;
    mc_mn_DEFS->COORD_KXY    =29;
    mc_mn_DEFS->COORD_VXY    =30;

/* mc_mn_token modifiers */
    mc_mn_DEFS->COORD_VAR    =0;    /* next mc_mn_token should be a variable or normal option */
    mc_mn_DEFS->COORD_MIN    =1;    /* next mc_mn_token is a min value */
    mc_mn_DEFS->COORD_MAX    =2;    /* next mc_mn_token is a max value */
    mc_mn_DEFS->COORD_DIM    =3;    /* next mc_mn_token is a bin value */
    mc_mn_DEFS->COORD_FIL    =4;    /* next mc_mn_token is a filename */
    mc_mn_DEFS->COORD_EVNT   =5;    /* next mc_mn_token is a buffer size value */
    mc_mn_DEFS->COORD_3HE    =6;    /* next mc_mn_token is a 3He pressure value */
    mc_mn_DEFS->COORD_INTERM =7;    /* next mc_mn_token is an intermediate save value (%) */
    mc_mn_DEFS->COORD_LOG    =32;   /* next variable will be in log scale */
    mc_mn_DEFS->COORD_ABS    =64;   /* next variable will be in abs scale */
    mc_mn_DEFS->COORD_SIGNAL =128;  /* next variable will be the signal var */
    mc_mn_DEFS->COORD_AUTO   =256;  /* set auto limits */

    strcpy(mc_mn_DEFS->TOKEN_DEL, " =,;[](){}:");  /* mc_mn_token separators */

    mc_mn_DEFS->SHAPE_SQUARE =0;    /* shape of the monitor */
    mc_mn_DEFS->SHAPE_DISK   =1;
    mc_mn_DEFS->SHAPE_SPHERE =2;
    mc_mn_DEFS->SHAPE_CYLIND =3;
    mc_mn_DEFS->SHAPE_BANANA =4;
    mc_mn_DEFS->SHAPE_BOX    =5;
    mc_mn_DEFS->SHAPE_PREVIOUS=6;

    mc_mn_Vars->Sphere_Radius     = 0;
    mc_mn_Vars->Cylinder_Height   = 0;
    mc_mn_Vars->Flag_With_Borders = 0;   /* 2 means xy borders too */
    mc_mn_Vars->Flag_List         = 0;   /* 1=store 1 buffer, 2=list all, 3=re-use buffer */
    mc_mn_Vars->Flag_Multiple     = 0;   /* 1 when n1D, 0 for 2D */
    mc_mn_Vars->Flag_Verbose      = 0;
    mc_mn_Vars->Flag_Shape        = mc_mn_DEFS->SHAPE_SQUARE;
    mc_mn_Vars->Flag_Auto_Limits  = 0;   /* get limits from first Buffer */
    mc_mn_Vars->Flag_Absorb       = 0;   /* monitor is also a slit */
    mc_mn_Vars->Flag_Exclusive    = 0;   /* absorb neutrons out of monitor limits */
    mc_mn_Vars->Flag_per_cm2      = 0;   /* flux is per cm2 */
    mc_mn_Vars->Flag_per_st       = 0;   /* flux is per steradian (in Auto mode only) */
    mc_mn_Vars->Flag_log          = 0;   /* log10 of the flux */
    mc_mn_Vars->Flag_parallel     = 0;   /* set neutron state back after detection (parallel components) */
    mc_mn_Vars->Flag_Binary_List  = 0;   /* save list as a binary file (smaller) */
    mc_mn_Vars->Coord_Number      = 0;   /* total number of variables to monitor, plus intensity (0) */
    mc_mn_Vars->Buffer_Block      = 10000;     /* Buffer size for list or auto limits */
    mc_mn_Vars->Neutron_Counter   = 0;   /* event counter, simulation total counts is mcget_ncount() */
    mc_mn_Vars->Buffer_Counter    = 0;   /* mc_mn_index in Buffer size (for realloc) */
    mc_mn_Vars->Buffer_Size       = 0;
    mc_mn_Vars->UserVariable1     = 0;
    mc_mn_Vars->UserVariable2     = 0;
    mc_mn_Vars->He3_pressure      = 0;
    mc_mn_Vars->IntermediateCnts  = 0;
    mc_mn_Vars->Flag_capture      = 0;
    mc_mn_Vars->Flag_signal       = mc_mn_DEFS->COORD_P;
    mc_mn_Vars->mean_dx=mc_mn_Vars->mean_dy=0;
    mc_mn_Vars->min_x = mc_mn_Vars->max_x  =0;
    mc_mn_Vars->min_y = mc_mn_Vars->max_y  =0;
    mc_mn_Vars->steradian=0;

    mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_NONE;
    mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR;

    /* handle size parameters */
    /* normal use is with xwidth, yheight, zdepth */
    /* if xmin,xmax,ymin,ymax,zmin,zmax are non 0, use them */
    if (fabs(mc_mn_xmin-mc_mn_xmax) == 0)
      { mc_mn_Vars->mxmin = -fabs(mc_mn_xwidth)/2; mc_mn_Vars->mxmax = fabs(mc_mn_xwidth)/2; }
    else
      { if (mc_mn_xmin < mc_mn_xmax) {mc_mn_Vars->mxmin = mc_mn_xmin; mc_mn_Vars->mxmax = mc_mn_xmax;}
        else {mc_mn_Vars->mxmin = mc_mn_xmax; mc_mn_Vars->mxmax = mc_mn_xmin;}
      }
    if (fabs(mc_mn_ymin-mc_mn_ymax) == 0)
      { mc_mn_Vars->mymin = -fabs(mc_mn_yheight)/2; mc_mn_Vars->mymax = fabs(mc_mn_yheight)/2; }
    else
      { if (mc_mn_ymin < mc_mn_ymax) {mc_mn_Vars->mymin = mc_mn_ymin; mc_mn_Vars->mymax = mc_mn_ymax;}
        else {mc_mn_Vars->mymin = mc_mn_ymax; mc_mn_Vars->mymax = mc_mn_ymin;}
      }
    if (fabs(mc_mn_zmin-mc_mn_zmax) == 0)
      { mc_mn_Vars->mzmin = -fabs(mc_mn_zdepth)/2; mc_mn_Vars->mzmax = fabs(mc_mn_zdepth)/2; }
    else
      { if (mc_mn_zmin < mc_mn_zmax) {mc_mn_Vars->mzmin = mc_mn_zmin; mc_mn_Vars->mzmax = mc_mn_zmax; }
        else {mc_mn_Vars->mzmin = mc_mn_zmax; mc_mn_Vars->mzmax = mc_mn_zmin; }
      }

    if (fabs(mc_mn_Vars->mzmax-mc_mn_Vars->mzmin) == 0)
      mc_mn_Vars->Flag_Shape        = mc_mn_DEFS->SHAPE_SQUARE;
    else
      mc_mn_Vars->Flag_Shape        = mc_mn_DEFS->SHAPE_BOX;

    /* parse option string */

    mc_mn_option_copy = (char*)malloc(strlen(mc_mn_Vars->option)+1);
    if (mc_mn_option_copy == NULL)
    {
      fprintf(stderr,"Monitor_nD: %s cannot allocate mc_mn_option_copy (%li). Fatal.\n", mc_mn_Vars->compcurname, strlen(mc_mn_Vars->option));
      exit(-1);
    }

    if (strlen(mc_mn_Vars->option))
    {
      mc_mn_Flag_End = 0;
      strcpy(mc_mn_option_copy, mc_mn_Vars->option);
    }

    if (strstr(mc_mn_Vars->option, "cm2") || strstr(mc_mn_Vars->option, "cm^2")) mc_mn_Vars->Flag_per_cm2 = 1;
    if (strstr(mc_mn_Vars->option, "steradian")) mc_mn_Vars->Flag_per_st = 1;

    if (strstr(mc_mn_Vars->option, "binary") || strstr(mc_mn_Vars->option, "float"))
      mc_mn_Vars->Flag_Binary_List  = 1;
    if (strstr(mc_mn_Vars->option, "double"))
      mc_mn_Vars->Flag_Binary_List  = 2;

    strcpy(mc_mn_Vars->Coord_Label[0],"Intensity");
    strncpy(mc_mn_Vars->Coord_Var[0],"p",30);
    mc_mn_Vars->Coord_Type[0] = mc_mn_DEFS->COORD_P;
    mc_mn_Vars->Coord_Bin[0] = 1;
    mc_mn_Vars->Coord_Min[0] = 0;
    mc_mn_Vars->Coord_Max[0] = FLT_MAX;

    /* default file name is comp name+dateID */
    sprintf(mc_mn_Vars->Mon_File, "%s_%li", mc_mn_Vars->compcurname, mc_mn_t);

    mc_mn_carg = 1;
    while((mc_mn_Flag_End == 0) && (mc_mn_carg < 128))
    {

      if (mc_mn_Flag_New_token) /* to get the previous mc_mn_token sometimes */
      {
        if (mc_mn_carg == 1) mc_mn_token=(char *)strtok(mc_mn_option_copy,mc_mn_DEFS->TOKEN_DEL);
        else mc_mn_token=(char *)strtok(NULL,mc_mn_DEFS->TOKEN_DEL);
        if (mc_mn_token == NULL) mc_mn_Flag_End=1;
      }
      mc_mn_Flag_New_token = 1;
      if ((mc_mn_token != NULL) && (strlen(mc_mn_token) != 0))
      {
        char mc_mn_iskeyword=0;
        int  mc_mn_old_Mode;
        /* first handle option values from preceeding keyword mc_mn_token detected */
        mc_mn_old_Mode = mc_mn_Set_Coord_Mode;
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_MAX)
        {
          if (!mc_mn_Flag_All)
            mc_mn_Vars->Coord_Max[mc_mn_Vars->Coord_Number] = atof(mc_mn_token);
          else
            for (mc_mn_i = 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_Vars->Coord_Max[mc_mn_i++] = atof(mc_mn_token));
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR; mc_mn_Flag_All = 0;
        }
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_MIN)
        {
          if (!mc_mn_Flag_All)
            mc_mn_Vars->Coord_Min[mc_mn_Vars->Coord_Number] = atof(mc_mn_token);
          else
            for (mc_mn_i = 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_Vars->Coord_Min[mc_mn_i++] = atof(mc_mn_token));
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_MAX;
        }
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_DIM)
        {
          if (!mc_mn_Flag_All)
            mc_mn_Vars->Coord_Bin[mc_mn_Vars->Coord_Number] = atoi(mc_mn_token);
          else
            for (mc_mn_i = 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_Vars->Coord_Bin[mc_mn_i++] = atoi(mc_mn_token));
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR; mc_mn_Flag_All = 0;
        }
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_FIL)
        {
          if (!mc_mn_Flag_No) strncpy(mc_mn_Vars->Mon_File,mc_mn_token,128);
          else { strcpy(mc_mn_Vars->Mon_File,""); mc_mn_Vars->Coord_Number = 0; mc_mn_Flag_End = 1;}
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR;
        }
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_EVNT)
        {
          if (!strcmp(mc_mn_token, "all") || mc_mn_Flag_All) mc_mn_Vars->Flag_List = 2;
          else { mc_mn_i = (long)ceil(atof(mc_mn_token)); if (mc_mn_i) mc_mn_Vars->Buffer_Block = mc_mn_i;
            mc_mn_Vars->Flag_List = 1; }
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR; mc_mn_Flag_All = 0;
        }
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_3HE)
        {
            mc_mn_Vars->He3_pressure = atof(mc_mn_token);
            mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR; mc_mn_Flag_All = 0;
        }
        if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_INTERM)
        {
            mc_mn_Vars->Intermediate = atof(mc_mn_token);
            mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR; mc_mn_Flag_All = 0;
        }

        /* now look for general option keywords */
        if (!strcmp(mc_mn_token, "borders"))  {mc_mn_Vars->Flag_With_Borders = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "verbose"))  {mc_mn_Vars->Flag_Verbose      = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "log"))      {mc_mn_Vars->Flag_log          = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "abs"))      {mc_mn_Flag_abs                = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "multiple")) {mc_mn_Vars->Flag_Multiple     = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "exclusive")){mc_mn_Vars->Flag_Exclusive    = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "list")) {
          mc_mn_Vars->Flag_List = 1; mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_EVNT;  }
        if (!strcmp(mc_mn_token, "limits") || !strcmp(mc_mn_token, "min"))
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_MIN;
        if (!strcmp(mc_mn_token, "slit") || !strcmp(mc_mn_token, "absorb")) {
          mc_mn_Vars->Flag_Absorb = 1;  mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "max"))  mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_MAX;
        if (!strcmp(mc_mn_token, "bins")) mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_DIM;
        if (!strcmp(mc_mn_token, "file")) {
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_FIL;
          if (mc_mn_Flag_No) { strcpy(mc_mn_Vars->Mon_File,""); mc_mn_Vars->Coord_Number = 0; mc_mn_Flag_End = 1; }
        }
        if (!strcmp(mc_mn_token, "unactivate")) {
          mc_mn_Flag_End = 1; mc_mn_Vars->Coord_Number = 0; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "all"))    { mc_mn_Flag_All = 1;  mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "sphere")) { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_SPHERE; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "cylinder")) { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_CYLIND; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "banana")) { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_BANANA; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "square")) { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_SQUARE; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "disk"))   { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_DISK; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "box"))     { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_BOX; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "previous")) { mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_PREVIOUS; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "parallel")){ mc_mn_Vars->Flag_parallel = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "capture")) { mc_mn_Vars->Flag_capture = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "auto") && (mc_mn_Flag_auto != -1)) {
          mc_mn_Vars->Flag_Auto_Limits = 1;
          if (mc_mn_Flag_All) mc_mn_Flag_auto = -1;
          else mc_mn_Flag_auto = 1;
          mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "premonitor")) {
          mc_mn_Vars->Flag_UsePreMonitor = 1; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "3He_pressure")) {
          mc_mn_Vars->He3_pressure = 3; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "intermediate")) {
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_INTERM;
          mc_mn_Vars->Intermediate = 5; mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "no") || !strcmp(mc_mn_token, "not")) { mc_mn_Flag_No = 1;  mc_mn_iskeyword=1; }
        if (!strcmp(mc_mn_token, "signal")) mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_SIGNAL;

        /* Mode has changed: this was a keyword or value */
        if (mc_mn_Set_Coord_Mode != mc_mn_old_Mode) mc_mn_iskeyword=1;

        /* now look for variable names to monitor */
        mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_NONE; mc_mn_lmin = 0; mc_mn_lmax = 0;

        if (!strcmp(mc_mn_token, "x"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_X; strcpy(mc_mn_Set_Vars_Coord_Label,"x [m]"); strcpy(mc_mn_Set_Vars_Coord_Var,"x");
          mc_mn_lmin = mc_mn_Vars->mxmin; mc_mn_lmax = mc_mn_Vars->mxmax;
          mc_mn_Vars->Coord_Min[mc_mn_Vars->Coord_Number+1] = mc_mn_Vars->mxmin;
          mc_mn_Vars->Coord_Max[mc_mn_Vars->Coord_Number+1] = mc_mn_Vars->mxmax;}
        if (!strcmp(mc_mn_token, "y"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_Y; strcpy(mc_mn_Set_Vars_Coord_Label,"y [m]"); strcpy(mc_mn_Set_Vars_Coord_Var,"y");
          mc_mn_lmin = mc_mn_Vars->mymin; mc_mn_lmax = mc_mn_Vars->mymax;
          mc_mn_Vars->Coord_Min[mc_mn_Vars->Coord_Number+1] = mc_mn_Vars->mymin;
          mc_mn_Vars->Coord_Max[mc_mn_Vars->Coord_Number+1] = mc_mn_Vars->mymax;}
        if (!strcmp(mc_mn_token, "z"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_Z; strcpy(mc_mn_Set_Vars_Coord_Label,"z [m]"); strcpy(mc_mn_Set_Vars_Coord_Var,"z"); mc_mn_lmin = mc_mn_Vars->mzmin; mc_mn_lmax = mc_mn_Vars->mzmax; }
        if (!strcmp(mc_mn_token, "k") || !strcmp(mc_mn_token, "wavevector"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_K; strcpy(mc_mn_Set_Vars_Coord_Label,"|k| [Angs-1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"k"); mc_mn_lmin = 0; mc_mn_lmax = 10; }
        if (!strcmp(mc_mn_token, "v"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_V; strcpy(mc_mn_Set_Vars_Coord_Label,"Velocity [m/s]"); strcpy(mc_mn_Set_Vars_Coord_Var,"v"); mc_mn_lmin = 0; mc_mn_lmax = 10000; }
        if (!strcmp(mc_mn_token, "t") || !strcmp(mc_mn_token, "time"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_T; strcpy(mc_mn_Set_Vars_Coord_Label,"TOF [s]"); strcpy(mc_mn_Set_Vars_Coord_Var,"t"); mc_mn_lmin = 0; mc_mn_lmax = .1; }
        if ((!strcmp(mc_mn_token, "p") || !strcmp(mc_mn_token, "intensity") || !strcmp(mc_mn_token, "flux")))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_P;
            strcpy(mc_mn_Set_Vars_Coord_Label,"Intensity");
            strncat(mc_mn_Set_Vars_Coord_Label, " [n/s", 30);
            if (mc_mn_Vars->Flag_per_cm2) strncat(mc_mn_Set_Vars_Coord_Label, "/cm2", 30);
            if (mc_mn_Vars->Flag_per_st) {
              if (mc_mn_Vars->Flag_Auto_Limits)
                strncat(mc_mn_Set_Vars_Coord_Label, "/st", 30);
            }
            if (mc_mn_XY > 1 && mc_mn_Vars->Coord_Number)
              strncat(mc_mn_Set_Vars_Coord_Label, "/bin", 30);
            strncat(mc_mn_Set_Vars_Coord_Label, "]", 30);
            strcpy(mc_mn_Set_Vars_Coord_Var,"I");
            mc_mn_lmin = 0; mc_mn_lmax = FLT_MAX;
          }

        if (!strcmp(mc_mn_token, "vx"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_VX; strcpy(mc_mn_Set_Vars_Coord_Label,"vx [m/s]"); strcpy(mc_mn_Set_Vars_Coord_Var,"vx"); mc_mn_lmin = -1000; mc_mn_lmax = 1000; }
        if (!strcmp(mc_mn_token, "vy"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_VY; strcpy(mc_mn_Set_Vars_Coord_Label,"vy [m/s]"); strcpy(mc_mn_Set_Vars_Coord_Var,"vy"); mc_mn_lmin = -1000; mc_mn_lmax = 1000; }
        if (!strcmp(mc_mn_token, "vz"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_VZ; strcpy(mc_mn_Set_Vars_Coord_Label,"vz [m/s]"); strcpy(mc_mn_Set_Vars_Coord_Var,"vz"); mc_mn_lmin = -10000; mc_mn_lmax = 10000; }
        if (!strcmp(mc_mn_token, "kx"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_KX; strcpy(mc_mn_Set_Vars_Coord_Label,"kx [Angs-1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"kx"); mc_mn_lmin = -1; mc_mn_lmax = 1; }
        if (!strcmp(mc_mn_token, "ky"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_KY; strcpy(mc_mn_Set_Vars_Coord_Label,"ky [Angs-1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"ky"); mc_mn_lmin = -1; mc_mn_lmax = 1; }
        if (!strcmp(mc_mn_token, "kz"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_KZ; strcpy(mc_mn_Set_Vars_Coord_Label,"kz [Angs-1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"kz"); mc_mn_lmin = -10; mc_mn_lmax = 10; }
        if (!strcmp(mc_mn_token, "sx"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_SX; strcpy(mc_mn_Set_Vars_Coord_Label,"sx [1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"sx"); mc_mn_lmin = -1; mc_mn_lmax = 1; }
        if (!strcmp(mc_mn_token, "sy"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_SY; strcpy(mc_mn_Set_Vars_Coord_Label,"sy [1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"sy"); mc_mn_lmin = -1; mc_mn_lmax = 1; }
        if (!strcmp(mc_mn_token, "sz"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_SZ; strcpy(mc_mn_Set_Vars_Coord_Label,"sz [1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"sz"); mc_mn_lmin = -1; mc_mn_lmax = 1; }

        if (!strcmp(mc_mn_token, "energy") || !strcmp(mc_mn_token, "omega"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_ENERGY; strcpy(mc_mn_Set_Vars_Coord_Label,"Energy [meV]"); strcpy(mc_mn_Set_Vars_Coord_Var,"E"); mc_mn_lmin = 0; mc_mn_lmax = 100; }
        if (!strcmp(mc_mn_token, "lambda") || !strcmp(mc_mn_token, "wavelength"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_LAMBDA; strcpy(mc_mn_Set_Vars_Coord_Label,"Wavelength [Angs]"); strcpy(mc_mn_Set_Vars_Coord_Var,"L"); mc_mn_lmin = 0; mc_mn_lmax = 100; }
        if (!strcmp(mc_mn_token, "radius") || !strcmp(mc_mn_token, "xy"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_RADIUS; strcpy(mc_mn_Set_Vars_Coord_Label,"Radius [m]"); strcpy(mc_mn_Set_Vars_Coord_Var,"R"); mc_mn_lmin = 0; mc_mn_lmax = mc_mn_xmax; }
        if (!strcmp(mc_mn_token, "vxy"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_VXY; strcpy(mc_mn_Set_Vars_Coord_Label,"Radial Velocity [m]"); strcpy(mc_mn_Set_Vars_Coord_Var,"Vxy"); mc_mn_lmin = 0; mc_mn_lmax = 2000; }
        if (!strcmp(mc_mn_token, "kxy"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_KXY; strcpy(mc_mn_Set_Vars_Coord_Label,"Radial Wavevector [Angs-1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"Kxy"); mc_mn_lmin = 0; mc_mn_lmax = 2; }
        if (!strcmp(mc_mn_token, "angle"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_ANGLE; strcpy(mc_mn_Set_Vars_Coord_Label,"Angle [deg]"); strcpy(mc_mn_Set_Vars_Coord_Var,"A"); mc_mn_lmin = -5; mc_mn_lmax = 5; }
        if (!strcmp(mc_mn_token, "hdiv")|| !strcmp(mc_mn_token, "divergence") || !strcmp(mc_mn_token, "xdiv") || !strcmp(mc_mn_token, "dx"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_HDIV; strcpy(mc_mn_Set_Vars_Coord_Label,"Hor. Divergence [deg]"); strcpy(mc_mn_Set_Vars_Coord_Var,"HD"); mc_mn_lmin = -5; mc_mn_lmax = 5; }
        if (!strcmp(mc_mn_token, "vdiv") || !strcmp(mc_mn_token, "ydiv") || !strcmp(mc_mn_token, "dy"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_VDIV; strcpy(mc_mn_Set_Vars_Coord_Label,"Vert. Divergence [deg]"); strcpy(mc_mn_Set_Vars_Coord_Var,"VD"); mc_mn_lmin = -5; mc_mn_lmax = 5; }
        if (!strcmp(mc_mn_token, "theta") || !strcmp(mc_mn_token, "longitude"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_THETA; strcpy(mc_mn_Set_Vars_Coord_Label,"Longitude [deg]"); strcpy(mc_mn_Set_Vars_Coord_Var,"th"); mc_mn_lmin = -180; mc_mn_lmax = 180; }
        if (!strcmp(mc_mn_token, "phi") || !strcmp(mc_mn_token, "lattitude"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_PHI; strcpy(mc_mn_Set_Vars_Coord_Label,"Lattitude [deg]"); strcpy(mc_mn_Set_Vars_Coord_Var,"ph"); mc_mn_lmin = -180; mc_mn_lmax = 180; }
        if (!strcmp(mc_mn_token, "ncounts"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_NCOUNT; strcpy(mc_mn_Set_Vars_Coord_Label,"Neutrons [1]"); strcpy(mc_mn_Set_Vars_Coord_Var,"N"); mc_mn_lmin = 0; mc_mn_lmax = 1e10; }
        if (!strcmp(mc_mn_token, "user") || !strcmp(mc_mn_token, "user1"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_USER1; strncpy(mc_mn_Set_Vars_Coord_Label,mc_mn_Vars->UserName1,30); strcpy(mc_mn_Set_Vars_Coord_Var,"U1"); mc_mn_lmin = -1e10; mc_mn_lmax = 1e10; }
        if (!strcmp(mc_mn_token, "user2"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_USER2; strncpy(mc_mn_Set_Vars_Coord_Label,mc_mn_Vars->UserName2,30); strcpy(mc_mn_Set_Vars_Coord_Var,"U2"); mc_mn_lmin = -1e10; mc_mn_lmax = 1e10; }
        if (!strcmp(mc_mn_token, "user3"))
          { mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_USER3; strncpy(mc_mn_Set_Vars_Coord_Label,mc_mn_Vars->UserName3,30); strcpy(mc_mn_Set_Vars_Coord_Var,"U3"); mc_mn_lmin = -1e10; mc_mn_lmax = 1e10; }

        /* now stores variable keywords detected, if any */
        if (mc_mn_Set_Vars_Coord_Type != mc_mn_DEFS->COORD_NONE)
        {
          int mc_mn_Coord_Number = mc_mn_Vars->Coord_Number;
          if (mc_mn_Vars->Flag_log) { mc_mn_Set_Vars_Coord_Type |= mc_mn_DEFS->COORD_LOG; mc_mn_Vars->Flag_log = 0; }
          if (mc_mn_Flag_abs) { mc_mn_Set_Vars_Coord_Type |= mc_mn_DEFS->COORD_ABS; mc_mn_Flag_abs = 0; }
          if (mc_mn_Flag_auto != 0) { mc_mn_Set_Vars_Coord_Type |= mc_mn_DEFS->COORD_AUTO; mc_mn_Flag_auto = 0; }
          if (mc_mn_Set_Coord_Mode == mc_mn_DEFS->COORD_SIGNAL)
          {
            mc_mn_Coord_Number = 0;
            mc_mn_Vars->Flag_signal = mc_mn_Set_Vars_Coord_Type;
          }
          else
          {
            if (mc_mn_Coord_Number < MONnD_COORD_NMAX)
            { mc_mn_Coord_Number++;
              mc_mn_Vars->Coord_Number = mc_mn_Coord_Number; }
            else if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s reached max number of variables (%i).\n", mc_mn_Vars->compcurname, MONnD_COORD_NMAX);
          }
          mc_mn_Vars->Coord_Type[mc_mn_Coord_Number] = mc_mn_Set_Vars_Coord_Type;
          strncpy(mc_mn_Vars->Coord_Label[mc_mn_Coord_Number], mc_mn_Set_Vars_Coord_Label,30);
          strncpy(mc_mn_Vars->Coord_Var[mc_mn_Coord_Number], mc_mn_Set_Vars_Coord_Var,30);
          if (mc_mn_lmin > mc_mn_lmax) { mc_mn_XY = mc_mn_lmin; mc_mn_lmin=mc_mn_lmax; mc_mn_lmax = mc_mn_XY; }
          mc_mn_Vars->Coord_Min[mc_mn_Coord_Number] = mc_mn_lmin;
          mc_mn_Vars->Coord_Max[mc_mn_Coord_Number] = mc_mn_lmax;
          if (mc_mn_Set_Coord_Mode != mc_mn_DEFS->COORD_SIGNAL) mc_mn_Vars->Coord_Bin[mc_mn_Coord_Number] = 20;
          mc_mn_Set_Coord_Mode = mc_mn_DEFS->COORD_VAR;
          mc_mn_Flag_All = 0;
          mc_mn_Flag_No  = 0;
        } else {
          /* no variable name could be read from options */
          if (!mc_mn_iskeyword) {
            if (strcmp(mc_mn_token, "cm2") && strcmp(mc_mn_token, "incoming")
             && strcmp(mc_mn_token, "outgoing") && strcmp(mc_mn_token, "cm2")
             && strcmp(mc_mn_token, "cm^2") && strcmp(mc_mn_token, "float")
             && strcmp(mc_mn_token, "double") && strcmp(mc_mn_token, "binary")
             && strcmp(mc_mn_token, "steradian") && mc_mn_Vars->Flag_Verbose)
              printf("Monitor_nD: %s: unknown '%s' keyword in 'options'. Ignoring.\n", mc_mn_Vars->compcurname, mc_mn_token);
          }
        }
      mc_mn_carg++;
      } /* end if mc_mn_token */
    } /* end while mc_mn_carg */
    free(mc_mn_option_copy);
    if (mc_mn_carg == 128) printf("Monitor_nD: %s reached max number of mc_mn_tokens (%i). Skipping.\n", mc_mn_Vars->compcurname, 128);

    if ((mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_BOX) && (fabs(mc_mn_Vars->mzmax - mc_mn_Vars->mzmin) == 0)) mc_mn_Vars->Flag_Shape = mc_mn_DEFS->SHAPE_SQUARE;

    if (mc_mn_Vars->Flag_log == 1) mc_mn_Vars->Coord_Type[0] |= mc_mn_DEFS->COORD_LOG;
    if (mc_mn_Vars->Coord_Number == 0)
    { mc_mn_Vars->Flag_Auto_Limits=0; mc_mn_Vars->Flag_Multiple=0; mc_mn_Vars->Flag_List=0; }

    /* now setting Monitor Name from variable mc_mn_labels */
    strcpy(mc_mn_Vars->Monitor_Label,"");
    mc_mn_XY = 1; /* will contain total bin number */
    for (mc_mn_i = 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
    {
      if (mc_mn_Flag_auto != 0) mc_mn_Vars->Coord_Type[mc_mn_i] |= mc_mn_DEFS->COORD_AUTO;
      mc_mn_Set_Vars_Coord_Type = (mc_mn_Vars->Coord_Type[mc_mn_i] & 31);
      if ((mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_THETA)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_PHI)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_X)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_Y)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_Z)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_RADIUS))
       strcpy(mc_mn_Short_Label[mc_mn_i],"Position");
      else
      if ((mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VX)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VY)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VZ)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_V)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VXY))
       strcpy(mc_mn_Short_Label[mc_mn_i],"Velocity");
      else
      if ((mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KX)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KY)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KZ)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KXY)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_K))
       strcpy(mc_mn_Short_Label[mc_mn_i],"Wavevector");
      else
      if ((mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_SX)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_SY)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_SZ))
       strcpy(mc_mn_Short_Label[mc_mn_i],"Spin");
      else
      if ((mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_HDIV)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VDIV)
       || (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_ANGLE))
       strcpy(mc_mn_Short_Label[mc_mn_i],"Divergence");
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_ENERGY)
       strcpy(mc_mn_Short_Label[mc_mn_i],"Energy");
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_LAMBDA)
       strcpy(mc_mn_Short_Label[mc_mn_i],"Wavelength");
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_NCOUNT)
       strcpy(mc_mn_Short_Label[mc_mn_i],"Neutron counts");
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_T)
          strcpy(mc_mn_Short_Label[mc_mn_i],"Time Of Flight");
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_P)
          strcpy(mc_mn_Short_Label[mc_mn_i],"Intensity");
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_USER1)
          strncpy(mc_mn_Short_Label[mc_mn_i],mc_mn_Vars->UserName1,30);
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_USER2)
          strncpy(mc_mn_Short_Label[mc_mn_i],mc_mn_Vars->UserName2,30);
      else
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_USER3)
          strncpy(mc_mn_Short_Label[mc_mn_i],mc_mn_Vars->UserName3,30);
      else
          strcpy(mc_mn_Short_Label[mc_mn_i],"Unknown");

      if (mc_mn_Vars->Coord_Type[mc_mn_i] & mc_mn_DEFS->COORD_ABS)
      { strcat(mc_mn_Vars->Coord_Label[mc_mn_i]," (abs)"); }

      if (mc_mn_Vars->Coord_Type[mc_mn_i] & mc_mn_DEFS->COORD_LOG)
      { strcat(mc_mn_Vars->Coord_Label[mc_mn_i]," (log)"); }

      strcat(mc_mn_Vars->Monitor_Label, " ");
      strcat(mc_mn_Vars->Monitor_Label, mc_mn_Short_Label[mc_mn_i]);
      mc_mn_XY *= mc_mn_Vars->Coord_Bin[mc_mn_i];
    } /* end for mc_mn_Short_Label */

    if ((mc_mn_Vars->Coord_Type[0] & 31) == mc_mn_DEFS->COORD_P) {
      strncat(mc_mn_Vars->Coord_Label[0], " [n/s", 30);
      if (mc_mn_Vars->Flag_per_cm2) strncat(mc_mn_Vars->Coord_Label[0], "/cm2", 30);
      if (mc_mn_Vars->Flag_per_st) {
        if (mc_mn_Vars->Flag_Auto_Limits)
          strncat(mc_mn_Vars->Coord_Label[0], "/st", 30);
        else
          printf("Monitor_nD: %s: Flux per steradian requires Auto limits mode\n"
                 "WARNING     use options='.. auto ...'\n", mc_mn_Vars->compcurname);
      }
      if (mc_mn_XY > 1 && mc_mn_Vars->Coord_Number)
        strncat(mc_mn_Vars->Coord_Label[0], "/bin", 30);
      strncat(mc_mn_Vars->Coord_Label[0], "]", 30);
    }

    /* update label 'signal per bin' if more than 1 bin */
    if (mc_mn_XY > 1 && mc_mn_Vars->Coord_Number) {
      if (mc_mn_Vars->Flag_capture)
        printf("Monitor_nD: %s: Using capture flux weightening on %ld bins.\n"
               "            Use binned data with caution, and prefer monitor integral value (I,Ierr).\n", mc_mn_Vars->compcurname, (long)mc_mn_XY);
    }

    strcat(mc_mn_Vars->Monitor_Label, " Monitor");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_SQUARE) strcat(mc_mn_Vars->Monitor_Label, " (Square)");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_DISK)   strcat(mc_mn_Vars->Monitor_Label, " (Disk)");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_SPHERE) strcat(mc_mn_Vars->Monitor_Label, " (Sphere)");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_CYLIND) strcat(mc_mn_Vars->Monitor_Label, " (Cylinder)");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_BANANA) strcat(mc_mn_Vars->Monitor_Label, " (Banana)");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_BOX)    strcat(mc_mn_Vars->Monitor_Label, " (Box)");
    if (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_PREVIOUS) strcat(mc_mn_Vars->Monitor_Label, " (on PREVIOUS)");
    if ((mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_CYLIND) || (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_BANANA) || (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_SPHERE) || (mc_mn_Vars->Flag_Shape == mc_mn_DEFS->SHAPE_BOX))
    {
      if (strstr(mc_mn_Vars->option, "incoming"))
      {
        mc_mn_Vars->Flag_Shape = abs(mc_mn_Vars->Flag_Shape);
        strcat(mc_mn_Vars->Monitor_Label, " [in]");
      }
      else /* if strstr(mc_mn_Vars->option, "outgoing")) */
      {
        mc_mn_Vars->Flag_Shape = -abs(mc_mn_Vars->Flag_Shape);
        strcat(mc_mn_Vars->Monitor_Label, " [out]");
      }
    }
    if (mc_mn_Vars->Flag_UsePreMonitor == 1)
    {
        strcat(mc_mn_Vars->Monitor_Label, " at ");
        strncat(mc_mn_Vars->Monitor_Label, mc_mn_Vars->UserName1,30);
    }
    if (mc_mn_Vars->Flag_log == 1) strcat(mc_mn_Vars->Monitor_Label, " [log] ");

    /* mc_mn_Vars->Coord_Number  0   : intensity or signal
     * mc_mn_Vars->Coord_Number  1:n : detector variables */

    /* now allocate memory to store variables in TRACE */
    if ((mc_mn_Vars->Coord_Number != 2) && !mc_mn_Vars->Flag_Multiple && !mc_mn_Vars->Flag_List)
    { mc_mn_Vars->Flag_Multiple = 1; mc_mn_Vars->Flag_List = 0; } /* default is n1D */

   /* list and auto limits case : mc_mn_Vars->Flag_List or mc_mn_Vars->Flag_Auto_Limits
    * -> Buffer to flush and suppress after mc_mn_Vars->Flag_Auto_Limits
    */
    if ((mc_mn_Vars->Flag_Auto_Limits || mc_mn_Vars->Flag_List) && mc_mn_Vars->Coord_Number)
    { /* Dim : (mc_mn_Vars->Coord_Number+1)*mc_mn_Vars->Buffer_Block matrix (for p, dp) */
      mc_mn_Vars->Mon2D_Buffer = (double *)malloc((mc_mn_Vars->Coord_Number+1)*mc_mn_Vars->Buffer_Block*sizeof(double));
      if (mc_mn_Vars->Mon2D_Buffer == NULL)
      { printf("Monitor_nD: %s cannot allocate mc_mn_Vars->Mon2D_Buffer (%li). No list and auto limits.\n", mc_mn_Vars->compcurname, mc_mn_Vars->Buffer_Block*(mc_mn_Vars->Coord_Number+1)*sizeof(double)); mc_mn_Vars->Flag_List = 0; mc_mn_Vars->Flag_Auto_Limits = 0; }
      else
      {
        for (mc_mn_i=0; mc_mn_i < (mc_mn_Vars->Coord_Number+1)*mc_mn_Vars->Buffer_Block; mc_mn_Vars->Mon2D_Buffer[mc_mn_i++] = (double)0);
      }
      mc_mn_Vars->Buffer_Size = mc_mn_Vars->Buffer_Block;
    }

    /* 1D and n1D case : mc_mn_Vars->Flag_Multiple */
    if (mc_mn_Vars->Flag_Multiple && mc_mn_Vars->Coord_Number)
    { /* Dim : mc_mn_Vars->Coord_Number*mc_mn_Vars->Coord_Bin[mc_mn_i] vectors */
      mc_mn_Vars->Mon2D_N  = (double **)malloc((mc_mn_Vars->Coord_Number)*sizeof(double *));
      mc_mn_Vars->Mon2D_p  = (double **)malloc((mc_mn_Vars->Coord_Number)*sizeof(double *));
      mc_mn_Vars->Mon2D_p2 = (double **)malloc((mc_mn_Vars->Coord_Number)*sizeof(double *));
      if ((mc_mn_Vars->Mon2D_N == NULL) || (mc_mn_Vars->Mon2D_p == NULL) || (mc_mn_Vars->Mon2D_p2 == NULL))
      { fprintf(stderr,"Monitor_nD: %s n1D cannot allocate mc_mn_Vars->Mon2D_N/p/2p (%li). Fatal.\n", mc_mn_Vars->compcurname, (mc_mn_Vars->Coord_Number)*sizeof(double *)); exit(-1); }
      for (mc_mn_i= 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
      {
        mc_mn_Vars->Mon2D_N[mc_mn_i-1]  = (double *)malloc(mc_mn_Vars->Coord_Bin[mc_mn_i]*sizeof(double));
        mc_mn_Vars->Mon2D_p[mc_mn_i-1]  = (double *)malloc(mc_mn_Vars->Coord_Bin[mc_mn_i]*sizeof(double));
        mc_mn_Vars->Mon2D_p2[mc_mn_i-1] = (double *)malloc(mc_mn_Vars->Coord_Bin[mc_mn_i]*sizeof(double));
        if ((mc_mn_Vars->Mon2D_N == NULL) || (mc_mn_Vars->Mon2D_p == NULL) || (mc_mn_Vars->Mon2D_p2 == NULL))
        { fprintf(stderr,"Monitor_nD: %s n1D cannot allocate %s mc_mn_Vars->Mon2D_N/p/2p[%li] (%li). Fatal.\n", mc_mn_Vars->compcurname, mc_mn_Vars->Coord_Var[mc_mn_i], mc_mn_i, (mc_mn_Vars->Coord_Bin[mc_mn_i])*sizeof(double *)); exit(-1); }
        else
        {
          for (mc_mn_j=0; mc_mn_j < mc_mn_Vars->Coord_Bin[mc_mn_i]; mc_mn_j++ )
          { mc_mn_Vars->Mon2D_N[mc_mn_i-1][mc_mn_j] = (double)0; mc_mn_Vars->Mon2D_p[mc_mn_i-1][mc_mn_j] = (double)0; mc_mn_Vars->Mon2D_p2[mc_mn_i-1][mc_mn_j] = (double)0; }
        }
      }
    }
    else /* 2D case : mc_mn_Vars->Coord_Number==2 and !mc_mn_Vars->Flag_Multiple and !mc_mn_Vars->Flag_List */
    if ((mc_mn_Vars->Coord_Number == 2) && !mc_mn_Vars->Flag_Multiple)
    { /* Dim : mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2] matrix */
      mc_mn_Vars->Mon2D_N  = (double **)malloc((mc_mn_Vars->Coord_Bin[1])*sizeof(double *));
      mc_mn_Vars->Mon2D_p  = (double **)malloc((mc_mn_Vars->Coord_Bin[1])*sizeof(double *));
      mc_mn_Vars->Mon2D_p2 = (double **)malloc((mc_mn_Vars->Coord_Bin[1])*sizeof(double *));
      if ((mc_mn_Vars->Mon2D_N == NULL) || (mc_mn_Vars->Mon2D_p == NULL) || (mc_mn_Vars->Mon2D_p2 == NULL))
      { fprintf(stderr,"Monitor_nD: %s 2D cannot allocate %s mc_mn_Vars->Mon2D_N/p/2p (%li). Fatal.\n", mc_mn_Vars->compcurname, mc_mn_Vars->Coord_Var[1], (mc_mn_Vars->Coord_Bin[1])*sizeof(double *)); exit(-1); }
      for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Bin[1]; mc_mn_i++)
      {
        mc_mn_Vars->Mon2D_N[mc_mn_i]  = (double *)malloc(mc_mn_Vars->Coord_Bin[2]*sizeof(double));
        mc_mn_Vars->Mon2D_p[mc_mn_i]  = (double *)malloc(mc_mn_Vars->Coord_Bin[2]*sizeof(double));
        mc_mn_Vars->Mon2D_p2[mc_mn_i] = (double *)malloc(mc_mn_Vars->Coord_Bin[2]*sizeof(double));
        if ((mc_mn_Vars->Mon2D_N == NULL) || (mc_mn_Vars->Mon2D_p == NULL) || (mc_mn_Vars->Mon2D_p2 == NULL))
        { fprintf(stderr,"Monitor_nD: %s 2D cannot allocate %s mc_mn_Vars->Mon2D_N/p/2p[%li] (%li). Fatal.\n", mc_mn_Vars->compcurname, mc_mn_Vars->Coord_Var[1], mc_mn_i, (mc_mn_Vars->Coord_Bin[2])*sizeof(double *)); exit(-1); }
        else
        {
          for (mc_mn_j=0; mc_mn_j < mc_mn_Vars->Coord_Bin[2]; mc_mn_j++ )
          { mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j] = (double)0; mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j] = (double)0; mc_mn_Vars->Mon2D_p2[mc_mn_i][mc_mn_j] = (double)0; }
        }
      }
    }
      /* no Mon2D allocated for
       * (mc_mn_Vars->Coord_Number != 2) && !mc_mn_Vars->Flag_Multiple && mc_mn_Vars->Flag_List */

    mc_mn_Vars->psum  = 0;
    mc_mn_Vars->p2sum = 0;
    mc_mn_Vars->Nsum  = 0;

    mc_mn_Vars->area  = fabs(mc_mn_Vars->mxmax - mc_mn_Vars->mxmin)*fabs(mc_mn_Vars->mymax - mc_mn_Vars->mymin)*1E4; /* in cm**2 for square and box shapes */
    mc_mn_Vars->Sphere_Radius = fabs(mc_mn_Vars->mxmax - mc_mn_Vars->mxmin)/2;
    if ((abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_DISK) || (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_SPHERE))
    {
      mc_mn_Vars->area = PI*mc_mn_Vars->Sphere_Radius*mc_mn_Vars->Sphere_Radius; /* disk shapes */
    }
    if (mc_mn_Vars->area == 0) mc_mn_Vars->Coord_Number = 0;
    if (mc_mn_Vars->Coord_Number == 0 && mc_mn_Vars->Flag_Verbose)
      printf("Monitor_nD: %s is unactivated (0D)\n", mc_mn_Vars->compcurname);
    mc_mn_Vars->Cylinder_Height = fabs(mc_mn_Vars->mymax - mc_mn_Vars->mymin);

    if (mc_mn_Vars->Intermediate < 0) mc_mn_Vars->Intermediate = 0;
    if (mc_mn_Vars->Intermediate > 1) mc_mn_Vars->Intermediate /= 100;
    mc_mn_Vars->IntermediateCnts = mc_mn_Vars->Intermediate*mcget_ncount();

    if (mc_mn_Vars->Flag_Verbose)
    {
      printf("Monitor_nD: %s is a %s.\n", mc_mn_Vars->compcurname, mc_mn_Vars->Monitor_Label);
      printf("Monitor_nD: version %s with options=%s\n", MONITOR_ND_LIB_H, mc_mn_Vars->option);
    }
  } /* end Monitor_nD_Init */

/* ========================================================================= */
/* ADD: E.Farhi, Aug 6th, 2001: Monitor_nD section */
/* this routine is used to monitor one propagating neutron */
/* ========================================================================= */

double Monitor_nD_Trace(MonitornD_Defines_type *mc_mn_DEFS, MonitornD_Variables_type *mc_mn_Vars)
{

  double  mc_mn_XY=0;
  long    mc_mn_i,mc_mn_j;
  double  mc_mn_pp;
  double  mc_mn_Coord[MONnD_COORD_NMAX];
  long    mc_mn_Coord_Index[MONnD_COORD_NMAX];
  char    mc_mn_While_End   =0;
  long    mc_mn_While_Buffer=0;
  char    mc_mn_Set_Vars_Coord_Type = mc_mn_DEFS->COORD_NONE;

  /* mc_mn_Vars->Flag_Auto_Limits */
  if ((mc_mn_Vars->Buffer_Counter >= mc_mn_Vars->Buffer_Block) && (mc_mn_Vars->Flag_Auto_Limits == 1) && (mc_mn_Vars->Coord_Number > 0))
  {
    /* auto limits case : get limits in Buffer for each variable */
          /* Dim : (mc_mn_Vars->Coord_Number+1)*mc_mn_Vars->Buffer_Block matrix (for p, dp) */
    if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s getting %li Auto Limits from List (%li).\n", mc_mn_Vars->compcurname, mc_mn_Vars->Coord_Number, mc_mn_Vars->Buffer_Counter);
    for (mc_mn_i = 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
    {
      if (mc_mn_Vars->Coord_Type[mc_mn_i] & mc_mn_DEFS->COORD_AUTO)
      {
        mc_mn_Vars->Coord_Min[mc_mn_i] = FLT_MAX;
        mc_mn_Vars->Coord_Max[mc_mn_i] = -FLT_MAX;
        for (mc_mn_j = 0; mc_mn_j < mc_mn_Vars->Buffer_Block; mc_mn_j++)
        {
          mc_mn_XY = mc_mn_Vars->Mon2D_Buffer[mc_mn_i+mc_mn_j*(mc_mn_Vars->Coord_Number+1)];  /* scanning variables in Buffer */
          if (mc_mn_XY < mc_mn_Vars->Coord_Min[mc_mn_i]) mc_mn_Vars->Coord_Min[mc_mn_i] = mc_mn_XY;
          if (mc_mn_XY > mc_mn_Vars->Coord_Max[mc_mn_i]) mc_mn_Vars->Coord_Max[mc_mn_i] = mc_mn_XY;
        }
      }
    }
    mc_mn_Vars->Flag_Auto_Limits = 2;  /* pass to 2nd auto limits step */
  }

  /* manage realloc for list all if Buffer size exceeded */
  if ((mc_mn_Vars->Buffer_Counter >= mc_mn_Vars->Buffer_Block) && (mc_mn_Vars->Flag_List >= 2))
  {
    if (mc_mn_Vars->Buffer_Size >= 20000 || mc_mn_Vars->Flag_List == 3)
    { /* save current (possibly append) and re-use Buffer */
      Monitor_nD_Save(mc_mn_DEFS, mc_mn_Vars);
      mc_mn_Vars->Flag_List = 3;
      mc_mn_Vars->Buffer_Block = mc_mn_Vars->Buffer_Size;
      mc_mn_Vars->Buffer_Counter  = 0;
      mc_mn_Vars->Neutron_Counter = 0;
    }
    else
    {
      mc_mn_Vars->Mon2D_Buffer  = (double *)realloc(mc_mn_Vars->Mon2D_Buffer, (mc_mn_Vars->Coord_Number+1)*(mc_mn_Vars->Neutron_Counter+mc_mn_Vars->Buffer_Block)*sizeof(double));
      if (mc_mn_Vars->Mon2D_Buffer == NULL)
            { printf("Monitor_nD: %s cannot reallocate mc_mn_Vars->Mon2D_Buffer[%li] (%li). Skipping.\n", mc_mn_Vars->compcurname, mc_mn_i, (mc_mn_Vars->Neutron_Counter+mc_mn_Vars->Buffer_Block)*sizeof(double)); mc_mn_Vars->Flag_List = 1; }
      else { mc_mn_Vars->Buffer_Counter = 0; mc_mn_Vars->Buffer_Size = mc_mn_Vars->Neutron_Counter+mc_mn_Vars->Buffer_Block; }
    }
  }

  while (!mc_mn_While_End)
  { /* we generate mc_mn_Coord[] and Coord_mc_mn_index[] from Buffer (auto limits) or passing neutron */
    if ((mc_mn_Vars->Flag_Auto_Limits == 2) && (mc_mn_Vars->Coord_Number > 0))
    {
      if (mc_mn_While_Buffer < mc_mn_Vars->Buffer_Block)
      {
        /* first while loops (mc_mn_While_Buffer) */
        /* auto limits case : scan Buffer within limits and store in Mon2D */
        mc_mn_pp = mc_mn_Vars->Mon2D_Buffer[mc_mn_While_Buffer*(mc_mn_Vars->Coord_Number+1)];
	/* For some reason the Intel c compiler version 10.1 gives 0 counts with Monitor_nD!
	   An ugly patch seems to be the following printf */
	printf("");
        mc_mn_Coord[0] = mc_mn_pp;

        for (mc_mn_i = 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
        {
          /* scanning variables in Buffer */
          mc_mn_XY = (mc_mn_Vars->Coord_Max[mc_mn_i]-mc_mn_Vars->Coord_Min[mc_mn_i]);

          mc_mn_Coord[mc_mn_i] = mc_mn_Vars->Mon2D_Buffer[mc_mn_i+mc_mn_While_Buffer*(mc_mn_Vars->Coord_Number+1)];
          if (mc_mn_XY > 0) mc_mn_Coord_Index[mc_mn_i] = floor((mc_mn_Coord[mc_mn_i]-mc_mn_Vars->Coord_Min[mc_mn_i])*mc_mn_Vars->Coord_Bin[mc_mn_i]/mc_mn_XY);
          else mc_mn_Coord_Index[mc_mn_i] = 0;
          if (mc_mn_Vars->Flag_With_Borders)
          {
            if (mc_mn_Coord_Index[mc_mn_i] < 0) mc_mn_Coord_Index[mc_mn_i] = 0;
            if (mc_mn_Coord_Index[mc_mn_i] >= mc_mn_Vars->Coord_Bin[mc_mn_i]) mc_mn_Coord_Index[mc_mn_i] = mc_mn_Vars->Coord_Bin[mc_mn_i] - 1;
          }
        } /* end for */
        mc_mn_While_Buffer++;
      } /* end if in Buffer */
      else /* (mc_mn_While_Buffer >= mc_mn_Vars->Buffer_Block) && (mc_mn_Vars->Flag_Auto_Limits == 2) */
      {
        mc_mn_Vars->Flag_Auto_Limits = 0;
        if (!mc_mn_Vars->Flag_List) /* free Buffer not needed (no list to output) */
        { /* Dim : (mc_mn_Vars->Coord_Number+1)*mc_mn_Vars->Buffer_Block matrix (for p, dp) */
          free(mc_mn_Vars->Mon2D_Buffer); mc_mn_Vars->Mon2D_Buffer = NULL;
        }
      }
    }
    else /* mc_mn_Vars->Flag_Auto_Limits == 0 or 1 */
    {
      for (mc_mn_i = 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
      { /* handle current neutron : last while */
        if (mc_mn_Vars->Flag_Auto_Limits==1) {
          double v;
          v=sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx
                +mc_mn_Vars->cvy*mc_mn_Vars->cvy
                +mc_mn_Vars->cvz*mc_mn_Vars->cvz);
          if (mc_mn_Vars->min_x > mc_mn_Vars->cx) mc_mn_Vars->min_x = mc_mn_Vars->cx;
          if (mc_mn_Vars->max_x < mc_mn_Vars->cx) mc_mn_Vars->max_x = mc_mn_Vars->cx;
          if (mc_mn_Vars->min_y > mc_mn_Vars->cy) mc_mn_Vars->min_y = mc_mn_Vars->cy;
          if (mc_mn_Vars->max_y < mc_mn_Vars->cy) mc_mn_Vars->max_y = mc_mn_Vars->cy;
          mc_mn_Vars->mean_p  += mc_mn_Vars->cp;
          if (v) {
            mc_mn_Vars->mean_dx += mc_mn_Vars->cp*fabs(mc_mn_Vars->cvx/v);
            mc_mn_Vars->mean_dy += mc_mn_Vars->cp*fabs(mc_mn_Vars->cvy/v);
          }
          mc_mn_Vars->area =(mc_mn_Vars->max_x-mc_mn_Vars->min_x)
                           *(mc_mn_Vars->max_y-mc_mn_Vars->min_y)*1E4; /* cm2 */
          if (mc_mn_Vars->Flag_per_st)
          mc_mn_Vars->steradian = 2*fabs(2*atan(mc_mn_Vars->mean_dx/mc_mn_Vars->mean_p)
                                    *sin(2*atan(mc_mn_Vars->mean_dy/mc_mn_Vars->mean_p)/2));
        }

        mc_mn_XY = 0;
        mc_mn_Set_Vars_Coord_Type = (mc_mn_Vars->Coord_Type[mc_mn_i] & 31);
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_X) mc_mn_XY = mc_mn_Vars->cx;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_Y) mc_mn_XY = mc_mn_Vars->cy;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_Z) mc_mn_XY = mc_mn_Vars->cz;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VX) mc_mn_XY = mc_mn_Vars->cvx;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VY) mc_mn_XY = mc_mn_Vars->cvy;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VZ) mc_mn_XY = mc_mn_Vars->cvz;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KX) mc_mn_XY = V2K*mc_mn_Vars->cvx;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KY) mc_mn_XY = V2K*mc_mn_Vars->cvy;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KZ) mc_mn_XY = V2K*mc_mn_Vars->cvz;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_SX) mc_mn_XY = mc_mn_Vars->csx;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_SY) mc_mn_XY = mc_mn_Vars->csy;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_SZ) mc_mn_XY = mc_mn_Vars->csz;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_T) mc_mn_XY = mc_mn_Vars->ct;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_P) mc_mn_XY = mc_mn_Vars->cp;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_HDIV) mc_mn_XY = RAD2DEG*atan2(mc_mn_Vars->cvx,mc_mn_Vars->cvz);
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VDIV) mc_mn_XY = RAD2DEG*atan2(mc_mn_Vars->cvy,mc_mn_Vars->cvz);
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_V) mc_mn_XY = sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy+mc_mn_Vars->cvz*mc_mn_Vars->cvz);
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_RADIUS) mc_mn_XY = sqrt(mc_mn_Vars->cx*mc_mn_Vars->cx+mc_mn_Vars->cy*mc_mn_Vars->cy);
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VXY) mc_mn_XY = sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy);
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_K) { mc_mn_XY = sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy+mc_mn_Vars->cvz*mc_mn_Vars->cvz);  mc_mn_XY *= V2K; }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_KXY) { mc_mn_XY = sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy);  mc_mn_XY *= V2K; }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_ENERGY) { mc_mn_XY = mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy+mc_mn_Vars->cvz*mc_mn_Vars->cvz;  mc_mn_XY *= VS2E; }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_LAMBDA) { mc_mn_XY = sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy+mc_mn_Vars->cvz*mc_mn_Vars->cvz);  mc_mn_XY *= V2K; if (mc_mn_XY != 0) mc_mn_XY = 2*PI/mc_mn_XY; }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_NCOUNT) mc_mn_XY = mc_mn_Coord[mc_mn_i]+1;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_ANGLE)
        {  mc_mn_XY = sqrt(mc_mn_Vars->cvx*mc_mn_Vars->cvx+mc_mn_Vars->cvy*mc_mn_Vars->cvy);
           if (mc_mn_Vars->cvz != 0)
           {
             mc_mn_XY= RAD2DEG*atan2(mc_mn_XY,mc_mn_Vars->cvz);
           } else mc_mn_XY = 0;
        }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_THETA)  { if (mc_mn_Vars->cz != 0) mc_mn_XY = RAD2DEG*atan2(mc_mn_Vars->cx,mc_mn_Vars->cz); }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_PHI) { if (mc_mn_Vars->cz != 0) mc_mn_XY = RAD2DEG*asin(mc_mn_Vars->cy/mc_mn_Vars->cz); }
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_USER1) mc_mn_XY = mc_mn_Vars->UserVariable1;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_USER2) mc_mn_XY = mc_mn_Vars->UserVariable2;
        else
        if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_USER3) mc_mn_XY = mc_mn_Vars->UserVariable3;
        else
        mc_mn_XY = 0;

        if (mc_mn_Vars->Coord_Type[mc_mn_i] & mc_mn_DEFS->COORD_ABS) mc_mn_XY=fabs(mc_mn_XY);

        if (mc_mn_i && (mc_mn_Vars->Coord_Type[mc_mn_i] & mc_mn_DEFS->COORD_LOG)) /* not for the flux */
        {  if (mc_mn_XY > 0) mc_mn_XY = log(mc_mn_XY)/log(10);
           else mc_mn_XY = -100; }

        mc_mn_Coord[mc_mn_i] = mc_mn_XY;
        if (mc_mn_i == 0) { mc_mn_pp = mc_mn_XY; mc_mn_Coord_Index[mc_mn_i] = 0; }
        else if (!mc_mn_Vars->Flag_Auto_Limits)
        {
          mc_mn_XY = (mc_mn_Vars->Coord_Max[mc_mn_i]-mc_mn_Vars->Coord_Min[mc_mn_i]);
          if (mc_mn_XY > 0) mc_mn_Coord_Index[mc_mn_i] = floor((mc_mn_Coord[mc_mn_i]-mc_mn_Vars->Coord_Min[mc_mn_i])*mc_mn_Vars->Coord_Bin[mc_mn_i]/mc_mn_XY);
          else mc_mn_Coord_Index[mc_mn_i] = 0;
          if (mc_mn_Vars->Flag_With_Borders)
          {
            if (mc_mn_Coord_Index[mc_mn_i] < 0) mc_mn_Coord_Index[mc_mn_i] = 0;
            if (mc_mn_Coord_Index[mc_mn_i] >= mc_mn_Vars->Coord_Bin[mc_mn_i]) mc_mn_Coord_Index[mc_mn_i] = mc_mn_Vars->Coord_Bin[mc_mn_i] - 1;
          }
        } /* else Auto_Limits will get Index later from Buffer */
      } /* end for mc_mn_i */
      mc_mn_While_End = 1;
    } /* end else if mc_mn_Vars->Flag_Auto_Limits == 2 */

    if (mc_mn_Vars->Flag_Auto_Limits != 2) /* not when reading auto limits Buffer */
    { /* now store Coord into Buffer (no mc_mn_index needed) if necessary */
      if ((mc_mn_Vars->Buffer_Counter < mc_mn_Vars->Buffer_Block) && ((mc_mn_Vars->Flag_List) || (mc_mn_Vars->Flag_Auto_Limits == 1)))
      {
        for (mc_mn_i = 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
        {
          mc_mn_Vars->Mon2D_Buffer[mc_mn_i + mc_mn_Vars->Neutron_Counter*(mc_mn_Vars->Coord_Number+1)] = mc_mn_Coord[mc_mn_i];
        }
        mc_mn_Vars->Buffer_Counter++;
        if (mc_mn_Vars->Flag_Verbose && (mc_mn_Vars->Buffer_Counter >= mc_mn_Vars->Buffer_Block) && (mc_mn_Vars->Flag_List == 1)) printf("Monitor_nD: %s %li neutrons stored in List.\n", mc_mn_Vars->compcurname, mc_mn_Vars->Buffer_Counter);
      }
      mc_mn_Vars->Neutron_Counter++;
    } /* end (mc_mn_Vars->Flag_Auto_Limits != 2) */

    /* store n1d/2d section for Buffer or current neutron in while */
    if (mc_mn_Vars->Flag_Auto_Limits != 1) /* not when storing auto limits Buffer */
    {

      if (mc_mn_Vars->Flag_per_cm2 && mc_mn_Vars->area      != 0)
        mc_mn_pp /= mc_mn_Vars->area;
      if (mc_mn_Vars->Flag_per_st  && mc_mn_Vars->steradian != 0)
        mc_mn_pp /= mc_mn_Vars->steradian;

    /* 1D and n1D case : mc_mn_Vars->Flag_Multiple */
      if (mc_mn_Vars->Flag_Multiple)
      { /* Dim : mc_mn_Vars->Coord_Number*mc_mn_Vars->Coord_Bin[mc_mn_i] vectors (intensity is not included) */
        /* check limits: monitors define a phase space to record */
        char within_limits=1;
        for (mc_mn_i= 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
        {
          mc_mn_j = mc_mn_Coord_Index[mc_mn_i];
          if (mc_mn_j < 0 || mc_mn_j >= mc_mn_Vars->Coord_Bin[mc_mn_i])
            within_limits=0;
        }
        if (within_limits)
        { for (mc_mn_i= 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
          {
            mc_mn_j = mc_mn_Coord_Index[mc_mn_i];
            if (mc_mn_j >= 0 && mc_mn_j < mc_mn_Vars->Coord_Bin[mc_mn_i])
            {
              mc_mn_Vars->Mon2D_N[mc_mn_i-1][mc_mn_j]++;
              mc_mn_Vars->Mon2D_p[mc_mn_i-1][mc_mn_j] += mc_mn_pp;
              mc_mn_Vars->Mon2D_p2[mc_mn_i-1][mc_mn_j] += mc_mn_pp*mc_mn_pp;
            }
          }
        }
        else if (mc_mn_Vars->Flag_Exclusive)
        { mc_mn_pp = 0.0;
        }
      }
      else /* 2D case : mc_mn_Vars->Coord_Number==2 and !mc_mn_Vars->Flag_Multiple and !mc_mn_Vars->Flag_List */
      if ((mc_mn_Vars->Coord_Number == 2) && !mc_mn_Vars->Flag_Multiple)
      { /* Dim : mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2] matrix */
        mc_mn_i = mc_mn_Coord_Index[1];
        mc_mn_j = mc_mn_Coord_Index[2];
        if (mc_mn_i >= 0 && mc_mn_i < mc_mn_Vars->Coord_Bin[1] && mc_mn_j >= 0 && mc_mn_j < mc_mn_Vars->Coord_Bin[2])
        {
          mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j]++;
          mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j] += mc_mn_pp;
          mc_mn_Vars->Mon2D_p2[mc_mn_i][mc_mn_j] += mc_mn_pp*mc_mn_pp;
        }
        else if (mc_mn_Vars->Flag_Exclusive)
        { mc_mn_pp = 0.0;
        }
      }
    } /* end (mc_mn_Vars->Flag_Auto_Limits != 1) */
  } /* end while */
  return mc_mn_pp;
} /* end Monitor_nD_Trace */

/* ========================================================================= */
/* ADD: E.Farhi, Aug 6th, 2001: Monitor_nD section */
/* this routine is used to save data files */
/* ========================================================================= */

void Monitor_nD_Save(MonitornD_Defines_type *mc_mn_DEFS, MonitornD_Variables_type *mc_mn_Vars)
  {
    char   *mc_mn_fname;
    long    mc_mn_i,mc_mn_j;
    double *mc_mn_p0m = NULL;
    double *mc_mn_p1m = NULL;
    double *mc_mn_p2m = NULL;
    char    mc_mn_Coord_X_Label[1024];
    double  mc_mn_min1d, mc_mn_max1d;
    double  mc_mn_min2d, mc_mn_max2d;
    long    mc_mn_bin1d, mc_mn_bin2d;
    char    mc_mn_While_End = 0;
    long    mc_mn_While_Buffer = 0;
    double  mc_mn_XY, mc_mn_pp;
    double  mc_mn_Coord[MONnD_COORD_NMAX];
    long    mc_mn_Coord_Index[MONnD_COORD_NMAX];
    char    mc_mn_label[1024];
    double  mc_mn_ratio;

    mc_mn_ratio = 100*mcget_run_num()/mcget_ncount();
    if (mc_mn_Vars->Flag_per_cm2 && mc_mn_Vars->area && mc_mn_Vars->Flag_Verbose)
      printf("Monitor_nD: %s: detector area is %g [cm2]\n",
        mc_mn_Vars->compcurname, mc_mn_Vars->area);
    if (mc_mn_Vars->Flag_per_st && mc_mn_Vars->steradian && mc_mn_Vars->Flag_Verbose)
      printf("Monitor_nD: %s: beam solid angle is %g [st] (%g x %g [deg2])\n",
        mc_mn_Vars->compcurname, mc_mn_Vars->steradian,
        atan(mc_mn_Vars->mean_dx/mc_mn_Vars->mean_p)*RAD2DEG,
        atan(mc_mn_Vars->mean_dy/mc_mn_Vars->mean_p)*RAD2DEG);

    if (mc_mn_ratio < 99)
    {
      if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s save intermediate results (%.2f %%).\n", mc_mn_Vars->compcurname, mc_mn_ratio);
    }
    /* check Buffer flush when end of simulation reached */
    if ((mc_mn_Vars->Buffer_Counter <= mc_mn_Vars->Buffer_Block) && mc_mn_Vars->Flag_Auto_Limits && mc_mn_Vars->Mon2D_Buffer && mc_mn_Vars->Buffer_Counter)
    {
      /* Get Auto Limits */
      if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s getting %li Auto Limits from List (%li).\n", mc_mn_Vars->compcurname, mc_mn_Vars->Coord_Number, mc_mn_Vars->Buffer_Counter);
      for (mc_mn_i = 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
      {
        if (mc_mn_Vars->Coord_Type[mc_mn_i] & mc_mn_DEFS->COORD_AUTO)
        {
          mc_mn_Vars->Coord_Min[mc_mn_i] = FLT_MAX;
          mc_mn_Vars->Coord_Max[mc_mn_i] = -FLT_MAX;

          for (mc_mn_j = 0; mc_mn_j < mc_mn_Vars->Buffer_Counter; mc_mn_j++)
          {
            mc_mn_XY = mc_mn_Vars->Mon2D_Buffer[mc_mn_i+mc_mn_j*(mc_mn_Vars->Coord_Number+1)];  /* scanning variables in Buffer */
            if (mc_mn_XY < mc_mn_Vars->Coord_Min[mc_mn_i]) mc_mn_Vars->Coord_Min[mc_mn_i] = mc_mn_XY;
            if (mc_mn_XY > mc_mn_Vars->Coord_Max[mc_mn_i]) mc_mn_Vars->Coord_Max[mc_mn_i] = mc_mn_XY;

          }
        }
      }
      mc_mn_Vars->Flag_Auto_Limits = 2;  /* pass to 2nd auto limits step */
      mc_mn_Vars->Buffer_Block = mc_mn_Vars->Buffer_Counter;

      while (!mc_mn_While_End)
      { /* we generate mc_mn_Coord[] and Coord_mc_mn_index[] from Buffer (auto limits) or passing neutron */
        if (mc_mn_While_Buffer < mc_mn_Vars->Buffer_Block)
        {
          /* first while loops (mc_mn_While_Buffer) */
          mc_mn_Coord[0] = mc_mn_Vars->Mon2D_Buffer[mc_mn_While_Buffer*(mc_mn_Vars->Coord_Number+1)];

          /* auto limits case : scan Buffer within limits and store in Mon2D */
          for (mc_mn_i = 1; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
          {
            /* scanning variables in Buffer */
            mc_mn_XY = (mc_mn_Vars->Coord_Max[mc_mn_i]-mc_mn_Vars->Coord_Min[mc_mn_i]);
            mc_mn_Coord[mc_mn_i] = mc_mn_Vars->Mon2D_Buffer[mc_mn_i+mc_mn_While_Buffer*(mc_mn_Vars->Coord_Number+1)];
            if (mc_mn_XY > 0) mc_mn_Coord_Index[mc_mn_i] = floor((mc_mn_Coord[mc_mn_i]-mc_mn_Vars->Coord_Min[mc_mn_i])*mc_mn_Vars->Coord_Bin[mc_mn_i]/mc_mn_XY);
            else mc_mn_Coord_Index[mc_mn_i] = 0;
            if (mc_mn_Vars->Flag_With_Borders)
            {
              if (mc_mn_Coord_Index[mc_mn_i] < 0) mc_mn_Coord_Index[mc_mn_i] = 0;
              if (mc_mn_Coord_Index[mc_mn_i] >= mc_mn_Vars->Coord_Bin[mc_mn_i]) mc_mn_Coord_Index[mc_mn_i] = mc_mn_Vars->Coord_Bin[mc_mn_i] - 1;
            }
          } /* end for */
          mc_mn_While_Buffer++;
        } /* end if in Buffer */
        else /* (mc_mn_While_Buffer >= mc_mn_Vars->Buffer_Block) && (mc_mn_Vars->Flag_Auto_Limits == 2) */
        {
          mc_mn_Vars->Flag_Auto_Limits = 0;
          mc_mn_While_End = 1;
        }

        /* store n1d/2d section from Buffer */

        mc_mn_pp = mc_mn_Coord[0];
        /* 1D and n1D case : mc_mn_Vars->Flag_Multiple */
        if (mc_mn_Vars->Flag_Multiple)
        { /* Dim : mc_mn_Vars->Coord_Number*mc_mn_Vars->Coord_Bin[mc_mn_i] vectors (intensity is not included) */
          for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Number; mc_mn_i++)
          {
            mc_mn_j = mc_mn_Coord_Index[mc_mn_i+1];
            if (mc_mn_j >= 0 && mc_mn_j < mc_mn_Vars->Coord_Bin[mc_mn_i+1])
            {
              mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j]++;
              mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j] += mc_mn_pp;
              mc_mn_Vars->Mon2D_p2[mc_mn_i][mc_mn_j] += mc_mn_pp*mc_mn_pp;
            }
          }
        }
        else /* 2D case : mc_mn_Vars->Coord_Number==2 and !mc_mn_Vars->Flag_Multiple and !mc_mn_Vars->Flag_List */
        if ((mc_mn_Vars->Coord_Number == 2) && !mc_mn_Vars->Flag_Multiple)
        { /* Dim : mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2] matrix */
          mc_mn_i = mc_mn_Coord_Index[1];
          mc_mn_j = mc_mn_Coord_Index[2];
          if (mc_mn_i >= 0 && mc_mn_i < mc_mn_Vars->Coord_Bin[1] && mc_mn_j >= 0 && mc_mn_j < mc_mn_Vars->Coord_Bin[2])
          {
            mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j]++;
            mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j] += mc_mn_pp;
            mc_mn_Vars->Mon2D_p2[mc_mn_i][mc_mn_j] += mc_mn_pp*mc_mn_pp;
          }
        } /* end store 2D/1D */
      } /* end while */
    } /* end Force Get Limits */

    /* write output files (sent to file as p[i*n + j] vectors) */
    if (mc_mn_Vars->Coord_Number == 0)
    {
      double mc_mn_Nsum;
      double mc_mn_psum, mc_mn_p2sum;
      mc_mn_Nsum = mc_mn_Vars->Nsum;
      mc_mn_psum = mc_mn_Vars->psum;
      mc_mn_p2sum= mc_mn_Vars->p2sum;
      if (mc_mn_Vars->Flag_signal != mc_mn_DEFS->COORD_P && mc_mn_Nsum > 0)
      { mc_mn_psum /=mc_mn_Nsum; mc_mn_p2sum /= mc_mn_Nsum*mc_mn_Nsum; }
      /* DETECTOR_OUT_0D(mc_mn_Vars->Monitor_Label, mc_mn_Vars->Nsum, mc_mn_Vars->psum, mc_mn_Vars->p2sum); */
      mcdetector_out_0D(mc_mn_Vars->Monitor_Label, mc_mn_Nsum, mc_mn_psum, mc_mn_p2sum, mc_mn_Vars->compcurname, mc_mn_Vars->compcurpos);
    }
    else
    if (strlen(mc_mn_Vars->Mon_File) > 0)
    {
      mc_mn_fname = (char*)malloc(strlen(mc_mn_Vars->Mon_File)+10*mc_mn_Vars->Coord_Number);
      if (mc_mn_Vars->Flag_List && mc_mn_Vars->Mon2D_Buffer) /* List: DETECTOR_OUT_2D */
      {
        int  ascii_only_orig;
        char formatName[64];
        char *formatName_orig;

        if (mc_mn_Vars->Flag_List >= 2) mc_mn_Vars->Buffer_Size = mc_mn_Vars->Neutron_Counter;
        if (mc_mn_Vars->Buffer_Size >= mc_mn_Vars->Neutron_Counter)
          mc_mn_Vars->Buffer_Size = mc_mn_Vars->Neutron_Counter;
        strcpy(mc_mn_fname,mc_mn_Vars->Mon_File);
        if (strchr(mc_mn_Vars->Mon_File,'.') == NULL) strcat(mc_mn_fname, "_list");

        mc_mn_min1d = 1; mc_mn_max1d = mc_mn_Vars->Coord_Number+1;
        mc_mn_min2d = 0; mc_mn_max2d = mc_mn_Vars->Buffer_Size;
        mc_mn_bin1d = mc_mn_Vars->Coord_Number+1; mc_mn_bin2d = mc_mn_Vars->Buffer_Size;
        strcpy(mc_mn_Coord_X_Label,"");
        for (mc_mn_i= 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
        {
          if (mc_mn_min2d < mc_mn_Vars->Coord_Min[mc_mn_i]) mc_mn_min2d = mc_mn_Vars->Coord_Min[mc_mn_i];
          if (mc_mn_max2d < mc_mn_Vars->Coord_Max[mc_mn_i]) mc_mn_max2d = mc_mn_Vars->Coord_Max[mc_mn_i];
          strcat(mc_mn_Coord_X_Label, mc_mn_Vars->Coord_Var[mc_mn_i]);
          strcat(mc_mn_Coord_X_Label, " ");
          if (strchr(mc_mn_Vars->Mon_File,'.') == NULL)
          { strcat(mc_mn_fname, "."); strcat(mc_mn_fname, mc_mn_Vars->Coord_Var[mc_mn_i]); }
        }
        if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s write monitor file %s List (%lix%li).\n", mc_mn_Vars->compcurname, mc_mn_fname,mc_mn_bin2d,mc_mn_bin1d);

        /* handle the type of list output */
        ascii_only_orig = mcascii_only;
        formatName_orig = mcformat.Name;  /* copy the pointer position */
        strcpy(formatName, mcformat.Name);
        if (mc_mn_Vars->Flag_List >= 1)
        { /* Flag_List mode:
               1=store 1 buffer
               2=list all, triggers 3 when 1st buffer reallocated
               3=re-used buffer (file already opened)
             Format modifiers for Flag_List
               1= normal monitor file (no modifier, export in one go)
               2= write data+header, and footer if buffer not full (mc_mn_Vars->Buffer_Counter < mc_mn_Vars->Buffer_Block)
               3= write data, and footer if buffer not full (final)
           */
          strcat(formatName, " list ");
          if (mc_mn_Vars->Flag_List == 3) strcat(formatName, " no header ");
          if (mc_mn_Vars->Flag_List >= 2 && mc_mn_Vars->Buffer_Counter >= mc_mn_Vars->Buffer_Block)
            strcat(formatName, " no footer ");

          if (mc_mn_Vars->Flag_Binary_List) mcascii_only = 1;
          if (mc_mn_Vars->Flag_Binary_List == 1)
            strcat(formatName, " binary float ");
          else if (mc_mn_Vars->Flag_Binary_List == 2)
            strcat(formatName, " binary double ");
        }
        if (mc_mn_min2d == mc_mn_max2d) mc_mn_max2d = mc_mn_min2d+1e-6;
        if (mc_mn_min1d == mc_mn_max1d) mc_mn_max1d = mc_mn_min1d+1e-6;
        strcpy(mc_mn_label, mc_mn_Vars->Monitor_Label);
        if (!mc_mn_Vars->Flag_Binary_List)
        { mc_mn_bin2d=-mc_mn_bin2d; }
        mcformat.Name = formatName;
        mcdetector_out_2D(
              mc_mn_label,
              "List of neutron events",
              mc_mn_Coord_X_Label,
              mc_mn_min2d, mc_mn_max2d,
              mc_mn_min1d, mc_mn_max1d,
              mc_mn_bin2d,
              mc_mn_bin1d,
            NULL,mc_mn_Vars->Mon2D_Buffer,NULL,
            mc_mn_fname, mc_mn_Vars->compcurname, mc_mn_Vars->compcurpos);

        /* reset the original type of output */
        mcascii_only = ascii_only_orig;
        mcformat.Name= formatName_orig;
      }
      if (mc_mn_Vars->Flag_Multiple) /* n1D: DETECTOR_OUT_1D */
      {
        for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Number; mc_mn_i++)
        {

          strcpy(mc_mn_fname,mc_mn_Vars->Mon_File);
          if (strchr(mc_mn_Vars->Mon_File,'.') == NULL)
          { strcat(mc_mn_fname, "."); strcat(mc_mn_fname, mc_mn_Vars->Coord_Var[mc_mn_i+1]); }
          sprintf(mc_mn_Coord_X_Label, "%s monitor", mc_mn_Vars->Coord_Label[mc_mn_i+1]);
          strcpy(mc_mn_label, mc_mn_Coord_X_Label);
          if (mc_mn_Vars->Coord_Bin[mc_mn_i+1] > 0) { /* 1D monitor */
            if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s write monitor file %s 1D (%li).\n", mc_mn_Vars->compcurname, mc_mn_fname, mc_mn_Vars->Coord_Bin[mc_mn_i+1]);
            mc_mn_min1d = mc_mn_Vars->Coord_Min[mc_mn_i+1];
            mc_mn_max1d = mc_mn_Vars->Coord_Max[mc_mn_i+1];
            if (mc_mn_min1d == mc_mn_max1d) mc_mn_max1d = mc_mn_min1d+1e-6;
            mc_mn_p1m = (double *)malloc(mc_mn_Vars->Coord_Bin[mc_mn_i+1]*sizeof(double));
            mc_mn_p2m = (double *)malloc(mc_mn_Vars->Coord_Bin[mc_mn_i+1]*sizeof(double));
            if (mc_mn_p2m == NULL) /* use Raw Buffer line output */
            {
              if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s cannot allocate memory for output. Using raw data.\n", mc_mn_Vars->compcurname);
              if (mc_mn_p1m != NULL) free(mc_mn_p1m);
              mcdetector_out_1D(
              mc_mn_label,
              mc_mn_Vars->Coord_Label[mc_mn_i+1],
              mc_mn_Vars->Coord_Label[0],
              mc_mn_Vars->Coord_Var[mc_mn_i+1],
              mc_mn_min1d, mc_mn_max1d,
              mc_mn_Vars->Coord_Bin[mc_mn_i+1],
              mc_mn_Vars->Mon2D_N[mc_mn_i],mc_mn_Vars->Mon2D_p[mc_mn_i],mc_mn_Vars->Mon2D_p2[mc_mn_i],
              mc_mn_fname, mc_mn_Vars->compcurname, mc_mn_Vars->compcurpos);
            } /* if (mc_mn_p2m == NULL) */
            else
            {
              if (mc_mn_Vars->Flag_log != 0)
              {
                mc_mn_XY = FLT_MAX;
                for (mc_mn_j=0; mc_mn_j < mc_mn_Vars->Coord_Bin[mc_mn_i+1]; mc_mn_j++) /* search min of signal */
                  if ((mc_mn_XY > mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j]) && (mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j] > 0)) mc_mn_XY = mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j];
                if (mc_mn_XY <= 0) mc_mn_XY = -log(FLT_MAX)/log(10); else mc_mn_XY = log(mc_mn_XY)/log(10)-1;
              } /* if */

              for (mc_mn_j=0; mc_mn_j < mc_mn_Vars->Coord_Bin[mc_mn_i+1]; mc_mn_j++)
              {
                mc_mn_p1m[mc_mn_j] = mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j];
                mc_mn_p2m[mc_mn_j] = mc_mn_Vars->Mon2D_p2[mc_mn_i][mc_mn_j];
                if (mc_mn_Vars->Flag_signal != mc_mn_DEFS->COORD_P && mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j] > 0)
                { /* normalize mean signal to the number of events */
                  mc_mn_p1m[mc_mn_j] /= mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j];
                  mc_mn_p2m[mc_mn_j] /= mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j]*mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j];
                }
                if (mc_mn_Vars->Flag_log != 0)
                {
                  if ((mc_mn_p1m[mc_mn_j] > 0) && (mc_mn_p2m[mc_mn_j] > 0))
                  {
                    mc_mn_p2m[mc_mn_j] /= mc_mn_p1m[mc_mn_j]*mc_mn_p1m[mc_mn_j];
                    mc_mn_p1m[mc_mn_j] = log(mc_mn_p1m[mc_mn_j])/log(10);
                  }
                  else
                  {
                    mc_mn_p1m[mc_mn_j] = mc_mn_XY;
                    mc_mn_p2m[mc_mn_j] = 0;
                  }
                }
              } /* for */
              mcdetector_out_1D(
                mc_mn_label,
                mc_mn_Vars->Coord_Label[mc_mn_i+1],
                mc_mn_Vars->Coord_Label[0],
                mc_mn_Vars->Coord_Var[mc_mn_i+1],
                mc_mn_min1d, mc_mn_max1d,
                mc_mn_Vars->Coord_Bin[mc_mn_i+1],
                mc_mn_Vars->Mon2D_N[mc_mn_i],mc_mn_p1m,mc_mn_p2m,
                mc_mn_fname, mc_mn_Vars->compcurname, mc_mn_Vars->compcurpos);

            } /* else */
            if (mc_mn_p1m != NULL) free(mc_mn_p1m); mc_mn_p1m=NULL;
            if (mc_mn_p2m != NULL) free(mc_mn_p2m); mc_mn_p2m=NULL;
          } else { /* 0d monitor */
            mcdetector_out_0D(mc_mn_label, mc_mn_Vars->Mon2D_p[mc_mn_i][0], mc_mn_Vars->Mon2D_p2[mc_mn_i][0], mc_mn_Vars->Mon2D_N[mc_mn_i][0], mc_mn_Vars->compcurname, mc_mn_Vars->compcurpos);
          }


        } /* for */
      } /* if 1D */
      else
      if (mc_mn_Vars->Coord_Number == 2)  /* 2D: DETECTOR_OUT_2D */
      {
        strcpy(mc_mn_fname,mc_mn_Vars->Mon_File);

        mc_mn_p0m = (double *)malloc(mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2]*sizeof(double));
        mc_mn_p1m = (double *)malloc(mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2]*sizeof(double));
        mc_mn_p2m = (double *)malloc(mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2]*sizeof(double));
        if (mc_mn_p2m == NULL)
        {
          if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s cannot allocate memory for 2D array (%li). Skipping.\n", mc_mn_Vars->compcurname, 3*mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2]*sizeof(double));
          if (mc_mn_p0m != NULL) free(mc_mn_p0m);
          if (mc_mn_p1m != NULL) free(mc_mn_p1m);
        }
        else
        {
          if (mc_mn_Vars->Flag_log != 0)
          {
            mc_mn_XY = FLT_MAX;
            for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Bin[1]; mc_mn_i++)
              for (mc_mn_j= 0; mc_mn_j < mc_mn_Vars->Coord_Bin[2]; mc_mn_j++) /* search min of signal */
                if ((mc_mn_XY > mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j]) && (mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j]>0)) mc_mn_XY = mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j];
            if (mc_mn_XY <= 0) mc_mn_XY = -log(FLT_MAX)/log(10); else mc_mn_XY = log(mc_mn_XY)/log(10)-1;
          }
          for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Bin[1]; mc_mn_i++)
          {
            for (mc_mn_j= 0; mc_mn_j < mc_mn_Vars->Coord_Bin[2]; mc_mn_j++)
            {
              long mc_mn_index;
              mc_mn_index = mc_mn_j + mc_mn_i*mc_mn_Vars->Coord_Bin[2];
              mc_mn_p0m[mc_mn_index] = mc_mn_Vars->Mon2D_N[mc_mn_i][mc_mn_j];
              mc_mn_p1m[mc_mn_index] = mc_mn_Vars->Mon2D_p[mc_mn_i][mc_mn_j];
              mc_mn_p2m[mc_mn_index] = mc_mn_Vars->Mon2D_p2[mc_mn_i][mc_mn_j];
              if (mc_mn_Vars->Flag_signal != mc_mn_DEFS->COORD_P && mc_mn_p0m[mc_mn_index] > 0)
              {
                  mc_mn_p1m[mc_mn_index] /= mc_mn_p0m[mc_mn_index];
                  mc_mn_p2m[mc_mn_index] /= mc_mn_p0m[mc_mn_index]*mc_mn_p0m[mc_mn_index];
              }

              if (mc_mn_Vars->Flag_log != 0)
              {
                if ((mc_mn_p1m[mc_mn_index] > 0) && (mc_mn_p2m[mc_mn_index] > 0))
                {
                  mc_mn_p2m[mc_mn_index] /= (mc_mn_p1m[mc_mn_index]*mc_mn_p1m[mc_mn_index]);
                  mc_mn_p1m[mc_mn_index] = log(mc_mn_p1m[mc_mn_index])/log(10);

                }
                else
                {
                  mc_mn_p1m[mc_mn_index] = mc_mn_XY;
                  mc_mn_p2m[mc_mn_index] = 0;
                }
              }
            }
          }
          if (strchr(mc_mn_Vars->Mon_File,'.') == NULL)
          { strcat(mc_mn_fname, "."); strcat(mc_mn_fname, mc_mn_Vars->Coord_Var[1]);
              strcat(mc_mn_fname, "_"); strcat(mc_mn_fname, mc_mn_Vars->Coord_Var[2]); }
          if (mc_mn_Vars->Flag_Verbose) printf("Monitor_nD: %s write monitor file %s 2D (%lix%li).\n", mc_mn_Vars->compcurname, mc_mn_fname, mc_mn_Vars->Coord_Bin[1], mc_mn_Vars->Coord_Bin[2]);

          mc_mn_min1d = mc_mn_Vars->Coord_Min[1];
          mc_mn_max1d = mc_mn_Vars->Coord_Max[1];
          if (mc_mn_min1d == mc_mn_max1d) mc_mn_max1d = mc_mn_min1d+1e-6;
          mc_mn_min2d = mc_mn_Vars->Coord_Min[2];
          mc_mn_max2d = mc_mn_Vars->Coord_Max[2];
          if (mc_mn_min2d == mc_mn_max2d) mc_mn_max2d = mc_mn_min2d+1e-6;
          strcpy(mc_mn_label, mc_mn_Vars->Monitor_Label);
          if (mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2] > 1
           && mc_mn_Vars->Flag_signal == mc_mn_DEFS->COORD_P)
            strcat(mc_mn_label, " per bin");

          mcdetector_out_2D(
            mc_mn_label,
            mc_mn_Vars->Coord_Label[1],
            mc_mn_Vars->Coord_Label[2],
            mc_mn_min1d, mc_mn_max1d,
            mc_mn_min2d, mc_mn_max2d,
            mc_mn_Vars->Coord_Bin[1],
            mc_mn_Vars->Coord_Bin[2],
            mc_mn_p0m,mc_mn_p1m,mc_mn_p2m,
            mc_mn_fname, mc_mn_Vars->compcurname, mc_mn_Vars->compcurpos);

          if (mc_mn_p0m != NULL) free(mc_mn_p0m);
          if (mc_mn_p1m != NULL) free(mc_mn_p1m);
          if (mc_mn_p2m != NULL) free(mc_mn_p2m);
        }
      }
      free(mc_mn_fname);
    }
  } /* end Monitor_nD_Save */

/* ========================================================================= */
/* ADD: E.Farhi, Aug 6th, 2001: Monitor_nD section */
/* this routine is used to free memory */
/* ========================================================================= */

void Monitor_nD_Finally(MonitornD_Defines_type *mc_mn_DEFS,
  MonitornD_Variables_type *mc_mn_Vars)
  {
    int mc_mn_i;

    /* Now Free memory Mon2D.. */
    if ((mc_mn_Vars->Flag_Auto_Limits || mc_mn_Vars->Flag_List) && mc_mn_Vars->Coord_Number)
    { /* Dim : (mc_mn_Vars->Coord_Number+1)*mc_mn_Vars->Buffer_Block matrix (for p, dp) */
      if (mc_mn_Vars->Mon2D_Buffer != NULL) free(mc_mn_Vars->Mon2D_Buffer);
    }

    /* 1D and n1D case : mc_mn_Vars->Flag_Multiple */
    if (mc_mn_Vars->Flag_Multiple && mc_mn_Vars->Coord_Number)
    { /* Dim : mc_mn_Vars->Coord_Number*mc_mn_Vars->Coord_Bin[mc_mn_i] vectors */
      for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Number; mc_mn_i++)
      {
        free(mc_mn_Vars->Mon2D_N[mc_mn_i]);
        free(mc_mn_Vars->Mon2D_p[mc_mn_i]);
        free(mc_mn_Vars->Mon2D_p2[mc_mn_i]);
      }
      free(mc_mn_Vars->Mon2D_N);
      free(mc_mn_Vars->Mon2D_p);
      free(mc_mn_Vars->Mon2D_p2);
    }


    /* 2D case : mc_mn_Vars->Coord_Number==2 and !mc_mn_Vars->Flag_Multiple and !mc_mn_Vars->Flag_List */
    if ((mc_mn_Vars->Coord_Number == 2) && !mc_mn_Vars->Flag_Multiple)
    { /* Dim : mc_mn_Vars->Coord_Bin[1]*mc_mn_Vars->Coord_Bin[2] matrix */
      for (mc_mn_i= 0; mc_mn_i < mc_mn_Vars->Coord_Bin[1]; mc_mn_i++)
      {
        free(mc_mn_Vars->Mon2D_N[mc_mn_i]);
        free(mc_mn_Vars->Mon2D_p[mc_mn_i]);
        free(mc_mn_Vars->Mon2D_p2[mc_mn_i]);
      }
      free(mc_mn_Vars->Mon2D_N);
      free(mc_mn_Vars->Mon2D_p);
      free(mc_mn_Vars->Mon2D_p2);
    }
  } /* end Monitor_nD_Finally */

/* ========================================================================= */
/* ADD: E.Farhi, Aug 6th, 2001: Monitor_nD section */
/* this routine is used to display component */
/* ========================================================================= */

void Monitor_nD_McDisplay(MonitornD_Defines_type *mc_mn_DEFS,
  MonitornD_Variables_type *mc_mn_Vars)
  {
    double mc_mn_radius, mc_mn_h;
    double mc_mn_xmin;
    double mc_mn_xmax;
    double mc_mn_ymin;
    double mc_mn_ymax;
    double mc_mn_zmin;
    double mc_mn_zmax;
    int    mc_mn_i;
    double mc_mn_hdiv_min=-180, mc_mn_hdiv_max=180, mc_mn_vdiv_min=-180, mc_mn_vdiv_max=180;
    char   mc_mn_restricted = 0;

    mc_mn_radius = mc_mn_Vars->Sphere_Radius;
    mc_mn_h = mc_mn_Vars->Cylinder_Height;
    mc_mn_xmin = mc_mn_Vars->mxmin;
    mc_mn_xmax = mc_mn_Vars->mxmax;
    mc_mn_ymin = mc_mn_Vars->mymin;
    mc_mn_ymax = mc_mn_Vars->mymax;
    mc_mn_zmin = mc_mn_Vars->mzmin;
    mc_mn_zmax = mc_mn_Vars->mzmax;

    /* determine if there are angular limits set at start (no auto) in coord_types
     * cylinder/banana: look for hdiv
     * sphere: look for angle, radius (->atan2(val,mc_mn_radius)), hdiv, vdiv
     * this activates a 'restricted' flag, to draw a region as blades on cylinder/sphere
     */
    for (mc_mn_i= 0; mc_mn_i <= mc_mn_Vars->Coord_Number; mc_mn_i++)
    {
      int mc_mn_Set_Vars_Coord_Type;
      mc_mn_Set_Vars_Coord_Type = (mc_mn_Vars->Coord_Type[mc_mn_i] & 31);
      if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_HDIV || mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_THETA)
      { mc_mn_hdiv_min = mc_mn_Vars->Coord_Min[mc_mn_i]; mc_mn_hdiv_max = mc_mn_Vars->Coord_Max[mc_mn_i]; mc_mn_restricted = 1; }
      else if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_VDIV || mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_PHI)
      { mc_mn_vdiv_min = mc_mn_Vars->Coord_Min[mc_mn_i]; mc_mn_vdiv_max = mc_mn_Vars->Coord_Max[mc_mn_i];mc_mn_restricted = 1;  }
      else if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_ANGLE)
      { mc_mn_hdiv_min = mc_mn_vdiv_min = mc_mn_Vars->Coord_Min[mc_mn_i];
        mc_mn_hdiv_max = mc_mn_vdiv_max = mc_mn_Vars->Coord_Max[mc_mn_i];
        mc_mn_restricted = 1; }
      else if (mc_mn_Set_Vars_Coord_Type == mc_mn_DEFS->COORD_RADIUS)
      { double angle;
        angle = RAD2DEG*atan2(mc_mn_Vars->Coord_Max[mc_mn_i], mc_mn_radius);
        mc_mn_hdiv_min = mc_mn_vdiv_min = angle;
        mc_mn_hdiv_max = mc_mn_vdiv_max = angle;
        mc_mn_restricted = 1; }
    }

    if ((!mc_mn_restricted && (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_SPHERE))
    || abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_PREVIOUS)
    {
      mcdis_magnify("");
      mcdis_circle("xy",0,0,0,mc_mn_radius);
      mcdis_circle("xz",0,0,0,mc_mn_radius);
      mcdis_circle("yz",0,0,0,mc_mn_radius);
    }
    else if (mc_mn_restricted && ((abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_CYLIND) || (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_BANANA) || (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_SPHERE)))
    {
      int NH=24, NV=24;
      int ih, iv;
      double width, height;
      int issphere;
      issphere = (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_SPHERE);
      width = (mc_mn_hdiv_max-mc_mn_hdiv_min)/NH;
      height= (mc_mn_vdiv_max-mc_mn_vdiv_min)/NV;
      mcdis_magnify("xyz");
      for(ih = 0; ih < NH; ih++)
        for(iv = 0; iv < NV; iv++)
        {
          double theta0, phi0, theta1, phi1;
          double x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3;
          double ymin, ymax;
          phi0 = (mc_mn_hdiv_min+ width*ih)*DEG2RAD; /* in xz plane */
          phi1 = (mc_mn_hdiv_min+ width*(ih+1))*DEG2RAD;
          if (issphere)
          {
            theta0= (90-mc_mn_vdiv_min+height*iv)*DEG2RAD;
            theta1= (90-mc_mn_vdiv_min+height*(iv+1))*DEG2RAD;
          } else
          {
            theta0= theta1 = PI/2;
            ymin  = mc_mn_ymin+(mc_mn_ymax-mc_mn_ymin)*(iv/NV);
            ymax  = mc_mn_ymin+(mc_mn_ymax-mc_mn_ymin)*((iv+1)/NV);
          }
          z0 = mc_mn_radius*sin(theta0)*cos(phi0);
          x0 = mc_mn_radius*sin(theta0)*sin(phi0);
          if (issphere) y0 = mc_mn_radius*cos(theta0); else y0 = ymin;
          z1 = mc_mn_radius*sin(theta1)*cos(phi0);
          x1 = mc_mn_radius*sin(theta1)*sin(phi0);
          if (issphere) y1 = mc_mn_radius*cos(theta1); else y1 = ymax;
          z2 = mc_mn_radius*sin(theta1)*cos(phi1);
          x2 = mc_mn_radius*sin(theta1)*sin(phi1);
          y2 = y1;
          z3 = mc_mn_radius*sin(theta0)*cos(phi1);
          x3 = mc_mn_radius*sin(theta0)*sin(phi1);
          y3 = y0;
          mcdis_multiline(5,
            x0,y0,z0,
            x1,y1,z1,
            x2,y2,z2,
            x3,y3,z3,
            x0,y0,z0);
        }
    }
    else
    if (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_DISK)
    {
      mcdis_magnify("");
      mcdis_circle("xy",0,0,0,mc_mn_radius);
    }
    else
    if (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_SQUARE)
    {
      mcdis_magnify("xy");
      mcdis_multiline(5, (double)mc_mn_xmin, (double)mc_mn_ymin, 0.0,
             (double)mc_mn_xmax, (double)mc_mn_ymin, 0.0,
             (double)mc_mn_xmax, (double)mc_mn_ymax, 0.0,
             (double)mc_mn_xmin, (double)mc_mn_ymax, 0.0,
             (double)mc_mn_xmin, (double)mc_mn_ymin, 0.0);
    }
    else
    if (!mc_mn_restricted && ((abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_CYLIND) || (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_BANANA)))
    {
      mcdis_magnify("xyz");
      mcdis_circle("xz", 0,  mc_mn_h/2.0, 0, mc_mn_radius);
      mcdis_circle("xz", 0, -mc_mn_h/2.0, 0, mc_mn_radius);
      mcdis_line(-mc_mn_radius, -mc_mn_h/2.0, 0, -mc_mn_radius, +mc_mn_h/2.0, 0);
      mcdis_line(+mc_mn_radius, -mc_mn_h/2.0, 0, +mc_mn_radius, +mc_mn_h/2.0, 0);
      mcdis_line(0, -mc_mn_h/2.0, -mc_mn_radius, 0, +mc_mn_h/2.0, -mc_mn_radius);
      mcdis_line(0, -mc_mn_h/2.0, +mc_mn_radius, 0, +mc_mn_h/2.0, +mc_mn_radius);
    }
    else
    if (abs(mc_mn_Vars->Flag_Shape) == mc_mn_DEFS->SHAPE_BOX)
    {
      mcdis_magnify("xyz");
      mcdis_multiline(5, mc_mn_xmin, mc_mn_ymin, mc_mn_zmin,
                   mc_mn_xmax, mc_mn_ymin, mc_mn_zmin,
                   mc_mn_xmax, mc_mn_ymax, mc_mn_zmin,
                   mc_mn_xmin, mc_mn_ymax, mc_mn_zmin,
                   mc_mn_xmin, mc_mn_ymin, mc_mn_zmin);
      mcdis_multiline(5, mc_mn_xmin, mc_mn_ymin, mc_mn_zmax,
                   mc_mn_xmax, mc_mn_ymin, mc_mn_zmax,
                   mc_mn_xmax, mc_mn_ymax, mc_mn_zmax,
                   mc_mn_xmin, mc_mn_ymax, mc_mn_zmax,
                   mc_mn_xmin, mc_mn_ymin, mc_mn_zmax);
      mcdis_line(mc_mn_xmin, mc_mn_ymin, mc_mn_zmin, mc_mn_xmin, mc_mn_ymin, mc_mn_zmax);
      mcdis_line(mc_mn_xmax, mc_mn_ymin, mc_mn_zmin, mc_mn_xmax, mc_mn_ymin, mc_mn_zmax);
      mcdis_line(mc_mn_xmin, mc_mn_ymax, mc_mn_zmin, mc_mn_xmin, mc_mn_ymax, mc_mn_zmax);
      mcdis_line(mc_mn_xmax, mc_mn_ymax, mc_mn_zmin, mc_mn_xmax, mc_mn_ymax, mc_mn_zmax);
    }
  } /* end Monitor_nD_McDisplay */

/* end of monitor_nd-lib.c */

#line 8940 "SEQ_11_09_2009.c"

/* Instrument parameters. */
MCNUM mcipFermi_nu;
MCNUM mcipFC_num;
MCNUM mcipT0_nu;
MCNUM mcipEdes;
MCNUM mcipT0_off;
MCNUM mcipsxmin;
MCNUM mcipsxmax;
MCNUM mcipsymin;
MCNUM mcipsymax;
char* mcipsam_file;

#define mcNUMIPAR 10
int mcnumipar = 10;
struct mcinputtable_struct mcinputtable[mcNUMIPAR+1] = {
  "Fermi_nu", &mcipFermi_nu, instr_type_double, "", 
  "FC_num", &mcipFC_num, instr_type_double, "1", 
  "T0_nu", &mcipT0_nu, instr_type_double, "", 
  "Edes", &mcipEdes, instr_type_double, "", 
  "T0_off", &mcipT0_off, instr_type_double, "", 
  "sxmin", &mcipsxmin, instr_type_double, "-0.04", 
  "sxmax", &mcipsxmax, instr_type_double, "0.04", 
  "symin", &mcipsymin, instr_type_double, "-0.04", 
  "symax", &mcipsymax, instr_type_double, "0.04", 
  "sam_file", &mcipsam_file, instr_type_string, "", 
  NULL, NULL, instr_type_double, ""
};

/* User declarations from instrument definition. */
#define mccompcurname Fermi_T0
#define Fermi_nu mcipFermi_nu
#define FC_num mcipFC_num
#define T0_nu mcipT0_nu
#define Edes mcipEdes
#define T0_off mcipT0_off
#define sxmin mcipsxmin
#define sxmax mcipsxmax
#define symin mcipsymin
#define symax mcipsymax
#define sam_file mcipsam_file
#line 16 "SEQ_11_09_2009.instr"
   double Emin,Emax;
   double Gu_R, Gu_alpha, Gu_Qc, Gu_W,Gu_m,Gu_m2;
   double phaseoff, phasefc1, phase_sam, phase_det,toffset,phase_T0,phase_Fermi;
   double phase_m1,phase_m2;
   double tmax,tplotmin,tplotmax;
   double crad,deltat,ccurv,cwid,T0_rad,nrad;
   double L1,L2,L3,samp_pos,LM1,LM2;
   double z_gs,z_T0,z_pt02;
   double pre_T01_h,pre_T01_w;
   double sh_end_w,sh_end_h,ws,hs;
   double ch_x, ch_y,T0_h1,T0_h2,T0_w1,T0_w2,sh_T0_slp_w,sh_T0_slp_h,T0wd2;   
   int nslits,nchans;
   char *detoptstr;
   char *dett0optstr;
   char *detsampoptstr;
   char *detdetoptstr;
   char *mon1optstr;
   char *mon2optstr;
   char *dettstr;
   char *dettstrB;
   char *dettstrD;
   char *tmpdettstr;   
   char *tmpdettstr2;
   char *uniquestr;
   
#line 9008 "SEQ_11_09_2009.c"
#undef sam_file
#undef symax
#undef symin
#undef sxmax
#undef sxmin
#undef T0_off
#undef Edes
#undef T0_nu
#undef FC_num
#undef Fermi_nu
#undef mccompcurname

/* Neutron state table at each component input (local coords) */
/* [x, y, z, vx, vy, vz, t, sx, sy, sz, p] */
MCNUM mccomp_storein[11*48];
/* Components position table (absolute and relative coords) */
Coords mccomp_posa[48];
Coords mccomp_posr[48];
/* Counter for each comp to check for inactive ones */
MCNUM  mcNCounter[48];
MCNUM  mcPCounter[48];
MCNUM  mcP2Counter[48];
#define mcNUMCOMP 47 /* number of components */
/* Counter for PROP ABSORB */
MCNUM  mcAbsorbProp[48];
/* Flag true when previous component acted on the neutron (SCATTER) */
MCNUM mcScattered=0;
/* Declarations of component definition and setting parameters. */

/* Definition parameters for component 'arm1' [1]. */
#define mccarm1_profile 0
/* Setting parameters for component 'arm1' [1]. */
MCNUM mccarm1_percent;
MCNUM mccarm1_flag_save;
MCNUM mccarm1_minutes;

/* Definition parameters for component 'mod' [2]. */
#define mccmod_S_filename "source_sct521_bu_17_1.dat"
/* Setting parameters for component 'mod' [2]. */
MCNUM mccmod_width;
MCNUM mccmod_height;
MCNUM mccmod_dist;
MCNUM mccmod_xw;
MCNUM mccmod_yh;
MCNUM mccmod_Emin;
MCNUM mccmod_Emax;

/* Setting parameters for component 'core_ves' [3]. */
MCNUM mcccore_ves_w1;
MCNUM mcccore_ves_h1;
MCNUM mcccore_ves_w2;
MCNUM mcccore_ves_h2;
MCNUM mcccore_ves_l;
MCNUM mcccore_ves_R0;
MCNUM mcccore_ves_Qcx;
MCNUM mcccore_ves_Qcy;
MCNUM mcccore_ves_alphax;
MCNUM mcccore_ves_alphay;
MCNUM mcccore_ves_W;
MCNUM mcccore_ves_k;
MCNUM mcccore_ves_d;
MCNUM mcccore_ves_mx;
MCNUM mcccore_ves_my;

/* Setting parameters for component 'shutter_guide' [4]. */
MCNUM mccshutter_guide_w1;
MCNUM mccshutter_guide_h1;
MCNUM mccshutter_guide_w2;
MCNUM mccshutter_guide_h2;
MCNUM mccshutter_guide_l;
MCNUM mccshutter_guide_R0;
MCNUM mccshutter_guide_Qcx;
MCNUM mccshutter_guide_Qcy;
MCNUM mccshutter_guide_alphax;
MCNUM mccshutter_guide_alphay;
MCNUM mccshutter_guide_W;
MCNUM mccshutter_guide_k;
MCNUM mccshutter_guide_d;
MCNUM mccshutter_guide_mx;
MCNUM mccshutter_guide_my;

/* Setting parameters for component 'guide1' [5]. */
MCNUM mccguide1_w1;
MCNUM mccguide1_h1;
MCNUM mccguide1_w2;
MCNUM mccguide1_h2;
MCNUM mccguide1_l;
MCNUM mccguide1_R0;
MCNUM mccguide1_Qcx;
MCNUM mccguide1_Qcy;
MCNUM mccguide1_alphax;
MCNUM mccguide1_alphay;
MCNUM mccguide1_W;
MCNUM mccguide1_k;
MCNUM mccguide1_d;
MCNUM mccguide1_mx;
MCNUM mccguide1_my;

/* Setting parameters for component 'guide2' [6]. */
MCNUM mccguide2_w1;
MCNUM mccguide2_h1;
MCNUM mccguide2_w2;
MCNUM mccguide2_h2;
MCNUM mccguide2_l;
MCNUM mccguide2_R0;
MCNUM mccguide2_Qcx;
MCNUM mccguide2_Qcy;
MCNUM mccguide2_alphax;
MCNUM mccguide2_alphay;
MCNUM mccguide2_W;
MCNUM mccguide2_k;
MCNUM mccguide2_d;
MCNUM mccguide2_mx;
MCNUM mccguide2_my;

/* Setting parameters for component 'guide3' [7]. */
MCNUM mccguide3_w1;
MCNUM mccguide3_h1;
MCNUM mccguide3_w2;
MCNUM mccguide3_h2;
MCNUM mccguide3_l;
MCNUM mccguide3_R0;
MCNUM mccguide3_Qcx;
MCNUM mccguide3_Qcy;
MCNUM mccguide3_alphax;
MCNUM mccguide3_alphay;
MCNUM mccguide3_W;
MCNUM mccguide3_k;
MCNUM mccguide3_d;
MCNUM mccguide3_mx;
MCNUM mccguide3_my;

/* Setting parameters for component 'guide4' [8]. */
MCNUM mccguide4_w1;
MCNUM mccguide4_h1;
MCNUM mccguide4_w2;
MCNUM mccguide4_h2;
MCNUM mccguide4_l;
MCNUM mccguide4_R0;
MCNUM mccguide4_Qcx;
MCNUM mccguide4_Qcy;
MCNUM mccguide4_alphax;
MCNUM mccguide4_alphay;
MCNUM mccguide4_W;
MCNUM mccguide4_k;
MCNUM mccguide4_d;
MCNUM mccguide4_mx;
MCNUM mccguide4_my;

/* Setting parameters for component 'guide5' [9]. */
MCNUM mccguide5_w1;
MCNUM mccguide5_h1;
MCNUM mccguide5_w2;
MCNUM mccguide5_h2;
MCNUM mccguide5_l;
MCNUM mccguide5_R0;
MCNUM mccguide5_Qcx;
MCNUM mccguide5_Qcy;
MCNUM mccguide5_alphax;
MCNUM mccguide5_alphay;
MCNUM mccguide5_W;
MCNUM mccguide5_k;
MCNUM mccguide5_d;
MCNUM mccguide5_mx;
MCNUM mccguide5_my;

/* Setting parameters for component 'guide6' [10]. */
MCNUM mccguide6_w1;
MCNUM mccguide6_h1;
MCNUM mccguide6_w2;
MCNUM mccguide6_h2;
MCNUM mccguide6_l;
MCNUM mccguide6_R0;
MCNUM mccguide6_Qcx;
MCNUM mccguide6_Qcy;
MCNUM mccguide6_alphax;
MCNUM mccguide6_alphay;
MCNUM mccguide6_W;
MCNUM mccguide6_k;
MCNUM mccguide6_d;
MCNUM mccguide6_mx;
MCNUM mccguide6_my;

/* Setting parameters for component 'guide7' [11]. */
MCNUM mccguide7_w1;
MCNUM mccguide7_h1;
MCNUM mccguide7_w2;
MCNUM mccguide7_h2;
MCNUM mccguide7_l;
MCNUM mccguide7_R0;
MCNUM mccguide7_Qcx;
MCNUM mccguide7_Qcy;
MCNUM mccguide7_alphax;
MCNUM mccguide7_alphay;
MCNUM mccguide7_W;
MCNUM mccguide7_k;
MCNUM mccguide7_d;
MCNUM mccguide7_mx;
MCNUM mccguide7_my;

/* Setting parameters for component 'guide8' [12]. */
MCNUM mccguide8_w1;
MCNUM mccguide8_h1;
MCNUM mccguide8_w2;
MCNUM mccguide8_h2;
MCNUM mccguide8_l;
MCNUM mccguide8_R0;
MCNUM mccguide8_Qcx;
MCNUM mccguide8_Qcy;
MCNUM mccguide8_alphax;
MCNUM mccguide8_alphay;
MCNUM mccguide8_W;
MCNUM mccguide8_k;
MCNUM mccguide8_d;
MCNUM mccguide8_mx;
MCNUM mccguide8_my;

/* Setting parameters for component 'guide9' [13]. */
MCNUM mccguide9_w1;
MCNUM mccguide9_h1;
MCNUM mccguide9_w2;
MCNUM mccguide9_h2;
MCNUM mccguide9_l;
MCNUM mccguide9_R0;
MCNUM mccguide9_Qcx;
MCNUM mccguide9_Qcy;
MCNUM mccguide9_alphax;
MCNUM mccguide9_alphay;
MCNUM mccguide9_W;
MCNUM mccguide9_k;
MCNUM mccguide9_d;
MCNUM mccguide9_mx;
MCNUM mccguide9_my;

/* Setting parameters for component 'guide10' [14]. */
MCNUM mccguide10_w1;
MCNUM mccguide10_h1;
MCNUM mccguide10_w2;
MCNUM mccguide10_h2;
MCNUM mccguide10_l;
MCNUM mccguide10_R0;
MCNUM mccguide10_Qcx;
MCNUM mccguide10_Qcy;
MCNUM mccguide10_alphax;
MCNUM mccguide10_alphay;
MCNUM mccguide10_W;
MCNUM mccguide10_k;
MCNUM mccguide10_d;
MCNUM mccguide10_mx;
MCNUM mccguide10_my;

/* Setting parameters for component 'guide11' [15]. */
MCNUM mccguide11_w1;
MCNUM mccguide11_h1;
MCNUM mccguide11_w2;
MCNUM mccguide11_h2;
MCNUM mccguide11_l;
MCNUM mccguide11_R0;
MCNUM mccguide11_Qcx;
MCNUM mccguide11_Qcy;
MCNUM mccguide11_alphax;
MCNUM mccguide11_alphay;
MCNUM mccguide11_W;
MCNUM mccguide11_k;
MCNUM mccguide11_d;
MCNUM mccguide11_mx;
MCNUM mccguide11_my;

/* Definition parameters for component 't0_chopp' [16]. */
#define mcct0_chopp_len 0.474
#define mcct0_chopp_w1 0.08
#define mcct0_chopp_w2 0.101
#define mcct0_chopp_nu mcipT0_nu
#define mcct0_chopp_delta 0.0
#define mcct0_chopp_tc phase_T0
#define mcct0_chopp_ymin -0.045
#define mcct0_chopp_ymax 0.045

/* Definition parameters for component 't_check1' [17]. */
#define mcct_check1_nchan 100
/* Setting parameters for component 't_check1' [17]. */
MCNUM mcct_check1_xmin;
MCNUM mcct_check1_xmax;
MCNUM mcct_check1_ymin;
MCNUM mcct_check1_ymax;
MCNUM mcct_check1_tmin;
MCNUM mcct_check1_tmax;
char mcct_check1_filename[1024];

/* Setting parameters for component 'guide13' [18]. */
MCNUM mccguide13_w1;
MCNUM mccguide13_h1;
MCNUM mccguide13_w2;
MCNUM mccguide13_h2;
MCNUM mccguide13_l;
MCNUM mccguide13_R0;
MCNUM mccguide13_Qcx;
MCNUM mccguide13_Qcy;
MCNUM mccguide13_alphax;
MCNUM mccguide13_alphay;
MCNUM mccguide13_W;
MCNUM mccguide13_k;
MCNUM mccguide13_d;
MCNUM mccguide13_mx;
MCNUM mccguide13_my;

/* Setting parameters for component 'guide14' [19]. */
MCNUM mccguide14_w1;
MCNUM mccguide14_h1;
MCNUM mccguide14_w2;
MCNUM mccguide14_h2;
MCNUM mccguide14_l;
MCNUM mccguide14_R0;
MCNUM mccguide14_Qcx;
MCNUM mccguide14_Qcy;
MCNUM mccguide14_alphax;
MCNUM mccguide14_alphay;
MCNUM mccguide14_W;
MCNUM mccguide14_k;
MCNUM mccguide14_d;
MCNUM mccguide14_mx;
MCNUM mccguide14_my;

/* Setting parameters for component 'guide15' [20]. */
MCNUM mccguide15_w1;
MCNUM mccguide15_h1;
MCNUM mccguide15_w2;
MCNUM mccguide15_h2;
MCNUM mccguide15_l;
MCNUM mccguide15_R0;
MCNUM mccguide15_Qcx;
MCNUM mccguide15_Qcy;
MCNUM mccguide15_alphax;
MCNUM mccguide15_alphay;
MCNUM mccguide15_W;
MCNUM mccguide15_k;
MCNUM mccguide15_d;
MCNUM mccguide15_mx;
MCNUM mccguide15_my;

/* Setting parameters for component 'guide16' [21]. */
MCNUM mccguide16_w1;
MCNUM mccguide16_h1;
MCNUM mccguide16_w2;
MCNUM mccguide16_h2;
MCNUM mccguide16_l;
MCNUM mccguide16_R0;
MCNUM mccguide16_Qcx;
MCNUM mccguide16_Qcy;
MCNUM mccguide16_alphax;
MCNUM mccguide16_alphay;
MCNUM mccguide16_W;
MCNUM mccguide16_k;
MCNUM mccguide16_d;
MCNUM mccguide16_mx;
MCNUM mccguide16_my;

/* Setting parameters for component 'guide17' [22]. */
MCNUM mccguide17_w1;
MCNUM mccguide17_h1;
MCNUM mccguide17_w2;
MCNUM mccguide17_h2;
MCNUM mccguide17_l;
MCNUM mccguide17_R0;
MCNUM mccguide17_Qcx;
MCNUM mccguide17_Qcy;
MCNUM mccguide17_alphax;
MCNUM mccguide17_alphay;
MCNUM mccguide17_W;
MCNUM mccguide17_k;
MCNUM mccguide17_d;
MCNUM mccguide17_mx;
MCNUM mccguide17_my;

/* Setting parameters for component 'guide18' [23]. */
MCNUM mccguide18_w1;
MCNUM mccguide18_h1;
MCNUM mccguide18_w2;
MCNUM mccguide18_h2;
MCNUM mccguide18_l;
MCNUM mccguide18_R0;
MCNUM mccguide18_Qcx;
MCNUM mccguide18_Qcy;
MCNUM mccguide18_alphax;
MCNUM mccguide18_alphay;
MCNUM mccguide18_W;
MCNUM mccguide18_k;
MCNUM mccguide18_d;
MCNUM mccguide18_mx;
MCNUM mccguide18_my;

/* Setting parameters for component 'guide19' [24]. */
MCNUM mccguide19_w1;
MCNUM mccguide19_h1;
MCNUM mccguide19_w2;
MCNUM mccguide19_h2;
MCNUM mccguide19_l;
MCNUM mccguide19_R0;
MCNUM mccguide19_Qcx;
MCNUM mccguide19_Qcy;
MCNUM mccguide19_alphax;
MCNUM mccguide19_alphay;
MCNUM mccguide19_W;
MCNUM mccguide19_k;
MCNUM mccguide19_d;
MCNUM mccguide19_mx;
MCNUM mccguide19_my;

/* Setting parameters for component 'guide20' [25]. */
MCNUM mccguide20_w1;
MCNUM mccguide20_h1;
MCNUM mccguide20_w2;
MCNUM mccguide20_h2;
MCNUM mccguide20_l;
MCNUM mccguide20_R0;
MCNUM mccguide20_Qcx;
MCNUM mccguide20_Qcy;
MCNUM mccguide20_alphax;
MCNUM mccguide20_alphay;
MCNUM mccguide20_W;
MCNUM mccguide20_k;
MCNUM mccguide20_d;
MCNUM mccguide20_mx;
MCNUM mccguide20_my;

/* Setting parameters for component 'guide21' [26]. */
MCNUM mccguide21_w1;
MCNUM mccguide21_h1;
MCNUM mccguide21_w2;
MCNUM mccguide21_h2;
MCNUM mccguide21_l;
MCNUM mccguide21_R0;
MCNUM mccguide21_Qcx;
MCNUM mccguide21_Qcy;
MCNUM mccguide21_alphax;
MCNUM mccguide21_alphay;
MCNUM mccguide21_W;
MCNUM mccguide21_k;
MCNUM mccguide21_d;
MCNUM mccguide21_mx;
MCNUM mccguide21_my;

/* Setting parameters for component 'guide22' [27]. */
MCNUM mccguide22_w1;
MCNUM mccguide22_h1;
MCNUM mccguide22_w2;
MCNUM mccguide22_h2;
MCNUM mccguide22_l;
MCNUM mccguide22_R0;
MCNUM mccguide22_Qcx;
MCNUM mccguide22_Qcy;
MCNUM mccguide22_alphax;
MCNUM mccguide22_alphay;
MCNUM mccguide22_W;
MCNUM mccguide22_k;
MCNUM mccguide22_d;
MCNUM mccguide22_mx;
MCNUM mccguide22_my;

/* Setting parameters for component 'guide23' [28]. */
MCNUM mccguide23_w1;
MCNUM mccguide23_h1;
MCNUM mccguide23_w2;
MCNUM mccguide23_h2;
MCNUM mccguide23_l;
MCNUM mccguide23_R0;
MCNUM mccguide23_Qcx;
MCNUM mccguide23_Qcy;
MCNUM mccguide23_alphax;
MCNUM mccguide23_alphay;
MCNUM mccguide23_W;
MCNUM mccguide23_k;
MCNUM mccguide23_d;
MCNUM mccguide23_mx;
MCNUM mccguide23_my;

/* Setting parameters for component 'guide24' [29]. */
MCNUM mccguide24_w1;
MCNUM mccguide24_h1;
MCNUM mccguide24_w2;
MCNUM mccguide24_h2;
MCNUM mccguide24_l;
MCNUM mccguide24_R0;
MCNUM mccguide24_Qcx;
MCNUM mccguide24_Qcy;
MCNUM mccguide24_alphax;
MCNUM mccguide24_alphay;
MCNUM mccguide24_W;
MCNUM mccguide24_k;
MCNUM mccguide24_d;
MCNUM mccguide24_mx;
MCNUM mccguide24_my;

/* Setting parameters for component 'guide25' [30]. */
MCNUM mccguide25_w1;
MCNUM mccguide25_h1;
MCNUM mccguide25_w2;
MCNUM mccguide25_h2;
MCNUM mccguide25_l;
MCNUM mccguide25_R0;
MCNUM mccguide25_Qcx;
MCNUM mccguide25_Qcy;
MCNUM mccguide25_alphax;
MCNUM mccguide25_alphay;
MCNUM mccguide25_W;
MCNUM mccguide25_k;
MCNUM mccguide25_d;
MCNUM mccguide25_mx;
MCNUM mccguide25_my;

/* Setting parameters for component 'guide26' [31]. */
MCNUM mccguide26_w1;
MCNUM mccguide26_h1;
MCNUM mccguide26_w2;
MCNUM mccguide26_h2;
MCNUM mccguide26_l;
MCNUM mccguide26_R0;
MCNUM mccguide26_Qcx;
MCNUM mccguide26_Qcy;
MCNUM mccguide26_alphax;
MCNUM mccguide26_alphay;
MCNUM mccguide26_W;
MCNUM mccguide26_k;
MCNUM mccguide26_d;
MCNUM mccguide26_mx;
MCNUM mccguide26_my;

/* Setting parameters for component 'guide27' [32]. */
MCNUM mccguide27_w1;
MCNUM mccguide27_h1;
MCNUM mccguide27_w2;
MCNUM mccguide27_h2;
MCNUM mccguide27_l;
MCNUM mccguide27_R0;
MCNUM mccguide27_Qcx;
MCNUM mccguide27_Qcy;
MCNUM mccguide27_alphax;
MCNUM mccguide27_alphay;
MCNUM mccguide27_W;
MCNUM mccguide27_k;
MCNUM mccguide27_d;
MCNUM mccguide27_mx;
MCNUM mccguide27_my;

/* Definition parameters for component 'fermi_chopp' [33]. */
#define mccfermi_chopp_len 0.10
#define mccfermi_chopp_w 0.06
#define mccfermi_chopp_nu mcipFermi_nu
#define mccfermi_chopp_delta 0.0
#define mccfermi_chopp_tc phase_Fermi
#define mccfermi_chopp_ymin -.0325
#define mccfermi_chopp_ymax .0325
#define mccfermi_chopp_nchan nchans
#define mccfermi_chopp_bw 0.0005
#define mccfermi_chopp_blader nrad

/* Setting parameters for component 'adjustable_slits' [34]. */
MCNUM mccadjustable_slits_xmin;
MCNUM mccadjustable_slits_xmax;
MCNUM mccadjustable_slits_ymin;
MCNUM mccadjustable_slits_ymax;
MCNUM mccadjustable_slits_radius;
MCNUM mccadjustable_slits_cut;
MCNUM mccadjustable_slits_width;
MCNUM mccadjustable_slits_height;

/* Definition parameters for component 'Monitor1' [35]. */
#define mccMonitor1_nchan 100
/* Setting parameters for component 'Monitor1' [35]. */
MCNUM mccMonitor1_xmin;
MCNUM mccMonitor1_xmax;
MCNUM mccMonitor1_ymin;
MCNUM mccMonitor1_ymax;
MCNUM mccMonitor1_tmin;
MCNUM mccMonitor1_tmax;
char mccMonitor1_filename[1024];

/* Setting parameters for component 'guide29' [36]. */
MCNUM mccguide29_w1;
MCNUM mccguide29_h1;
MCNUM mccguide29_w2;
MCNUM mccguide29_h2;
MCNUM mccguide29_l;
MCNUM mccguide29_R0;
MCNUM mccguide29_Qcx;
MCNUM mccguide29_Qcy;
MCNUM mccguide29_alphax;
MCNUM mccguide29_alphay;
MCNUM mccguide29_W;
MCNUM mccguide29_k;
MCNUM mccguide29_d;
MCNUM mccguide29_mx;
MCNUM mccguide29_my;

/* Setting parameters for component 'guide31' [37]. */
MCNUM mccguide31_w1;
MCNUM mccguide31_h1;
MCNUM mccguide31_w2;
MCNUM mccguide31_h2;
MCNUM mccguide31_l;
MCNUM mccguide31_R0;
MCNUM mccguide31_Qcx;
MCNUM mccguide31_Qcy;
MCNUM mccguide31_alphax;
MCNUM mccguide31_alphay;
MCNUM mccguide31_W;
MCNUM mccguide31_k;
MCNUM mccguide31_d;
MCNUM mccguide31_mx;
MCNUM mccguide31_my;

/* Setting parameters for component 'guide32' [38]. */
MCNUM mccguide32_w1;
MCNUM mccguide32_h1;
MCNUM mccguide32_w2;
MCNUM mccguide32_h2;
MCNUM mccguide32_l;
MCNUM mccguide32_R0;
MCNUM mccguide32_Qcx;
MCNUM mccguide32_Qcy;
MCNUM mccguide32_alphax;
MCNUM mccguide32_alphay;
MCNUM mccguide32_W;
MCNUM mccguide32_k;
MCNUM mccguide32_d;
MCNUM mccguide32_mx;
MCNUM mccguide32_my;

/* Setting parameters for component 'guide34' [39]. */
MCNUM mccguide34_w1;
MCNUM mccguide34_h1;
MCNUM mccguide34_w2;
MCNUM mccguide34_h2;
MCNUM mccguide34_l;
MCNUM mccguide34_R0;
MCNUM mccguide34_Qcx;
MCNUM mccguide34_Qcy;
MCNUM mccguide34_alphax;
MCNUM mccguide34_alphay;
MCNUM mccguide34_W;
MCNUM mccguide34_k;
MCNUM mccguide34_d;
MCNUM mccguide34_mx;
MCNUM mccguide34_my;

/* Definition parameters for component 'E_det' [40]. */
#define mccE_det_nchan 50
#define mccE_det_filename detoptstr
#define mccE_det_restore_neutron 0
/* Setting parameters for component 'E_det' [40]. */
MCNUM mccE_det_xmin;
MCNUM mccE_det_xmax;
MCNUM mccE_det_ymin;
MCNUM mccE_det_ymax;
MCNUM mccE_det_xwidth;
MCNUM mccE_det_yheight;
MCNUM mccE_det_Emin;
MCNUM mccE_det_Emax;

/* Setting parameters for component 'sample' [42]. */
MCNUM mccsample_radius_i;
MCNUM mccsample_radius_o;
MCNUM mccsample_h;
MCNUM mccsample_focus_r;
MCNUM mccsample_pack;
MCNUM mccsample_frac;
MCNUM mccsample_f_QE;
MCNUM mccsample_gamma;
MCNUM mccsample_target_x;
MCNUM mccsample_target_y;
MCNUM mccsample_target_z;
MCNUM mccsample_focus_xw;
MCNUM mccsample_focus_yh;
MCNUM mccsample_focus_aw;
MCNUM mccsample_focus_ah;
MCNUM mccsample_xwidth;
MCNUM mccsample_yheight;
MCNUM mccsample_zthick;
MCNUM mccsample_rad_sphere;
MCNUM mccsample_sig_a;
MCNUM mccsample_sig_i;
MCNUM mccsample_V0;
int mccsample_target_index;
MCNUM mccsample_multiples;

/* Definition parameters for component 't_mon_detC' [43]. */
#define mcct_mon_detC_options "banana t theta limits=[-30.0 60.0] y limits=[-0.636 0.564] list all outgoing parallel file=detc"
#define mcct_mon_detC_filename 0
#define mcct_mon_detC_user1 FLT_MAX
#define mcct_mon_detC_user2 FLT_MAX
#define mcct_mon_detC_user3 FLT_MAX
#define mcct_mon_detC_username1 0
#define mcct_mon_detC_username2 0
#define mcct_mon_detC_username3 0
/* Setting parameters for component 't_mon_detC' [43]. */
MCNUM mcct_mon_detC_xwidth;
MCNUM mcct_mon_detC_yheight;
MCNUM mcct_mon_detC_zthick;
MCNUM mcct_mon_detC_xmin;
MCNUM mcct_mon_detC_xmax;
MCNUM mcct_mon_detC_ymin;
MCNUM mcct_mon_detC_ymax;
MCNUM mcct_mon_detC_zmin;
MCNUM mcct_mon_detC_zmax;
MCNUM mcct_mon_detC_bins;
MCNUM mcct_mon_detC_min;
MCNUM mcct_mon_detC_max;
MCNUM mcct_mon_detC_restore_neutron;

/* Definition parameters for component 't_mon_detB' [44]. */
#define mcct_mon_detB_options "banana t theta limits=[-30.0 60.0] y limits=[-1.904 -0.704] list all outgoing parallel file=detb"
#define mcct_mon_detB_filename 0
#define mcct_mon_detB_user1 FLT_MAX
#define mcct_mon_detB_user2 FLT_MAX
#define mcct_mon_detB_user3 FLT_MAX
#define mcct_mon_detB_username1 0
#define mcct_mon_detB_username2 0
#define mcct_mon_detB_username3 0
/* Setting parameters for component 't_mon_detB' [44]. */
MCNUM mcct_mon_detB_xwidth;
MCNUM mcct_mon_detB_yheight;
MCNUM mcct_mon_detB_zthick;
MCNUM mcct_mon_detB_xmin;
MCNUM mcct_mon_detB_xmax;
MCNUM mcct_mon_detB_ymin;
MCNUM mcct_mon_detB_ymax;
MCNUM mcct_mon_detB_zmin;
MCNUM mcct_mon_detB_zmax;
MCNUM mcct_mon_detB_bins;
MCNUM mcct_mon_detB_min;
MCNUM mcct_mon_detB_max;
MCNUM mcct_mon_detB_restore_neutron;

/* Definition parameters for component 't_mon_detD' [45]. */
#define mcct_mon_detD_options "banana t theta limits=[-30.0 60.0] y limits=[0.633 1.833] list all outgoing file=detd"
#define mcct_mon_detD_filename 0
#define mcct_mon_detD_user1 FLT_MAX
#define mcct_mon_detD_user2 FLT_MAX
#define mcct_mon_detD_user3 FLT_MAX
#define mcct_mon_detD_username1 0
#define mcct_mon_detD_username2 0
#define mcct_mon_detD_username3 0
/* Setting parameters for component 't_mon_detD' [45]. */
MCNUM mcct_mon_detD_xwidth;
MCNUM mcct_mon_detD_yheight;
MCNUM mcct_mon_detD_zthick;
MCNUM mcct_mon_detD_xmin;
MCNUM mcct_mon_detD_xmax;
MCNUM mcct_mon_detD_ymin;
MCNUM mcct_mon_detD_ymax;
MCNUM mcct_mon_detD_zmin;
MCNUM mcct_mon_detD_zmax;
MCNUM mcct_mon_detD_bins;
MCNUM mcct_mon_detD_min;
MCNUM mcct_mon_detD_max;
MCNUM mcct_mon_detD_restore_neutron;

/* Definition parameters for component 't_mon2' [46]. */
#define mcct_mon2_nchan 100
/* Setting parameters for component 't_mon2' [46]. */
MCNUM mcct_mon2_xmin;
MCNUM mcct_mon2_xmax;
MCNUM mcct_mon2_ymin;
MCNUM mcct_mon2_ymax;
MCNUM mcct_mon2_tmin;
MCNUM mcct_mon2_tmax;
char mcct_mon2_filename[1024];

/* User component declarations. */

/* User declarations for component 'arm1' [1]. */
#define mccompcurname  arm1
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define profile mccarm1_profile
#define IntermediateCnts mccarm1_IntermediateCnts
#define StartTime mccarm1_StartTime
#define EndTime mccarm1_EndTime
#define percent mccarm1_percent
#define flag_save mccarm1_flag_save
#define minutes mccarm1_minutes
#line 48 "/usr/local/lib/mcstas/misc/Progress_bar.comp"
#ifndef PROGRESS_BAR
#define PROGRESS_BAR
#else
#error Only one Progress_bar component may be used in an instrument definition.
#endif

  double IntermediateCnts=0;
  time_t StartTime       =0;
  time_t EndTime         =0;
  time_t CurrentTime     =0;
#line 9801 "SEQ_11_09_2009.c"
#undef minutes
#undef flag_save
#undef percent
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef profile
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'mod' [2]. */
#define mccompcurname  mod
#define mccompcurtype  SNS_source
#define mccompcurindex 2
#define S_filename mccmod_S_filename
#define hdiv mccmod_hdiv
#define vdiv mccmod_vdiv
#define p_in mccmod_p_in
#define width mccmod_width
#define height mccmod_height
#define dist mccmod_dist
#define xw mccmod_xw
#define yh mccmod_yh
#define Emin mccmod_Emin
#define Emax mccmod_Emax
#line 51 "SNS_source.comp"
  double xonly(double);
  double Pfunc(double,double);
  double txonly(double);
  double tPfunc(double,double);
  double hdiv,vdiv;
  double p_in;
  double *inxvec,*inyvec,*Pvec;
  int xylength;
  double *tcol, *Ecol;
  double *txval, *tyval;
  double *tPvec;
  double **Ptmat;
  double EPmax, EPmin,INorm,INorm2;
  int ntvals,idxstart,idxstop,tidxstart,tidxstop,nEvals;
  #define Maxlength 200
  #define MAXCOLS 500
  /* ----------------------------------------------------------------
      routine to load E, I and t I data from SNS source files
  -----------------------------------------------------------------*/

  void sns_source_load(char filename[], double *xvec, double *yvec, int xcol, int ycol, int *veclenptr, double *tcol, double *Ecol, double **Imat,int *ntvals, int *nEvals)
  {
    FILE *fp;
    int idx1,idx2,idx3; /* counter for number of x, y values */
    int jk,idx3max;
    int numtvals;
    int totalvals;
    float indat[6];
    double *Icoltmp, *tcoltmp, *Ecoltmp;
    char *line;
    char *lntoken, *cp;
    Icoltmp=malloc(100000*sizeof(double));
    tcoltmp=malloc(100000*sizeof(double));
    Ecoltmp=malloc(100000*sizeof(double));
    line=malloc(200*sizeof(char));
    /* open file */
    printf("%s\n",filename);
    fp=fopen(filename,"r");
    if (fp==NULL){
      printf("Error opening file");
      }
    /* skip header lines any line that begin with # */
    while((fgets(line,Maxlength,fp)!=NULL)&&(strchr(line,'#')!=NULL)){      
    }
    idx1=0;  
    /* read all lines that fit the format for the time integrated data*/
    while(sscanf(line," %f %f %f %f %f %f",&indat[0], &indat[1], &indat[2], &indat[3],&indat[4],&indat[5])>0){
        xvec[idx1]=indat[xcol];
        yvec[idx1]=indat[ycol];
        //printf("idx1 %i xvec %g yvec %g\n",idx1,xvec[idx1],yvec[idx1]);
        idx1++;
        fgets(line,Maxlength,fp);
    }
    idx1--;   // correct index since it counts one line past useful data
   // printf("idx1 %i\n",idx1);
    idx2=floor(idx1/2);
    while((idx2<idx1)&&(yvec[idx2]>0)){
      idx2++;
    }
    if(idx2<idx1){
      *veclenptr=idx2;
    }
    else{
      *veclenptr=idx1-2; 
    }
  /* find t data header */
    fgets(line,Maxlength,fp);
    while(strrchr(line,'#')==NULL){
      fgets(line,Maxlength,fp);
    }
  /*find end of t data header */
    while((fgets(line,Maxlength,fp)!=NULL)&&(strchr(line,'#')!=NULL)){      
    }
  /* read in t data */
 /*printf("t data read start\n");*/
    idx2=0;
   // while(fgets(line,Maxlength,fp)!=NULL){ 
   do {   
        jk=sscanf(line," %f %f %f %f",&indat[0], &indat[1], &indat[2], &indat[3]);
          if ((line!=NULL)&&(jk>3)){
            tcoltmp[idx2]=indat[0];
            Ecoltmp[idx2]=indat[1];
            Icoltmp[idx2]=indat[2];
           // printf("%d %d %g %g %g %g\n",idx2,jk,tcoltmp[idx2],Ecoltmp[idx2],Icoltmp[idx2],indat[3]);
            idx2++;
          }
    }
    while(fgets(line,Maxlength,fp)!=NULL);    
    fclose(fp);
    totalvals=idx2+1;
    printf("total vals: %d\n",totalvals);
    /* reformat data into an Ecol, a tcol, and an I matrix*/
    idx1=0;idx2=0;idx3=0;
    Ecol[idx2]=Ecoltmp[idx1];  
    tcol[idx3]=tcoltmp[idx1];
    Imat[idx3][idx2]=Icoltmp[idx1];
    idx1++;idx3++;
    while(idx1<totalvals){
      jk=idx1-1;    
      if(Ecoltmp[idx1]==Ecoltmp[jk]){
        tcol[idx3]=tcoltmp[idx1];
         Imat[idx3][idx2]=Icoltmp[idx1]; 
         idx1++;idx3++; 
      }    
      else{
        idx3max=idx3;
        idx2++;idx3=0;
        Ecol[idx2]=Ecoltmp[idx1];
        tcol[idx3]=tcoltmp[idx1];
        Imat[idx3][idx2]=Icoltmp[idx1];
        idx1++;
      }
    }
   *ntvals=idx3max+1;*nEvals=idx2;
   printf("ntvals: %i idx: %i\n",*ntvals, idx3);
   free(Icoltmp);free(tcoltmp);free(Ecoltmp);free(line);
  }
/*-------------------------------------------------------------
        End load file routines
--------------------------------------------------------------*/  
/*----------------------------------------------------------------------
                routine to do a 1D linear interpolation
------------------------------------------------------------------------*/
/* given a point (x1,y1) on the low side of xdes and one (x2,y2) on the
high side of xdes return the interpolated y values */
double linint(double xdes,double x1, double x2, double y1, double y2)
{
  double m;
  m=(y2-y1)/(x2-x1);
  return (m*(xdes-x1)+y1);
}

double linfuncint(double xdes, double xylen, double *vecx, double *vecy)
  {
  int idx;
  idx=0;
  while((vecx[idx]<xdes)&&idx<xylen){
     idx++;
    }
  if (idx>xylen){
      printf("error exceeded vector length");
    }
  if (vecx[idx]==xdes){
      return vecy[idx];
      }
   else
     {
     return linint(xdes,vecx[idx-1],vecx[idx],vecy[idx-1],vecy[idx]);
     }

  }
/*------------------------------------------------------------------------
            routine to perform a 1 d quadratic interpolation 
--------------------------------------------------------------------------*/
/* given 2 points on the low side of xdes and one on the high side, return
a quadratically interpolated result */
double quadint(double xdes,double x1, double x2,double x3, double y1, double
y2, double y3)
{
  double t1, t2, t3;
  t1=((xdes-x2)*(xdes-x3)*y1)/((x1-x2)*(x1-x3));
  t2=((xdes-x1)*(xdes-x3)*y2)/((x2-x1)*(x2-x3));
  t3=((xdes-x1)*(xdes-x2)*y3)/((x3-x1)*(x3-x2));
  return t1+t2+t3; 
}

double quadfuncint(double xdes, double xylen, double *vecx, double *vecy)
  {
  int idx;
  idx=1;
  while((vecx[idx]<xdes)&&idx<xylen){
     idx++;
    }
  if (idx>xylen){
      printf("error exceeded vector length");
    }

   if (vecx[idx]==xdes){
      return vecy[idx]; 
      }
   else
     {
     return quadint(xdes,vecx[idx-2],vecx[idx-1],vecx[idx],vecy[idx-2],vecy[idx-1],vecy[idx]);
     }
      
  }
/*-------------------------------------------------------------------
  integration routines
---------------------------------------------------------------------*/
double integtrap(double (*func)(double),double prev,double low,double high, int step)
{
 double s,npts,stpsze,sum,x;
 int pw2, idx;
 if (step==1){
   return(s=0.5*(high-low)*((*func)(high)+(*func)(low)));
 }
 else{
   s=prev;
   for(pw2=1,idx=1;idx<step-1;idx++){
     pw2<<=1;
   } 
   npts=pw2;
   stpsze=(high-low)/npts;
   x=low+0.5*stpsze;
   for(sum=0.0,idx=1;idx<=pw2;idx++,x+=stpsze){
     sum+=(*func)(x);
   }
   s=0.5*(s+(high-low)*sum/npts);
   return s;
 }
}
double integ1(double (*func)(double),double low, double high, double err)
{ 
  double out,outprev;
  int idx;
  out=integtrap(*func,0.0,low,high,1);
  outprev=out;  
  out=integtrap(*func,out,low,high,2);
  /*printf("out %g outprev %g \n",out,outprev);*/
  idx=2;
  while(fabs(out-outprev)>err*fabs(out)){
    idx++;
    outprev=out;
    out=integtrap(*func,out,low,high,idx);
   /* printf("out %g outprev %g \n",out,outprev);*/
  }
  return out;
}
/*---------------------------------------------------------------------------
   Routine for finding zeros. 
  Modified version of rtbis from "Numerical Recipes in C: pg 354
 -----------------------------------------------------------------------------*/

double zero_find(double (*func)(double, double),double yval,double xmin,double xmax, double tol)
{
  double xl,xh,f,fmid,xmid,dx,rtb;
  xl=xmin;
  xh=pow(10,(log10(xmin)+yval*(log10(xmax)-log10(xmin))));
  f=(*func)(xl,yval);
  fmid=(*func)(xh,yval);
  while (fmid*f>=0.0){
    xh=xh+(xh-xl)*2.0;
    fmid=(*func)(xh,yval);
  }
  dx=xh-xl;
  rtb=xl;
  while(fabs((*func)(rtb,yval))>tol){
    dx=dx*0.5;
    xmid=rtb+dx;
    fmid=(*func)(xmid,yval);
    if (fmid<0){
      rtb=xmid;
    }
  }
 return rtb;
}
/*----------------------------------------------------------------------------
Routine for calculating Probability distribution
----------------------------------------------------------------------------*/
void Pcalc(double (*func)(double),double llim, double hlim, double *xvec, double *Prob, int veclen, int *idxstart, int *idxstop)
{
  int idx1,idx2;
  double junk,Norm;
  idx1=0;
  while(xvec[idx1]<=llim){
     Prob[idx1]=0;
     idx1++;
     
  }
  if (idx1<1){
   printf("Error: lower energy limit is out of bounds\n");
   exit(0);
  }
  *idxstart=idx1;  
   Prob[idx1]=integ1((*func),llim,xvec[idx1],0.001);
   idx1++;
  while(xvec[idx1]<=hlim){    
     junk=integ1((*func),xvec[idx1-1],xvec[idx1],0.001);     
     Prob[idx1]=(Prob[idx1-1]+junk);    
     idx1++;    
   }
   *idxstop=idx1;
   while(idx1<veclen){
     Prob[idx1]=1;
     idx1++;
   }
   
  /*Normalize all Probability values*/
    Norm=Prob[*idxstop-1];
  if (Norm>0){
    for(idx2=*idxstart;idx2<*idxstop;idx2++){
      Prob[idx2]=Prob[idx2]/Norm;
    }
  }
}
/*----------------------------------------------------------------------------
Routine for calculating t Probability distribution
----------------------------------------------------------------------------*/
void tPcalc(double (*func)(double),double llim, double hlim, double *xvec, double *Prob, int veclen, int *idxstart, int *idxstop)
{
  int idx1,idx2;
  double junk,Norm;
  idx1=0;
  while(xvec[idx1]<=llim){
     Prob[idx1]=0;
     idx1++;
     
  }
  *idxstart=idx1;  
   Prob[idx1]=integ1((*func),llim,xvec[idx1],0.001);
  while(xvec[idx1]<=hlim){    
     junk=integ1((*func),xvec[idx1-1],xvec[idx1],0.001);
     Prob[idx1]=(Prob[idx1-1]+junk);
     idx1++;    
   }
   *idxstop=idx1;
   while(idx1<veclen){
     Prob[idx1]=1;
     idx1++;
   }
   /* calculate normalization*/
   Norm=Prob[*idxstop-1];
   /*printf("Norm %f\n",Norm); */
  /*Normalize all Probability values*/
  if (Norm>0){
    for(idx2=*idxstart;idx2<*idxstop;idx2++){
      Prob[idx2]=Prob[idx2]/Norm;
      /*printf("%d %g \n",idx2,Prob[idx2])*/;
    }
  }
}
/*-----------------------------------------------------------------
Functions for random energy generation
------------------------------------------------------------------*/
double xonly(double x)
{
  return linfuncint(x,xylength,inxvec,inyvec);
}
double Pfunc(double x, double y)
{
  return quadfuncint(x,xylength,inxvec,Pvec)-y;
}
/*----------------------------------------------------------------
Functions for random time generation
------------------------------------------------------------------*/
double txonly(double t)
{
  return linfuncint(t,ntvals,txval,tyval);
}
double tPfunc(double t,double y)
{
  return quadfuncint(t,ntvals,txval,tyval)-y;
}

#line 10183 "SEQ_11_09_2009.c"
#undef Emax
#undef Emin
#undef yh
#undef xw
#undef dist
#undef height
#undef width
#undef p_in
#undef vdiv
#undef hdiv
#undef S_filename
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'core_ves' [3]. */
#define mccompcurname  core_ves
#define mccompcurtype  Channeled_guide
#define mccompcurindex 3
#define w1c mcccore_ves_w1c
#define w2c mcccore_ves_w2c
#define ww mcccore_ves_ww
#define hh mcccore_ves_hh
#define whalf mcccore_ves_whalf
#define hhalf mcccore_ves_hhalf
#define lwhalf mcccore_ves_lwhalf
#define lhhalf mcccore_ves_lhhalf
#define w1 mcccore_ves_w1
#define h1 mcccore_ves_h1
#define w2 mcccore_ves_w2
#define h2 mcccore_ves_h2
#define l mcccore_ves_l
#define R0 mcccore_ves_R0
#define Qcx mcccore_ves_Qcx
#define Qcy mcccore_ves_Qcy
#define alphax mcccore_ves_alphax
#define alphay mcccore_ves_alphay
#define W mcccore_ves_W
#define k mcccore_ves_k
#define d mcccore_ves_d
#define mx mcccore_ves_mx
#define my mcccore_ves_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10232 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'shutter_guide' [4]. */
#define mccompcurname  shutter_guide
#define mccompcurtype  Channeled_guide
#define mccompcurindex 4
#define w1c mccshutter_guide_w1c
#define w2c mccshutter_guide_w2c
#define ww mccshutter_guide_ww
#define hh mccshutter_guide_hh
#define whalf mccshutter_guide_whalf
#define hhalf mccshutter_guide_hhalf
#define lwhalf mccshutter_guide_lwhalf
#define lhhalf mccshutter_guide_lhhalf
#define w1 mccshutter_guide_w1
#define h1 mccshutter_guide_h1
#define w2 mccshutter_guide_w2
#define h2 mccshutter_guide_h2
#define l mccshutter_guide_l
#define R0 mccshutter_guide_R0
#define Qcx mccshutter_guide_Qcx
#define Qcy mccshutter_guide_Qcy
#define alphax mccshutter_guide_alphax
#define alphay mccshutter_guide_alphay
#define W mccshutter_guide_W
#define k mccshutter_guide_k
#define d mccshutter_guide_d
#define mx mccshutter_guide_mx
#define my mccshutter_guide_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10293 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide1' [5]. */
#define mccompcurname  guide1
#define mccompcurtype  Channeled_guide
#define mccompcurindex 5
#define w1c mccguide1_w1c
#define w2c mccguide1_w2c
#define ww mccguide1_ww
#define hh mccguide1_hh
#define whalf mccguide1_whalf
#define hhalf mccguide1_hhalf
#define lwhalf mccguide1_lwhalf
#define lhhalf mccguide1_lhhalf
#define w1 mccguide1_w1
#define h1 mccguide1_h1
#define w2 mccguide1_w2
#define h2 mccguide1_h2
#define l mccguide1_l
#define R0 mccguide1_R0
#define Qcx mccguide1_Qcx
#define Qcy mccguide1_Qcy
#define alphax mccguide1_alphax
#define alphay mccguide1_alphay
#define W mccguide1_W
#define k mccguide1_k
#define d mccguide1_d
#define mx mccguide1_mx
#define my mccguide1_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10354 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide2' [6]. */
#define mccompcurname  guide2
#define mccompcurtype  Channeled_guide
#define mccompcurindex 6
#define w1c mccguide2_w1c
#define w2c mccguide2_w2c
#define ww mccguide2_ww
#define hh mccguide2_hh
#define whalf mccguide2_whalf
#define hhalf mccguide2_hhalf
#define lwhalf mccguide2_lwhalf
#define lhhalf mccguide2_lhhalf
#define w1 mccguide2_w1
#define h1 mccguide2_h1
#define w2 mccguide2_w2
#define h2 mccguide2_h2
#define l mccguide2_l
#define R0 mccguide2_R0
#define Qcx mccguide2_Qcx
#define Qcy mccguide2_Qcy
#define alphax mccguide2_alphax
#define alphay mccguide2_alphay
#define W mccguide2_W
#define k mccguide2_k
#define d mccguide2_d
#define mx mccguide2_mx
#define my mccguide2_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10415 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide3' [7]. */
#define mccompcurname  guide3
#define mccompcurtype  Channeled_guide
#define mccompcurindex 7
#define w1c mccguide3_w1c
#define w2c mccguide3_w2c
#define ww mccguide3_ww
#define hh mccguide3_hh
#define whalf mccguide3_whalf
#define hhalf mccguide3_hhalf
#define lwhalf mccguide3_lwhalf
#define lhhalf mccguide3_lhhalf
#define w1 mccguide3_w1
#define h1 mccguide3_h1
#define w2 mccguide3_w2
#define h2 mccguide3_h2
#define l mccguide3_l
#define R0 mccguide3_R0
#define Qcx mccguide3_Qcx
#define Qcy mccguide3_Qcy
#define alphax mccguide3_alphax
#define alphay mccguide3_alphay
#define W mccguide3_W
#define k mccguide3_k
#define d mccguide3_d
#define mx mccguide3_mx
#define my mccguide3_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10476 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide4' [8]. */
#define mccompcurname  guide4
#define mccompcurtype  Channeled_guide
#define mccompcurindex 8
#define w1c mccguide4_w1c
#define w2c mccguide4_w2c
#define ww mccguide4_ww
#define hh mccguide4_hh
#define whalf mccguide4_whalf
#define hhalf mccguide4_hhalf
#define lwhalf mccguide4_lwhalf
#define lhhalf mccguide4_lhhalf
#define w1 mccguide4_w1
#define h1 mccguide4_h1
#define w2 mccguide4_w2
#define h2 mccguide4_h2
#define l mccguide4_l
#define R0 mccguide4_R0
#define Qcx mccguide4_Qcx
#define Qcy mccguide4_Qcy
#define alphax mccguide4_alphax
#define alphay mccguide4_alphay
#define W mccguide4_W
#define k mccguide4_k
#define d mccguide4_d
#define mx mccguide4_mx
#define my mccguide4_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10537 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide5' [9]. */
#define mccompcurname  guide5
#define mccompcurtype  Channeled_guide
#define mccompcurindex 9
#define w1c mccguide5_w1c
#define w2c mccguide5_w2c
#define ww mccguide5_ww
#define hh mccguide5_hh
#define whalf mccguide5_whalf
#define hhalf mccguide5_hhalf
#define lwhalf mccguide5_lwhalf
#define lhhalf mccguide5_lhhalf
#define w1 mccguide5_w1
#define h1 mccguide5_h1
#define w2 mccguide5_w2
#define h2 mccguide5_h2
#define l mccguide5_l
#define R0 mccguide5_R0
#define Qcx mccguide5_Qcx
#define Qcy mccguide5_Qcy
#define alphax mccguide5_alphax
#define alphay mccguide5_alphay
#define W mccguide5_W
#define k mccguide5_k
#define d mccguide5_d
#define mx mccguide5_mx
#define my mccguide5_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10598 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide6' [10]. */
#define mccompcurname  guide6
#define mccompcurtype  Channeled_guide
#define mccompcurindex 10
#define w1c mccguide6_w1c
#define w2c mccguide6_w2c
#define ww mccguide6_ww
#define hh mccguide6_hh
#define whalf mccguide6_whalf
#define hhalf mccguide6_hhalf
#define lwhalf mccguide6_lwhalf
#define lhhalf mccguide6_lhhalf
#define w1 mccguide6_w1
#define h1 mccguide6_h1
#define w2 mccguide6_w2
#define h2 mccguide6_h2
#define l mccguide6_l
#define R0 mccguide6_R0
#define Qcx mccguide6_Qcx
#define Qcy mccguide6_Qcy
#define alphax mccguide6_alphax
#define alphay mccguide6_alphay
#define W mccguide6_W
#define k mccguide6_k
#define d mccguide6_d
#define mx mccguide6_mx
#define my mccguide6_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10659 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide7' [11]. */
#define mccompcurname  guide7
#define mccompcurtype  Channeled_guide
#define mccompcurindex 11
#define w1c mccguide7_w1c
#define w2c mccguide7_w2c
#define ww mccguide7_ww
#define hh mccguide7_hh
#define whalf mccguide7_whalf
#define hhalf mccguide7_hhalf
#define lwhalf mccguide7_lwhalf
#define lhhalf mccguide7_lhhalf
#define w1 mccguide7_w1
#define h1 mccguide7_h1
#define w2 mccguide7_w2
#define h2 mccguide7_h2
#define l mccguide7_l
#define R0 mccguide7_R0
#define Qcx mccguide7_Qcx
#define Qcy mccguide7_Qcy
#define alphax mccguide7_alphax
#define alphay mccguide7_alphay
#define W mccguide7_W
#define k mccguide7_k
#define d mccguide7_d
#define mx mccguide7_mx
#define my mccguide7_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10720 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide8' [12]. */
#define mccompcurname  guide8
#define mccompcurtype  Channeled_guide
#define mccompcurindex 12
#define w1c mccguide8_w1c
#define w2c mccguide8_w2c
#define ww mccguide8_ww
#define hh mccguide8_hh
#define whalf mccguide8_whalf
#define hhalf mccguide8_hhalf
#define lwhalf mccguide8_lwhalf
#define lhhalf mccguide8_lhhalf
#define w1 mccguide8_w1
#define h1 mccguide8_h1
#define w2 mccguide8_w2
#define h2 mccguide8_h2
#define l mccguide8_l
#define R0 mccguide8_R0
#define Qcx mccguide8_Qcx
#define Qcy mccguide8_Qcy
#define alphax mccguide8_alphax
#define alphay mccguide8_alphay
#define W mccguide8_W
#define k mccguide8_k
#define d mccguide8_d
#define mx mccguide8_mx
#define my mccguide8_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10781 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide9' [13]. */
#define mccompcurname  guide9
#define mccompcurtype  Channeled_guide
#define mccompcurindex 13
#define w1c mccguide9_w1c
#define w2c mccguide9_w2c
#define ww mccguide9_ww
#define hh mccguide9_hh
#define whalf mccguide9_whalf
#define hhalf mccguide9_hhalf
#define lwhalf mccguide9_lwhalf
#define lhhalf mccguide9_lhhalf
#define w1 mccguide9_w1
#define h1 mccguide9_h1
#define w2 mccguide9_w2
#define h2 mccguide9_h2
#define l mccguide9_l
#define R0 mccguide9_R0
#define Qcx mccguide9_Qcx
#define Qcy mccguide9_Qcy
#define alphax mccguide9_alphax
#define alphay mccguide9_alphay
#define W mccguide9_W
#define k mccguide9_k
#define d mccguide9_d
#define mx mccguide9_mx
#define my mccguide9_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10842 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide10' [14]. */
#define mccompcurname  guide10
#define mccompcurtype  Channeled_guide
#define mccompcurindex 14
#define w1c mccguide10_w1c
#define w2c mccguide10_w2c
#define ww mccguide10_ww
#define hh mccguide10_hh
#define whalf mccguide10_whalf
#define hhalf mccguide10_hhalf
#define lwhalf mccguide10_lwhalf
#define lhhalf mccguide10_lhhalf
#define w1 mccguide10_w1
#define h1 mccguide10_h1
#define w2 mccguide10_w2
#define h2 mccguide10_h2
#define l mccguide10_l
#define R0 mccguide10_R0
#define Qcx mccguide10_Qcx
#define Qcy mccguide10_Qcy
#define alphax mccguide10_alphax
#define alphay mccguide10_alphay
#define W mccguide10_W
#define k mccguide10_k
#define d mccguide10_d
#define mx mccguide10_mx
#define my mccguide10_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10903 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide11' [15]. */
#define mccompcurname  guide11
#define mccompcurtype  Channeled_guide
#define mccompcurindex 15
#define w1c mccguide11_w1c
#define w2c mccguide11_w2c
#define ww mccguide11_ww
#define hh mccguide11_hh
#define whalf mccguide11_whalf
#define hhalf mccguide11_hhalf
#define lwhalf mccguide11_lwhalf
#define lhhalf mccguide11_lhhalf
#define w1 mccguide11_w1
#define h1 mccguide11_h1
#define w2 mccguide11_w2
#define h2 mccguide11_h2
#define l mccguide11_l
#define R0 mccguide11_R0
#define Qcx mccguide11_Qcx
#define Qcy mccguide11_Qcy
#define alphax mccguide11_alphax
#define alphay mccguide11_alphay
#define W mccguide11_W
#define k mccguide11_k
#define d mccguide11_d
#define mx mccguide11_mx
#define my mccguide11_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 10964 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 't0_chopp' [16]. */
#define mccompcurname  t0_chopp
#define mccompcurtype  Vertical_T0a
#define mccompcurindex 16
#define len mcct0_chopp_len
#define w1 mcct0_chopp_w1
#define w2 mcct0_chopp_w2
#define nu mcct0_chopp_nu
#define delta mcct0_chopp_delta
#define tc mcct0_chopp_tc
#define ymin mcct0_chopp_ymin
#define ymax mcct0_chopp_ymax
#define omega mcct0_chopp_omega
#define r_blade mcct0_chopp_r_blade
#define x_width mcct0_chopp_x_width
#define nn mcct0_chopp_nn
#define tdr mcct0_chopp_tdr
#line 67 "Vertical_T0a.comp"

   double omega,off,splen,rad,sw;
    /* function to calculate if the neutron is in the channel or not 
     * return 0 if neutron does not transmit return 1  if neutron will pass*/
    int t0checkabsorb(double phi, double inrad,double inw1, double inw2, double c[]){
     double xtmp,neuzr,neuxr;
     neutxypos(&neuzr,&neuxr,phi,inrad,c);
  // printf("xr:%g zr:%g phi: %g r: %g c[0]: %g c[1]: %g\n",neuxr,neuzr,phi,inrad,c[0],c[1]);
        if (fabs(neuxr)>inw1/2.0+(inw2-inw1)/(inrad/2.0)*fabs(neuzr)) // check if neutron x position is outside of channel 
         return 0;    
     return 1;
    }
  
#line 11023 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w2
#undef w1
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 't_check1' [17]. */
#define mccompcurname  t_check1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 17
#define nchan mcct_check1_nchan
#define TOF_N mcct_check1_TOF_N
#define TOF_p mcct_check1_TOF_p
#define TOF_p2 mcct_check1_TOF_p2
#define xmin mcct_check1_xmin
#define xmax mcct_check1_xmax
#define ymin mcct_check1_ymin
#define ymax mcct_check1_ymax
#define tmin mcct_check1_tmin
#define tmax mcct_check1_tmax
#define filename mcct_check1_filename
#line 44 "TOF_monitor2.comp"
    double TOF_N[nchan];
    double TOF_p[nchan];
    double TOF_p2[nchan];
#line 11060 "SEQ_11_09_2009.c"
#undef filename
#undef tmax
#undef tmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide13' [18]. */
#define mccompcurname  guide13
#define mccompcurtype  Channeled_guide
#define mccompcurindex 18
#define w1c mccguide13_w1c
#define w2c mccguide13_w2c
#define ww mccguide13_ww
#define hh mccguide13_hh
#define whalf mccguide13_whalf
#define hhalf mccguide13_hhalf
#define lwhalf mccguide13_lwhalf
#define lhhalf mccguide13_lhhalf
#define w1 mccguide13_w1
#define h1 mccguide13_h1
#define w2 mccguide13_w2
#define h2 mccguide13_h2
#define l mccguide13_l
#define R0 mccguide13_R0
#define Qcx mccguide13_Qcx
#define Qcy mccguide13_Qcy
#define alphax mccguide13_alphax
#define alphay mccguide13_alphay
#define W mccguide13_W
#define k mccguide13_k
#define d mccguide13_d
#define mx mccguide13_mx
#define my mccguide13_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11109 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide14' [19]. */
#define mccompcurname  guide14
#define mccompcurtype  Channeled_guide
#define mccompcurindex 19
#define w1c mccguide14_w1c
#define w2c mccguide14_w2c
#define ww mccguide14_ww
#define hh mccguide14_hh
#define whalf mccguide14_whalf
#define hhalf mccguide14_hhalf
#define lwhalf mccguide14_lwhalf
#define lhhalf mccguide14_lhhalf
#define w1 mccguide14_w1
#define h1 mccguide14_h1
#define w2 mccguide14_w2
#define h2 mccguide14_h2
#define l mccguide14_l
#define R0 mccguide14_R0
#define Qcx mccguide14_Qcx
#define Qcy mccguide14_Qcy
#define alphax mccguide14_alphax
#define alphay mccguide14_alphay
#define W mccguide14_W
#define k mccguide14_k
#define d mccguide14_d
#define mx mccguide14_mx
#define my mccguide14_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11170 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide15' [20]. */
#define mccompcurname  guide15
#define mccompcurtype  Channeled_guide
#define mccompcurindex 20
#define w1c mccguide15_w1c
#define w2c mccguide15_w2c
#define ww mccguide15_ww
#define hh mccguide15_hh
#define whalf mccguide15_whalf
#define hhalf mccguide15_hhalf
#define lwhalf mccguide15_lwhalf
#define lhhalf mccguide15_lhhalf
#define w1 mccguide15_w1
#define h1 mccguide15_h1
#define w2 mccguide15_w2
#define h2 mccguide15_h2
#define l mccguide15_l
#define R0 mccguide15_R0
#define Qcx mccguide15_Qcx
#define Qcy mccguide15_Qcy
#define alphax mccguide15_alphax
#define alphay mccguide15_alphay
#define W mccguide15_W
#define k mccguide15_k
#define d mccguide15_d
#define mx mccguide15_mx
#define my mccguide15_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11231 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide16' [21]. */
#define mccompcurname  guide16
#define mccompcurtype  Channeled_guide
#define mccompcurindex 21
#define w1c mccguide16_w1c
#define w2c mccguide16_w2c
#define ww mccguide16_ww
#define hh mccguide16_hh
#define whalf mccguide16_whalf
#define hhalf mccguide16_hhalf
#define lwhalf mccguide16_lwhalf
#define lhhalf mccguide16_lhhalf
#define w1 mccguide16_w1
#define h1 mccguide16_h1
#define w2 mccguide16_w2
#define h2 mccguide16_h2
#define l mccguide16_l
#define R0 mccguide16_R0
#define Qcx mccguide16_Qcx
#define Qcy mccguide16_Qcy
#define alphax mccguide16_alphax
#define alphay mccguide16_alphay
#define W mccguide16_W
#define k mccguide16_k
#define d mccguide16_d
#define mx mccguide16_mx
#define my mccguide16_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11292 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide17' [22]. */
#define mccompcurname  guide17
#define mccompcurtype  Channeled_guide
#define mccompcurindex 22
#define w1c mccguide17_w1c
#define w2c mccguide17_w2c
#define ww mccguide17_ww
#define hh mccguide17_hh
#define whalf mccguide17_whalf
#define hhalf mccguide17_hhalf
#define lwhalf mccguide17_lwhalf
#define lhhalf mccguide17_lhhalf
#define w1 mccguide17_w1
#define h1 mccguide17_h1
#define w2 mccguide17_w2
#define h2 mccguide17_h2
#define l mccguide17_l
#define R0 mccguide17_R0
#define Qcx mccguide17_Qcx
#define Qcy mccguide17_Qcy
#define alphax mccguide17_alphax
#define alphay mccguide17_alphay
#define W mccguide17_W
#define k mccguide17_k
#define d mccguide17_d
#define mx mccguide17_mx
#define my mccguide17_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11353 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide18' [23]. */
#define mccompcurname  guide18
#define mccompcurtype  Channeled_guide
#define mccompcurindex 23
#define w1c mccguide18_w1c
#define w2c mccguide18_w2c
#define ww mccguide18_ww
#define hh mccguide18_hh
#define whalf mccguide18_whalf
#define hhalf mccguide18_hhalf
#define lwhalf mccguide18_lwhalf
#define lhhalf mccguide18_lhhalf
#define w1 mccguide18_w1
#define h1 mccguide18_h1
#define w2 mccguide18_w2
#define h2 mccguide18_h2
#define l mccguide18_l
#define R0 mccguide18_R0
#define Qcx mccguide18_Qcx
#define Qcy mccguide18_Qcy
#define alphax mccguide18_alphax
#define alphay mccguide18_alphay
#define W mccguide18_W
#define k mccguide18_k
#define d mccguide18_d
#define mx mccguide18_mx
#define my mccguide18_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11414 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide19' [24]. */
#define mccompcurname  guide19
#define mccompcurtype  Channeled_guide
#define mccompcurindex 24
#define w1c mccguide19_w1c
#define w2c mccguide19_w2c
#define ww mccguide19_ww
#define hh mccguide19_hh
#define whalf mccguide19_whalf
#define hhalf mccguide19_hhalf
#define lwhalf mccguide19_lwhalf
#define lhhalf mccguide19_lhhalf
#define w1 mccguide19_w1
#define h1 mccguide19_h1
#define w2 mccguide19_w2
#define h2 mccguide19_h2
#define l mccguide19_l
#define R0 mccguide19_R0
#define Qcx mccguide19_Qcx
#define Qcy mccguide19_Qcy
#define alphax mccguide19_alphax
#define alphay mccguide19_alphay
#define W mccguide19_W
#define k mccguide19_k
#define d mccguide19_d
#define mx mccguide19_mx
#define my mccguide19_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11475 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide20' [25]. */
#define mccompcurname  guide20
#define mccompcurtype  Channeled_guide
#define mccompcurindex 25
#define w1c mccguide20_w1c
#define w2c mccguide20_w2c
#define ww mccguide20_ww
#define hh mccguide20_hh
#define whalf mccguide20_whalf
#define hhalf mccguide20_hhalf
#define lwhalf mccguide20_lwhalf
#define lhhalf mccguide20_lhhalf
#define w1 mccguide20_w1
#define h1 mccguide20_h1
#define w2 mccguide20_w2
#define h2 mccguide20_h2
#define l mccguide20_l
#define R0 mccguide20_R0
#define Qcx mccguide20_Qcx
#define Qcy mccguide20_Qcy
#define alphax mccguide20_alphax
#define alphay mccguide20_alphay
#define W mccguide20_W
#define k mccguide20_k
#define d mccguide20_d
#define mx mccguide20_mx
#define my mccguide20_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11536 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide21' [26]. */
#define mccompcurname  guide21
#define mccompcurtype  Channeled_guide
#define mccompcurindex 26
#define w1c mccguide21_w1c
#define w2c mccguide21_w2c
#define ww mccguide21_ww
#define hh mccguide21_hh
#define whalf mccguide21_whalf
#define hhalf mccguide21_hhalf
#define lwhalf mccguide21_lwhalf
#define lhhalf mccguide21_lhhalf
#define w1 mccguide21_w1
#define h1 mccguide21_h1
#define w2 mccguide21_w2
#define h2 mccguide21_h2
#define l mccguide21_l
#define R0 mccguide21_R0
#define Qcx mccguide21_Qcx
#define Qcy mccguide21_Qcy
#define alphax mccguide21_alphax
#define alphay mccguide21_alphay
#define W mccguide21_W
#define k mccguide21_k
#define d mccguide21_d
#define mx mccguide21_mx
#define my mccguide21_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11597 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide22' [27]. */
#define mccompcurname  guide22
#define mccompcurtype  Channeled_guide
#define mccompcurindex 27
#define w1c mccguide22_w1c
#define w2c mccguide22_w2c
#define ww mccguide22_ww
#define hh mccguide22_hh
#define whalf mccguide22_whalf
#define hhalf mccguide22_hhalf
#define lwhalf mccguide22_lwhalf
#define lhhalf mccguide22_lhhalf
#define w1 mccguide22_w1
#define h1 mccguide22_h1
#define w2 mccguide22_w2
#define h2 mccguide22_h2
#define l mccguide22_l
#define R0 mccguide22_R0
#define Qcx mccguide22_Qcx
#define Qcy mccguide22_Qcy
#define alphax mccguide22_alphax
#define alphay mccguide22_alphay
#define W mccguide22_W
#define k mccguide22_k
#define d mccguide22_d
#define mx mccguide22_mx
#define my mccguide22_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11658 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide23' [28]. */
#define mccompcurname  guide23
#define mccompcurtype  Channeled_guide
#define mccompcurindex 28
#define w1c mccguide23_w1c
#define w2c mccguide23_w2c
#define ww mccguide23_ww
#define hh mccguide23_hh
#define whalf mccguide23_whalf
#define hhalf mccguide23_hhalf
#define lwhalf mccguide23_lwhalf
#define lhhalf mccguide23_lhhalf
#define w1 mccguide23_w1
#define h1 mccguide23_h1
#define w2 mccguide23_w2
#define h2 mccguide23_h2
#define l mccguide23_l
#define R0 mccguide23_R0
#define Qcx mccguide23_Qcx
#define Qcy mccguide23_Qcy
#define alphax mccguide23_alphax
#define alphay mccguide23_alphay
#define W mccguide23_W
#define k mccguide23_k
#define d mccguide23_d
#define mx mccguide23_mx
#define my mccguide23_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11719 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide24' [29]. */
#define mccompcurname  guide24
#define mccompcurtype  Channeled_guide
#define mccompcurindex 29
#define w1c mccguide24_w1c
#define w2c mccguide24_w2c
#define ww mccguide24_ww
#define hh mccguide24_hh
#define whalf mccguide24_whalf
#define hhalf mccguide24_hhalf
#define lwhalf mccguide24_lwhalf
#define lhhalf mccguide24_lhhalf
#define w1 mccguide24_w1
#define h1 mccguide24_h1
#define w2 mccguide24_w2
#define h2 mccguide24_h2
#define l mccguide24_l
#define R0 mccguide24_R0
#define Qcx mccguide24_Qcx
#define Qcy mccguide24_Qcy
#define alphax mccguide24_alphax
#define alphay mccguide24_alphay
#define W mccguide24_W
#define k mccguide24_k
#define d mccguide24_d
#define mx mccguide24_mx
#define my mccguide24_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11780 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide25' [30]. */
#define mccompcurname  guide25
#define mccompcurtype  Channeled_guide
#define mccompcurindex 30
#define w1c mccguide25_w1c
#define w2c mccguide25_w2c
#define ww mccguide25_ww
#define hh mccguide25_hh
#define whalf mccguide25_whalf
#define hhalf mccguide25_hhalf
#define lwhalf mccguide25_lwhalf
#define lhhalf mccguide25_lhhalf
#define w1 mccguide25_w1
#define h1 mccguide25_h1
#define w2 mccguide25_w2
#define h2 mccguide25_h2
#define l mccguide25_l
#define R0 mccguide25_R0
#define Qcx mccguide25_Qcx
#define Qcy mccguide25_Qcy
#define alphax mccguide25_alphax
#define alphay mccguide25_alphay
#define W mccguide25_W
#define k mccguide25_k
#define d mccguide25_d
#define mx mccguide25_mx
#define my mccguide25_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11841 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide26' [31]. */
#define mccompcurname  guide26
#define mccompcurtype  Channeled_guide
#define mccompcurindex 31
#define w1c mccguide26_w1c
#define w2c mccguide26_w2c
#define ww mccguide26_ww
#define hh mccguide26_hh
#define whalf mccguide26_whalf
#define hhalf mccguide26_hhalf
#define lwhalf mccguide26_lwhalf
#define lhhalf mccguide26_lhhalf
#define w1 mccguide26_w1
#define h1 mccguide26_h1
#define w2 mccguide26_w2
#define h2 mccguide26_h2
#define l mccguide26_l
#define R0 mccguide26_R0
#define Qcx mccguide26_Qcx
#define Qcy mccguide26_Qcy
#define alphax mccguide26_alphax
#define alphay mccguide26_alphay
#define W mccguide26_W
#define k mccguide26_k
#define d mccguide26_d
#define mx mccguide26_mx
#define my mccguide26_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11902 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide27' [32]. */
#define mccompcurname  guide27
#define mccompcurtype  Channeled_guide
#define mccompcurindex 32
#define w1c mccguide27_w1c
#define w2c mccguide27_w2c
#define ww mccguide27_ww
#define hh mccguide27_hh
#define whalf mccguide27_whalf
#define hhalf mccguide27_hhalf
#define lwhalf mccguide27_lwhalf
#define lhhalf mccguide27_lhhalf
#define w1 mccguide27_w1
#define h1 mccguide27_h1
#define w2 mccguide27_w2
#define h2 mccguide27_h2
#define l mccguide27_l
#define R0 mccguide27_R0
#define Qcx mccguide27_Qcx
#define Qcy mccguide27_Qcy
#define alphax mccguide27_alphax
#define alphay mccguide27_alphay
#define W mccguide27_W
#define k mccguide27_k
#define d mccguide27_d
#define mx mccguide27_mx
#define my mccguide27_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 11963 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'fermi_chopp' [33]. */
#define mccompcurname  fermi_chopp
#define mccompcurtype  Fermi_chop2a
#define mccompcurindex 33
#define len mccfermi_chopp_len
#define w mccfermi_chopp_w
#define nu mccfermi_chopp_nu
#define delta mccfermi_chopp_delta
#define tc mccfermi_chopp_tc
#define ymin mccfermi_chopp_ymin
#define ymax mccfermi_chopp_ymax
#define nchan mccfermi_chopp_nchan
#define bw mccfermi_chopp_bw
#define blader mccfermi_chopp_blader
#define omega mccfermi_chopp_omega
#define r_blade mccfermi_chopp_r_blade
#define x_width mccfermi_chopp_x_width
#define nn mccfermi_chopp_nn
#define tdr mccfermi_chopp_tdr
#line 71 "Fermi_chop2a.comp"

    double omega,off,splen,rad,sw,tw;
    /* function that describes the shape of the blades */
    double blades(double zin,double rin,double off){
        if (rin!=0.0)
     	  return rin*(1-cos(asin(zin/fabs(rin))))+off;
        else
       	  return 0;
    }
    /* function to calculate which channel the neturon is in and to check if it is in a blade 
     *  or outside the slit package 
     * return 0 if neutron does not transmit return 1 with channel number if neutron will pass*/
    int checkabsorb(double phi,int *chan_num, double inrad,double inw, double insw, double inbw, double c[]){
     double xtmp,neuzr,neuxr;
     neutxypos(&neuzr,&neuxr,phi,inrad,c);
  // printf("xr:%g zr:%g phi: %g r: %g c[0]: %g c[1]: %g\n",neuxr,neuzr,phi,inrad,c[0],c[1]);
     if (fabs(neuxr)>inw/2.0) // check if neutron x position is outside of slit package
         return 0;
     xtmp=neuxr+inw/2.0;  // move origin to side of slit package 
     *chan_num=ceil((xtmp-blades(neuzr,blader,off))/(inbw+insw)); //calculate channel number
      //check if neutron is in blade 
     if (xtmp >*chan_num*(inbw+insw)+blades(neuzr,blader,off))
         return 0;
     return 1;
    }
  
#line 12037 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef blader
#undef bw
#undef nchan
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'adjustable_slits' [34]. */
#define mccompcurname  adjustable_slits
#define mccompcurtype  Slit
#define mccompcurindex 34
#define xmin mccadjustable_slits_xmin
#define xmax mccadjustable_slits_xmax
#define ymin mccadjustable_slits_ymin
#define ymax mccadjustable_slits_ymax
#define radius mccadjustable_slits_radius
#define cut mccadjustable_slits_cut
#define width mccadjustable_slits_width
#define height mccadjustable_slits_height
#undef height
#undef width
#undef cut
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'Monitor1' [35]. */
#define mccompcurname  Monitor1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 35
#define nchan mccMonitor1_nchan
#define TOF_N mccMonitor1_TOF_N
#define TOF_p mccMonitor1_TOF_p
#define TOF_p2 mccMonitor1_TOF_p2
#define xmin mccMonitor1_xmin
#define xmax mccMonitor1_xmax
#define ymin mccMonitor1_ymin
#define ymax mccMonitor1_ymax
#define tmin mccMonitor1_tmin
#define tmax mccMonitor1_tmax
#define filename mccMonitor1_filename
#line 44 "TOF_monitor2.comp"
    double TOF_N[nchan];
    double TOF_p[nchan];
    double TOF_p2[nchan];
#line 12100 "SEQ_11_09_2009.c"
#undef filename
#undef tmax
#undef tmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide29' [36]. */
#define mccompcurname  guide29
#define mccompcurtype  Channeled_guide
#define mccompcurindex 36
#define w1c mccguide29_w1c
#define w2c mccguide29_w2c
#define ww mccguide29_ww
#define hh mccguide29_hh
#define whalf mccguide29_whalf
#define hhalf mccguide29_hhalf
#define lwhalf mccguide29_lwhalf
#define lhhalf mccguide29_lhhalf
#define w1 mccguide29_w1
#define h1 mccguide29_h1
#define w2 mccguide29_w2
#define h2 mccguide29_h2
#define l mccguide29_l
#define R0 mccguide29_R0
#define Qcx mccguide29_Qcx
#define Qcy mccguide29_Qcy
#define alphax mccguide29_alphax
#define alphay mccguide29_alphay
#define W mccguide29_W
#define k mccguide29_k
#define d mccguide29_d
#define mx mccguide29_mx
#define my mccguide29_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 12149 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide31' [37]. */
#define mccompcurname  guide31
#define mccompcurtype  Channeled_guide
#define mccompcurindex 37
#define w1c mccguide31_w1c
#define w2c mccguide31_w2c
#define ww mccguide31_ww
#define hh mccguide31_hh
#define whalf mccguide31_whalf
#define hhalf mccguide31_hhalf
#define lwhalf mccguide31_lwhalf
#define lhhalf mccguide31_lhhalf
#define w1 mccguide31_w1
#define h1 mccguide31_h1
#define w2 mccguide31_w2
#define h2 mccguide31_h2
#define l mccguide31_l
#define R0 mccguide31_R0
#define Qcx mccguide31_Qcx
#define Qcy mccguide31_Qcy
#define alphax mccguide31_alphax
#define alphay mccguide31_alphay
#define W mccguide31_W
#define k mccguide31_k
#define d mccguide31_d
#define mx mccguide31_mx
#define my mccguide31_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 12210 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide32' [38]. */
#define mccompcurname  guide32
#define mccompcurtype  Channeled_guide
#define mccompcurindex 38
#define w1c mccguide32_w1c
#define w2c mccguide32_w2c
#define ww mccguide32_ww
#define hh mccguide32_hh
#define whalf mccguide32_whalf
#define hhalf mccguide32_hhalf
#define lwhalf mccguide32_lwhalf
#define lhhalf mccguide32_lhhalf
#define w1 mccguide32_w1
#define h1 mccguide32_h1
#define w2 mccguide32_w2
#define h2 mccguide32_h2
#define l mccguide32_l
#define R0 mccguide32_R0
#define Qcx mccguide32_Qcx
#define Qcy mccguide32_Qcy
#define alphax mccguide32_alphax
#define alphay mccguide32_alphay
#define W mccguide32_W
#define k mccguide32_k
#define d mccguide32_d
#define mx mccguide32_mx
#define my mccguide32_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 12271 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'guide34' [39]. */
#define mccompcurname  guide34
#define mccompcurtype  Channeled_guide
#define mccompcurindex 39
#define w1c mccguide34_w1c
#define w2c mccguide34_w2c
#define ww mccguide34_ww
#define hh mccguide34_hh
#define whalf mccguide34_whalf
#define hhalf mccguide34_hhalf
#define lwhalf mccguide34_lwhalf
#define lhhalf mccguide34_lhhalf
#define w1 mccguide34_w1
#define h1 mccguide34_h1
#define w2 mccguide34_w2
#define h2 mccguide34_h2
#define l mccguide34_l
#define R0 mccguide34_R0
#define Qcx mccguide34_Qcx
#define Qcy mccguide34_Qcy
#define alphax mccguide34_alphax
#define alphay mccguide34_alphay
#define W mccguide34_W
#define k mccguide34_k
#define d mccguide34_d
#define mx mccguide34_mx
#define my mccguide34_my
#line 67 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
  double w1c;
  double w2c;
  double ww, hh;
  double whalf, hhalf;
  double lwhalf, lhhalf;
#line 12332 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'E_det' [40]. */
#define mccompcurname  E_det
#define mccompcurtype  E_monitor
#define mccompcurindex 40
#define nchan mccE_det_nchan
#define filename mccE_det_filename
#define restore_neutron mccE_det_restore_neutron
#define E_N mccE_det_E_N
#define E_p mccE_det_E_p
#define E_p2 mccE_det_E_p2
#define S_p mccE_det_S_p
#define S_pE mccE_det_S_pE
#define S_pE2 mccE_det_S_pE2
#define xmin mccE_det_xmin
#define xmax mccE_det_xmax
#define ymin mccE_det_ymin
#define ymax mccE_det_ymax
#define xwidth mccE_det_xwidth
#define yheight mccE_det_yheight
#define Emin mccE_det_Emin
#define Emax mccE_det_Emax
#line 60 "/usr/local/lib/mcstas/monitors/E_monitor.comp"
    double E_N[nchan];
    double E_p[nchan], E_p2[nchan];
    double S_p, S_pE, S_pE2;
#line 12385 "SEQ_11_09_2009.c"
#undef Emax
#undef Emin
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef restore_neutron
#undef filename
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'Sample_Arm' [41]. */
#define mccompcurname  Sample_Arm
#define mccompcurtype  Arm
#define mccompcurindex 41
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 'sample' [42]. */
#define mccompcurname  sample
#define mccompcurtype  V_sample
#define mccompcurindex 42
#define StructVarsV mccsample_StructVarsV
#define VarsV mccsample_VarsV
#define radius_i mccsample_radius_i
#define radius_o mccsample_radius_o
#define h mccsample_h
#define focus_r mccsample_focus_r
#define pack mccsample_pack
#define frac mccsample_frac
#define f_QE mccsample_f_QE
#define gamma mccsample_gamma
#define target_x mccsample_target_x
#define target_y mccsample_target_y
#define target_z mccsample_target_z
#define focus_xw mccsample_focus_xw
#define focus_yh mccsample_focus_yh
#define focus_aw mccsample_focus_aw
#define focus_ah mccsample_focus_ah
#define xwidth mccsample_xwidth
#define yheight mccsample_yheight
#define zthick mccsample_zthick
#define rad_sphere mccsample_rad_sphere
#define sig_a mccsample_sig_a
#define sig_i mccsample_sig_i
#define V0 mccsample_V0
#define target_index mccsample_target_index
#define multiples mccsample_multiples
#line 103 "/usr/local/lib/mcstas/samples/V_sample.comp"
  struct StructVarsV
  {
    double  sigma_a; /* Absorption cross section per atom (barns) */
    double  sigma_i; /* Incoherent scattering cross section per atom (barns) */
    double  rho;     /* Density of atoms (AA-3) */
    double  my_s;
    double  my_a_v;
    int     shapetyp;    /* 0 double well cylynder, 1 box,  3 sphere */
    double  distance;    /* when non zero, gives rect target distance */
    double  aw,ah;       /* rectangular angular dimensions */
    double  xw,yh;       /* rectangular metrical dimensions */
    double  tx,ty,tz;    /* target coords */
    } VarsV;
#line 12459 "SEQ_11_09_2009.c"
#undef multiples
#undef target_index
#undef V0
#undef sig_i
#undef sig_a
#undef rad_sphere
#undef zthick
#undef yheight
#undef xwidth
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef target_z
#undef target_y
#undef target_x
#undef gamma
#undef f_QE
#undef frac
#undef pack
#undef focus_r
#undef h
#undef radius_o
#undef radius_i
#undef VarsV
#undef StructVarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 't_mon_detC' [43]. */
#define mccompcurname  t_mon_detC
#define mccompcurtype  Monitor_nD
#define mccompcurindex 43
#define options mcct_mon_detC_options
#define filename mcct_mon_detC_filename
#define user1 mcct_mon_detC_user1
#define user2 mcct_mon_detC_user2
#define user3 mcct_mon_detC_user3
#define username1 mcct_mon_detC_username1
#define username2 mcct_mon_detC_username2
#define username3 mcct_mon_detC_username3
#define DEFS mcct_mon_detC_DEFS
#define Vars mcct_mon_detC_Vars
#define xwidth mcct_mon_detC_xwidth
#define yheight mcct_mon_detC_yheight
#define zthick mcct_mon_detC_zthick
#define xmin mcct_mon_detC_xmin
#define xmax mcct_mon_detC_xmax
#define ymin mcct_mon_detC_ymin
#define ymax mcct_mon_detC_ymax
#define zmin mcct_mon_detC_zmin
#define zmax mcct_mon_detC_zmax
#define bins mcct_mon_detC_bins
#define min mcct_mon_detC_min
#define max mcct_mon_detC_max
#define restore_neutron mcct_mon_detC_restore_neutron
#line 220 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
  MonitornD_Defines_type DEFS;
  MonitornD_Variables_type Vars;
#line 12520 "SEQ_11_09_2009.c"
#undef restore_neutron
#undef max
#undef min
#undef bins
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef zthick
#undef yheight
#undef xwidth
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 't_mon_detB' [44]. */
#define mccompcurname  t_mon_detB
#define mccompcurtype  Monitor_nD
#define mccompcurindex 44
#define options mcct_mon_detB_options
#define filename mcct_mon_detB_filename
#define user1 mcct_mon_detB_user1
#define user2 mcct_mon_detB_user2
#define user3 mcct_mon_detB_user3
#define username1 mcct_mon_detB_username1
#define username2 mcct_mon_detB_username2
#define username3 mcct_mon_detB_username3
#define DEFS mcct_mon_detB_DEFS
#define Vars mcct_mon_detB_Vars
#define xwidth mcct_mon_detB_xwidth
#define yheight mcct_mon_detB_yheight
#define zthick mcct_mon_detB_zthick
#define xmin mcct_mon_detB_xmin
#define xmax mcct_mon_detB_xmax
#define ymin mcct_mon_detB_ymin
#define ymax mcct_mon_detB_ymax
#define zmin mcct_mon_detB_zmin
#define zmax mcct_mon_detB_zmax
#define bins mcct_mon_detB_bins
#define min mcct_mon_detB_min
#define max mcct_mon_detB_max
#define restore_neutron mcct_mon_detB_restore_neutron
#line 220 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
  MonitornD_Defines_type DEFS;
  MonitornD_Variables_type Vars;
#line 12578 "SEQ_11_09_2009.c"
#undef restore_neutron
#undef max
#undef min
#undef bins
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef zthick
#undef yheight
#undef xwidth
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 't_mon_detD' [45]. */
#define mccompcurname  t_mon_detD
#define mccompcurtype  Monitor_nD
#define mccompcurindex 45
#define options mcct_mon_detD_options
#define filename mcct_mon_detD_filename
#define user1 mcct_mon_detD_user1
#define user2 mcct_mon_detD_user2
#define user3 mcct_mon_detD_user3
#define username1 mcct_mon_detD_username1
#define username2 mcct_mon_detD_username2
#define username3 mcct_mon_detD_username3
#define DEFS mcct_mon_detD_DEFS
#define Vars mcct_mon_detD_Vars
#define xwidth mcct_mon_detD_xwidth
#define yheight mcct_mon_detD_yheight
#define zthick mcct_mon_detD_zthick
#define xmin mcct_mon_detD_xmin
#define xmax mcct_mon_detD_xmax
#define ymin mcct_mon_detD_ymin
#define ymax mcct_mon_detD_ymax
#define zmin mcct_mon_detD_zmin
#define zmax mcct_mon_detD_zmax
#define bins mcct_mon_detD_bins
#define min mcct_mon_detD_min
#define max mcct_mon_detD_max
#define restore_neutron mcct_mon_detD_restore_neutron
#line 220 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
  MonitornD_Defines_type DEFS;
  MonitornD_Variables_type Vars;
#line 12636 "SEQ_11_09_2009.c"
#undef restore_neutron
#undef max
#undef min
#undef bins
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef zthick
#undef yheight
#undef xwidth
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

/* User declarations for component 't_mon2' [46]. */
#define mccompcurname  t_mon2
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 46
#define nchan mcct_mon2_nchan
#define TOF_N mcct_mon2_TOF_N
#define TOF_p mcct_mon2_TOF_p
#define TOF_p2 mcct_mon2_TOF_p2
#define xmin mcct_mon2_xmin
#define xmax mcct_mon2_xmax
#define ymin mcct_mon2_ymin
#define ymax mcct_mon2_ymax
#define tmin mcct_mon2_tmin
#define tmax mcct_mon2_tmax
#define filename mcct_mon2_filename
#line 44 "TOF_monitor2.comp"
    double TOF_N[nchan];
    double TOF_p[nchan];
    double TOF_p2[nchan];
#line 12683 "SEQ_11_09_2009.c"
#undef filename
#undef tmax
#undef tmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

Coords mcposaarm1, mcposrarm1;
Rotation mcrotaarm1, mcrotrarm1;
Coords mcposamod, mcposrmod;
Rotation mcrotamod, mcrotrmod;
Coords mcposacore_ves, mcposrcore_ves;
Rotation mcrotacore_ves, mcrotrcore_ves;
Coords mcposashutter_guide, mcposrshutter_guide;
Rotation mcrotashutter_guide, mcrotrshutter_guide;
Coords mcposaguide1, mcposrguide1;
Rotation mcrotaguide1, mcrotrguide1;
Coords mcposaguide2, mcposrguide2;
Rotation mcrotaguide2, mcrotrguide2;
Coords mcposaguide3, mcposrguide3;
Rotation mcrotaguide3, mcrotrguide3;
Coords mcposaguide4, mcposrguide4;
Rotation mcrotaguide4, mcrotrguide4;
Coords mcposaguide5, mcposrguide5;
Rotation mcrotaguide5, mcrotrguide5;
Coords mcposaguide6, mcposrguide6;
Rotation mcrotaguide6, mcrotrguide6;
Coords mcposaguide7, mcposrguide7;
Rotation mcrotaguide7, mcrotrguide7;
Coords mcposaguide8, mcposrguide8;
Rotation mcrotaguide8, mcrotrguide8;
Coords mcposaguide9, mcposrguide9;
Rotation mcrotaguide9, mcrotrguide9;
Coords mcposaguide10, mcposrguide10;
Rotation mcrotaguide10, mcrotrguide10;
Coords mcposaguide11, mcposrguide11;
Rotation mcrotaguide11, mcrotrguide11;
Coords mcposat0_chopp, mcposrt0_chopp;
Rotation mcrotat0_chopp, mcrotrt0_chopp;
Coords mcposat_check1, mcposrt_check1;
Rotation mcrotat_check1, mcrotrt_check1;
Coords mcposaguide13, mcposrguide13;
Rotation mcrotaguide13, mcrotrguide13;
Coords mcposaguide14, mcposrguide14;
Rotation mcrotaguide14, mcrotrguide14;
Coords mcposaguide15, mcposrguide15;
Rotation mcrotaguide15, mcrotrguide15;
Coords mcposaguide16, mcposrguide16;
Rotation mcrotaguide16, mcrotrguide16;
Coords mcposaguide17, mcposrguide17;
Rotation mcrotaguide17, mcrotrguide17;
Coords mcposaguide18, mcposrguide18;
Rotation mcrotaguide18, mcrotrguide18;
Coords mcposaguide19, mcposrguide19;
Rotation mcrotaguide19, mcrotrguide19;
Coords mcposaguide20, mcposrguide20;
Rotation mcrotaguide20, mcrotrguide20;
Coords mcposaguide21, mcposrguide21;
Rotation mcrotaguide21, mcrotrguide21;
Coords mcposaguide22, mcposrguide22;
Rotation mcrotaguide22, mcrotrguide22;
Coords mcposaguide23, mcposrguide23;
Rotation mcrotaguide23, mcrotrguide23;
Coords mcposaguide24, mcposrguide24;
Rotation mcrotaguide24, mcrotrguide24;
Coords mcposaguide25, mcposrguide25;
Rotation mcrotaguide25, mcrotrguide25;
Coords mcposaguide26, mcposrguide26;
Rotation mcrotaguide26, mcrotrguide26;
Coords mcposaguide27, mcposrguide27;
Rotation mcrotaguide27, mcrotrguide27;
Coords mcposafermi_chopp, mcposrfermi_chopp;
Rotation mcrotafermi_chopp, mcrotrfermi_chopp;
Coords mcposaadjustable_slits, mcposradjustable_slits;
Rotation mcrotaadjustable_slits, mcrotradjustable_slits;
Coords mcposaMonitor1, mcposrMonitor1;
Rotation mcrotaMonitor1, mcrotrMonitor1;
Coords mcposaguide29, mcposrguide29;
Rotation mcrotaguide29, mcrotrguide29;
Coords mcposaguide31, mcposrguide31;
Rotation mcrotaguide31, mcrotrguide31;
Coords mcposaguide32, mcposrguide32;
Rotation mcrotaguide32, mcrotrguide32;
Coords mcposaguide34, mcposrguide34;
Rotation mcrotaguide34, mcrotrguide34;
Coords mcposaE_det, mcposrE_det;
Rotation mcrotaE_det, mcrotrE_det;
Coords mcposaSample_Arm, mcposrSample_Arm;
Rotation mcrotaSample_Arm, mcrotrSample_Arm;
Coords mcposasample, mcposrsample;
Rotation mcrotasample, mcrotrsample;
Coords mcposat_mon_detC, mcposrt_mon_detC;
Rotation mcrotat_mon_detC, mcrotrt_mon_detC;
Coords mcposat_mon_detB, mcposrt_mon_detB;
Rotation mcrotat_mon_detB, mcrotrt_mon_detB;
Coords mcposat_mon_detD, mcposrt_mon_detD;
Rotation mcrotat_mon_detD, mcrotrt_mon_detD;
Coords mcposat_mon2, mcposrt_mon2;
Rotation mcrotat_mon2, mcrotrt_mon2;

MCNUM mcnx, mcny, mcnz, mcnvx, mcnvy, mcnvz, mcnt, mcnsx, mcnsy, mcnsz, mcnp;

/* end declare */

void mcinit(void) {
#define mccompcurname Fermi_T0
#define Fermi_nu mcipFermi_nu
#define FC_num mcipFC_num
#define T0_nu mcipT0_nu
#define Edes mcipEdes
#define T0_off mcipT0_off
#define sxmin mcipsxmin
#define sxmax mcipsxmax
#define symin mcipsymin
#define symax mcipsymax
#define sam_file mcipsam_file
#line 43 "SEQ_11_09_2009.instr"
{
   uniquestr=malloc(10*sizeof(char));
   detoptstr=malloc(150*sizeof(char));
   dett0optstr=malloc(200*sizeof(char));
   detsampoptstr=malloc(400*sizeof(char));
   detdetoptstr=malloc(200*sizeof(char));
   mon1optstr=malloc(200*sizeof(char));
   mon2optstr=malloc(200*sizeof(char)); 
   dettstr=malloc(200*sizeof(char));
   dettstrB=malloc(200*sizeof(char));
   dettstrD=malloc(200*sizeof(char));
   tmpdettstr=malloc(200*sizeof(char));
   tmpdettstr2=malloc(200*sizeof(char));
   L1=18.0;L2=2.0;L3=5.5;LM1=18.26;LM2=29.0032;
   z_gs=4.1802;z_T0=10.0;
   samp_pos=L1+L2+0.0254;
   crad=0.11735;T0_rad=0.281+0.219; 
   ws=0.08294;hs=0.0999;
   sh_end_w=0.0794;sh_end_h=0.09456;
   sh_T0_slp_w=(sh_end_w-0.05)/(samp_pos-z_gs);
   sh_T0_slp_h=(sh_end_h-0.05)/(samp_pos-z_gs);
   //printf("sh_T0_slp_w:%f sh_T0_slp_h:%f\n",sh_T0_slp_w,sh_T0_slp_h);
   //printf("z_T0: %g T0_rad: %g z_gs: %g\n",z_T0,T0_rad,z_gs);
   T0_h1=sh_T0_slp_h*(samp_pos-z_T0+T0_rad)+0.05;
   T0_h2=T0_h1;
   T0_w1=sh_T0_slp_w*(samp_pos-z_T0+T0_rad)+0.05;
   T0_w2=T0_w1;T0wd2=T0_w1/2.0;
   /* set parameters for guide reflectivity profile */
   Gu_R=0.98;Gu_alpha=5.5;Gu_Qc=0.02;Gu_W=2e-3;Gu_m=3.6;Gu_m2=3.0;
   Emin=Edes*0.8;Emax=Edes*1.2;
   /* set parameters for Fermi choppers */
   if (FC_num>0.5 && FC_num<1.5){
       nrad=1.53;
       nchans =16;
   }
   else if (FC_num>1.5 && FC_num<2.5){
       nrad=0.58;
       nchans =27;
   }
   else
	  printf(" Fc_num must be 1 or 2");
   /*determine emission time of certain energy neutrons after the prompt pulse */
   ch_x=log10(Edes*1e-3);  ch_y=-0.4420*ch_x*(1+tanh((ch_x+1.1197)/0.4042))/2-0.1235*ch_x*(1-tanh((ch_x+1.1197)/0.4042))/2-0.4189*tanh((ch_x+1.1197)/0.4042)+0.5612;
   toffset=pow(10,ch_y)/1.0e6;
  /* set phases for critical lengths */
   phase_T0=z_T0/(sqrt(Edes)*SE2V)+toffset+T0_off;
   phase_sam=(samp_pos)/(sqrt(Edes)*SE2V)+toffset;
   phase_det=(samp_pos+L3)/(sqrt(Edes)*SE2V)+toffset;
   phase_Fermi=(L1)/(sqrt(Edes)*SE2V)+toffset;
   phase_m1=(LM1)/(sqrt(Edes)*SE2V)+toffset;
   phase_m2=(LM2)/(sqrt(Edes)*SE2V)+toffset;
   tplotmin=LM1/(sqrt(Emax)*SE2V)+toffset;
   tplotmax=LM1/(sqrt(Emin)*SE2V)+toffset;
   
uniquestr="SEQ_";   sprintf(detoptstr,"SEQ_Sam_mon_Edes_%1.3e_Ferminu_%1.2e_FC_num_%g_T0_off_%1.3e_T0_nu_%1.1e_sxmin%g_sxmax%g_symin%g_symax%g%s",Edes,Fermi_nu,FC_num,T0_off,T0_nu,sxmin,sxmax,symin,symax,".Edat");
   printf("here1");
   sprintf(dett0optstr,"SEQ_T0_mon_Edes_%1.3e_Ferminu_%1.2e_FC_num_%g_T0_off_%1.3e_T0_nu_%1.1e_sxmin%g_sxmax%g_symin%g_symax%g%s",Edes,Fermi_nu,FC_num,T0_off,T0_nu,sxmin,sxmax,symin,symax,".tdat");
   printf("here2\n");
   sprintf(detsampoptstr,"x bins=50, t bins=400 limits [%g %g] file=SEQ_Sam_mon_Edes_%1.3e_Ferminu_%1.2e_FC_num_%g_T0_off_%1.3e_T0_nu_%1.1e_sxmin%g_sxmax%g_symin%g_symax%g%s",((tplotmin-toffset)*samp_pos/LM1+toffset),((tplotmax-toffset)*samp_pos/LM1+toffset),Edes,Fermi_nu,FC_num,T0_off,T0_nu,sxmin,sxmax,symin,symax,".tdat");   
   printf("%s\n%",detsampoptstr);
   printf("here3\n");
   sprintf(detdetoptstr,"SEQ_det_mon_Edes_%1.3e_Ferminu_%1.2e_FC_num_%g_T0_off_%1.3e_T0_nu_%1.1e_sxmin%g_sxmax%g_symin%g_symax%g%s",Edes,Fermi_nu,FC_num,T0_off,T0_nu,sxmin,sxmax,symin,symax,".tdat");
   printf("here4\n");
   sprintf(mon1optstr,"SEQ_mon1_Edes_%1.3e_Ferminu_%1.2e_FC_num_%g_T0_off_%1.3e_T0_nu_%1.1e_sxmin%g_sxmax%g_symin%g_symax%g%s",Edes,Fermi_nu,FC_num,T0_off,T0_nu,sxmin,sxmax,symin,symax,".tdat");
   printf("here5\n");
   sprintf(mon2optstr,"SEQ_mon2_Edes_%1.3e_Ferminu_%1.2e_FC_num_%g_T0_off_%1.3e_T0_nu_%1.1e_sxmin%g_sxmax%g_symin%g_symax%g%s",Edes,Fermi_nu,FC_num,T0_off,T0_nu,sxmin,sxmax,symin,symax,".tdat");
  printf("here6\n");
strcpy(tmpdettstr2,uniquestr);
sprintf(dettstr,"banana t theta y list all outgoing file=");
strcpy(dettstrB,dettstr);
strcpy(dettstrD,dettstr);
sprintf(tmpdettstr,"det1_E_%1.1f_FC_num%g_%g_T0_nu_%g_.tc",Edes,FC_num,Fermi_nu,T0_nu);  
strcat(tmpdettstr2,tmpdettstr);
strcat(dettstr,tmpdettstr2);
strcpy(tmpdettstr2,uniquestr);
sprintf(tmpdettstr,"det1_E_%1.1f_FC_num%g_%g_T0_nu_%g_.tb",Edes,FC_num,Fermi_nu,T0_nu);
strcat(tmpdettstr2,tmpdettstr);
strcat(dettstrB,tmpdettstr2); 
strcpy(tmpdettstr2,uniquestr);
sprintf(tmpdettstr,"det1_E_%1.1f_FC_num%g_%g_T0_nu_%g_.td",Edes,FC_num,Fermi_nu,T0_nu);
strcat(tmpdettstr2,tmpdettstr);
strcat(dettstrD,tmpdettstr2); 
 //printf("here7\n"); 
printf("%s\n%s\n%s\n",dettstr,dettstrB,dettstrD); 
   printf("T0_h1: %e T0_w1: %e T0_h2: %e T0_w2 %e",T0_h1,T0_w1,T0_h2,T0_w2);
   printf("%s%f %s%f\n","sh_end_h: ",sh_end_h,"sh_end_w: ",sh_end_w);
   
}
#line 12897 "SEQ_11_09_2009.c"
#undef sam_file
#undef symax
#undef symin
#undef sxmax
#undef sxmin
#undef T0_off
#undef Edes
#undef T0_nu
#undef FC_num
#undef Fermi_nu
#undef mccompcurname
  /* Computation of coordinate transformations. */
  {
    Coords mctc1, mctc2;
    Rotation mctr1;

    mcDEBUG_INSTR()
    /* Component arm1. */
    SIG_MESSAGE("arm1 (Init:Place/Rotate)");
    rot_set_rotation(mcrotaarm1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 12921 "SEQ_11_09_2009.c"
    rot_copy(mcrotrarm1, mcrotaarm1);
    mcposaarm1 = coords_set(
#line 133 "SEQ_11_09_2009.instr"
      0,
#line 133 "SEQ_11_09_2009.instr"
      0,
#line 133 "SEQ_11_09_2009.instr"
      0);
#line 12930 "SEQ_11_09_2009.c"
    mctc1 = coords_neg(mcposaarm1);
    mcposrarm1 = rot_apply(mcrotaarm1, mctc1);
    mcDEBUG_COMPONENT("arm1", mcposaarm1, mcrotaarm1)
    mccomp_posa[1] = mcposaarm1;
    mccomp_posr[1] = mcposrarm1;
    mcNCounter[1]  = mcPCounter[1] = mcP2Counter[1] = 0;
    mcAbsorbProp[1]= 0;
    /* Component mod. */
    SIG_MESSAGE("mod (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 12944 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotaarm1, mcrotamod);
    rot_transpose(mcrotaarm1, mctr1);
    rot_mul(mcrotamod, mctr1, mcrotrmod);
    mctc1 = coords_set(
#line 142 "SEQ_11_09_2009.instr"
      0,
#line 142 "SEQ_11_09_2009.instr"
      0,
#line 142 "SEQ_11_09_2009.instr"
      0);
#line 12955 "SEQ_11_09_2009.c"
    rot_transpose(mcrotaarm1, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposamod = coords_add(mcposaarm1, mctc2);
    mctc1 = coords_sub(mcposaarm1, mcposamod);
    mcposrmod = rot_apply(mcrotamod, mctc1);
    mcDEBUG_COMPONENT("mod", mcposamod, mcrotamod)
    mccomp_posa[2] = mcposamod;
    mccomp_posr[2] = mcposrmod;
    mcNCounter[2]  = mcPCounter[2] = mcP2Counter[2] = 0;
    mcAbsorbProp[2]= 0;
    /* Component core_ves. */
    SIG_MESSAGE("core_ves (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 12972 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotacore_ves);
    rot_transpose(mcrotamod, mctr1);
    rot_mul(mcrotacore_ves, mctr1, mcrotrcore_ves);
    mctc1 = coords_set(
#line 146 "SEQ_11_09_2009.instr"
      0,
#line 146 "SEQ_11_09_2009.instr"
      0,
#line 146 "SEQ_11_09_2009.instr"
      1.0106);
#line 12983 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposacore_ves = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposamod, mcposacore_ves);
    mcposrcore_ves = rot_apply(mcrotacore_ves, mctc1);
    mcDEBUG_COMPONENT("core_ves", mcposacore_ves, mcrotacore_ves)
    mccomp_posa[3] = mcposacore_ves;
    mccomp_posr[3] = mcposrcore_ves;
    mcNCounter[3]  = mcPCounter[3] = mcP2Counter[3] = 0;
    mcAbsorbProp[3]= 0;
    /* Component shutter_guide. */
    SIG_MESSAGE("shutter_guide (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
#line 151 "SEQ_11_09_2009.instr"
      (0)*DEG2RAD,
#line 151 "SEQ_11_09_2009.instr"
      (0.0)*DEG2RAD,
#line 151 "SEQ_11_09_2009.instr"
      (0)*DEG2RAD);
#line 13003 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotacore_ves, mcrotashutter_guide);
    rot_transpose(mcrotacore_ves, mctr1);
    rot_mul(mcrotashutter_guide, mctr1, mcrotrshutter_guide);
    mctc1 = coords_set(
#line 151 "SEQ_11_09_2009.instr"
      0,
#line 151 "SEQ_11_09_2009.instr"
      0,
#line 151 "SEQ_11_09_2009.instr"
      2.2988);
#line 13014 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposashutter_guide = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposacore_ves, mcposashutter_guide);
    mcposrshutter_guide = rot_apply(mcrotashutter_guide, mctc1);
    mcDEBUG_COMPONENT("shutter_guide", mcposashutter_guide, mcrotashutter_guide)
    mccomp_posa[4] = mcposashutter_guide;
    mccomp_posr[4] = mcposrshutter_guide;
    mcNCounter[4]  = mcPCounter[4] = mcP2Counter[4] = 0;
    mcAbsorbProp[4]= 0;
    /* Component guide1. */
    SIG_MESSAGE("guide1 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13031 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide1);
    rot_transpose(mcrotashutter_guide, mctr1);
    rot_mul(mcrotaguide1, mctr1, mcrotrguide1);
    mctc1 = coords_set(
#line 157 "SEQ_11_09_2009.instr"
      0,
#line 157 "SEQ_11_09_2009.instr"
      0,
#line 157 "SEQ_11_09_2009.instr"
      4.2);
#line 13042 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide1 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposashutter_guide, mcposaguide1);
    mcposrguide1 = rot_apply(mcrotaguide1, mctc1);
    mcDEBUG_COMPONENT("guide1", mcposaguide1, mcrotaguide1)
    mccomp_posa[5] = mcposaguide1;
    mccomp_posr[5] = mcposrguide1;
    mcNCounter[5]  = mcPCounter[5] = mcP2Counter[5] = 0;
    mcAbsorbProp[5]= 0;
    /* Component guide2. */
    SIG_MESSAGE("guide2 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13059 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide2);
    rot_transpose(mcrotaguide1, mctr1);
    rot_mul(mcrotaguide2, mctr1, mcrotrguide2);
    mctc1 = coords_set(
#line 161 "SEQ_11_09_2009.instr"
      0,
#line 161 "SEQ_11_09_2009.instr"
      0,
#line 161 "SEQ_11_09_2009.instr"
      4.682);
#line 13070 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide2 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide1, mcposaguide2);
    mcposrguide2 = rot_apply(mcrotaguide2, mctc1);
    mcDEBUG_COMPONENT("guide2", mcposaguide2, mcrotaguide2)
    mccomp_posa[6] = mcposaguide2;
    mccomp_posr[6] = mcposrguide2;
    mcNCounter[6]  = mcPCounter[6] = mcP2Counter[6] = 0;
    mcAbsorbProp[6]= 0;
    /* Component guide3. */
    SIG_MESSAGE("guide3 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13087 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide3);
    rot_transpose(mcrotaguide2, mctr1);
    rot_mul(mcrotaguide3, mctr1, mcrotrguide3);
    mctc1 = coords_set(
#line 165 "SEQ_11_09_2009.instr"
      0,
#line 165 "SEQ_11_09_2009.instr"
      0,
#line 165 "SEQ_11_09_2009.instr"
      5.164);
#line 13098 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide3 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide2, mcposaguide3);
    mcposrguide3 = rot_apply(mcrotaguide3, mctc1);
    mcDEBUG_COMPONENT("guide3", mcposaguide3, mcrotaguide3)
    mccomp_posa[7] = mcposaguide3;
    mccomp_posr[7] = mcposrguide3;
    mcNCounter[7]  = mcPCounter[7] = mcP2Counter[7] = 0;
    mcAbsorbProp[7]= 0;
    /* Component guide4. */
    SIG_MESSAGE("guide4 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13115 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide4);
    rot_transpose(mcrotaguide3, mctr1);
    rot_mul(mcrotaguide4, mctr1, mcrotrguide4);
    mctc1 = coords_set(
#line 169 "SEQ_11_09_2009.instr"
      0,
#line 169 "SEQ_11_09_2009.instr"
      0,
#line 169 "SEQ_11_09_2009.instr"
      5.646);
#line 13126 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide4 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide3, mcposaguide4);
    mcposrguide4 = rot_apply(mcrotaguide4, mctc1);
    mcDEBUG_COMPONENT("guide4", mcposaguide4, mcrotaguide4)
    mccomp_posa[8] = mcposaguide4;
    mccomp_posr[8] = mcposrguide4;
    mcNCounter[8]  = mcPCounter[8] = mcP2Counter[8] = 0;
    mcAbsorbProp[8]= 0;
    /* Component guide5. */
    SIG_MESSAGE("guide5 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13143 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide5);
    rot_transpose(mcrotaguide4, mctr1);
    rot_mul(mcrotaguide5, mctr1, mcrotrguide5);
    mctc1 = coords_set(
#line 173 "SEQ_11_09_2009.instr"
      0,
#line 173 "SEQ_11_09_2009.instr"
      0,
#line 173 "SEQ_11_09_2009.instr"
      6.128);
#line 13154 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide5 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide4, mcposaguide5);
    mcposrguide5 = rot_apply(mcrotaguide5, mctc1);
    mcDEBUG_COMPONENT("guide5", mcposaguide5, mcrotaguide5)
    mccomp_posa[9] = mcposaguide5;
    mccomp_posr[9] = mcposrguide5;
    mcNCounter[9]  = mcPCounter[9] = mcP2Counter[9] = 0;
    mcAbsorbProp[9]= 0;
    /* Component guide6. */
    SIG_MESSAGE("guide6 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13171 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide6);
    rot_transpose(mcrotaguide5, mctr1);
    rot_mul(mcrotaguide6, mctr1, mcrotrguide6);
    mctc1 = coords_set(
#line 177 "SEQ_11_09_2009.instr"
      0,
#line 177 "SEQ_11_09_2009.instr"
      0,
#line 177 "SEQ_11_09_2009.instr"
      6.61);
#line 13182 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide6 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide5, mcposaguide6);
    mcposrguide6 = rot_apply(mcrotaguide6, mctc1);
    mcDEBUG_COMPONENT("guide6", mcposaguide6, mcrotaguide6)
    mccomp_posa[10] = mcposaguide6;
    mccomp_posr[10] = mcposrguide6;
    mcNCounter[10]  = mcPCounter[10] = mcP2Counter[10] = 0;
    mcAbsorbProp[10]= 0;
    /* Component guide7. */
    SIG_MESSAGE("guide7 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13199 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide7);
    rot_transpose(mcrotaguide6, mctr1);
    rot_mul(mcrotaguide7, mctr1, mcrotrguide7);
    mctc1 = coords_set(
#line 181 "SEQ_11_09_2009.instr"
      0,
#line 181 "SEQ_11_09_2009.instr"
      0,
#line 181 "SEQ_11_09_2009.instr"
      7.092);
#line 13210 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide7 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide6, mcposaguide7);
    mcposrguide7 = rot_apply(mcrotaguide7, mctc1);
    mcDEBUG_COMPONENT("guide7", mcposaguide7, mcrotaguide7)
    mccomp_posa[11] = mcposaguide7;
    mccomp_posr[11] = mcposrguide7;
    mcNCounter[11]  = mcPCounter[11] = mcP2Counter[11] = 0;
    mcAbsorbProp[11]= 0;
    /* Component guide8. */
    SIG_MESSAGE("guide8 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13227 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide8);
    rot_transpose(mcrotaguide7, mctr1);
    rot_mul(mcrotaguide8, mctr1, mcrotrguide8);
    mctc1 = coords_set(
#line 185 "SEQ_11_09_2009.instr"
      0,
#line 185 "SEQ_11_09_2009.instr"
      0,
#line 185 "SEQ_11_09_2009.instr"
      7.574);
#line 13238 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide8 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide7, mcposaguide8);
    mcposrguide8 = rot_apply(mcrotaguide8, mctc1);
    mcDEBUG_COMPONENT("guide8", mcposaguide8, mcrotaguide8)
    mccomp_posa[12] = mcposaguide8;
    mccomp_posr[12] = mcposrguide8;
    mcNCounter[12]  = mcPCounter[12] = mcP2Counter[12] = 0;
    mcAbsorbProp[12]= 0;
    /* Component guide9. */
    SIG_MESSAGE("guide9 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13255 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide9);
    rot_transpose(mcrotaguide8, mctr1);
    rot_mul(mcrotaguide9, mctr1, mcrotrguide9);
    mctc1 = coords_set(
#line 189 "SEQ_11_09_2009.instr"
      0,
#line 189 "SEQ_11_09_2009.instr"
      0,
#line 189 "SEQ_11_09_2009.instr"
      8.056);
#line 13266 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide9 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide8, mcposaguide9);
    mcposrguide9 = rot_apply(mcrotaguide9, mctc1);
    mcDEBUG_COMPONENT("guide9", mcposaguide9, mcrotaguide9)
    mccomp_posa[13] = mcposaguide9;
    mccomp_posr[13] = mcposrguide9;
    mcNCounter[13]  = mcPCounter[13] = mcP2Counter[13] = 0;
    mcAbsorbProp[13]= 0;
    /* Component guide10. */
    SIG_MESSAGE("guide10 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13283 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide10);
    rot_transpose(mcrotaguide9, mctr1);
    rot_mul(mcrotaguide10, mctr1, mcrotrguide10);
    mctc1 = coords_set(
#line 193 "SEQ_11_09_2009.instr"
      0,
#line 193 "SEQ_11_09_2009.instr"
      0,
#line 193 "SEQ_11_09_2009.instr"
      8.538);
#line 13294 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide10 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide9, mcposaguide10);
    mcposrguide10 = rot_apply(mcrotaguide10, mctc1);
    mcDEBUG_COMPONENT("guide10", mcposaguide10, mcrotaguide10)
    mccomp_posa[14] = mcposaguide10;
    mccomp_posr[14] = mcposrguide10;
    mcNCounter[14]  = mcPCounter[14] = mcP2Counter[14] = 0;
    mcAbsorbProp[14]= 0;
    /* Component guide11. */
    SIG_MESSAGE("guide11 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13311 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide11);
    rot_transpose(mcrotaguide10, mctr1);
    rot_mul(mcrotaguide11, mctr1, mcrotrguide11);
    mctc1 = coords_set(
#line 197 "SEQ_11_09_2009.instr"
      0,
#line 197 "SEQ_11_09_2009.instr"
      0,
#line 197 "SEQ_11_09_2009.instr"
      9.02);
#line 13322 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide11 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide10, mcposaguide11);
    mcposrguide11 = rot_apply(mcrotaguide11, mctc1);
    mcDEBUG_COMPONENT("guide11", mcposaguide11, mcrotaguide11)
    mccomp_posa[15] = mcposaguide11;
    mccomp_posr[15] = mcposrguide11;
    mcNCounter[15]  = mcPCounter[15] = mcP2Counter[15] = 0;
    mcAbsorbProp[15]= 0;
    /* Component t0_chopp. */
    SIG_MESSAGE("t0_chopp (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13339 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotat0_chopp);
    rot_transpose(mcrotaguide11, mctr1);
    rot_mul(mcrotat0_chopp, mctr1, mcrotrt0_chopp);
    mctc1 = coords_set(
#line 202 "SEQ_11_09_2009.instr"
      0,
#line 202 "SEQ_11_09_2009.instr"
      0,
#line 202 "SEQ_11_09_2009.instr"
      z_T0);
#line 13350 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposat0_chopp = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide11, mcposat0_chopp);
    mcposrt0_chopp = rot_apply(mcrotat0_chopp, mctc1);
    mcDEBUG_COMPONENT("t0_chopp", mcposat0_chopp, mcrotat0_chopp)
    mccomp_posa[16] = mcposat0_chopp;
    mccomp_posr[16] = mcposrt0_chopp;
    mcNCounter[16]  = mcPCounter[16] = mcP2Counter[16] = 0;
    mcAbsorbProp[16]= 0;
    /* Component t_check1. */
    SIG_MESSAGE("t_check1 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13367 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotat_check1);
    rot_transpose(mcrotat0_chopp, mctr1);
    rot_mul(mcrotat_check1, mctr1, mcrotrt_check1);
    mctc1 = coords_set(
#line 208 "SEQ_11_09_2009.instr"
      0,
#line 208 "SEQ_11_09_2009.instr"
      0,
#line 208 "SEQ_11_09_2009.instr"
      z_T0 + 0.3);
#line 13378 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposat_check1 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposat0_chopp, mcposat_check1);
    mcposrt_check1 = rot_apply(mcrotat_check1, mctc1);
    mcDEBUG_COMPONENT("t_check1", mcposat_check1, mcrotat_check1)
    mccomp_posa[17] = mcposat_check1;
    mccomp_posr[17] = mcposrt_check1;
    mcNCounter[17]  = mcPCounter[17] = mcP2Counter[17] = 0;
    mcAbsorbProp[17]= 0;
    /* Component guide13. */
    SIG_MESSAGE("guide13 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13395 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide13);
    rot_transpose(mcrotat_check1, mctr1);
    rot_mul(mcrotaguide13, mctr1, mcrotrguide13);
    mctc1 = coords_set(
#line 213 "SEQ_11_09_2009.instr"
      0,
#line 213 "SEQ_11_09_2009.instr"
      0,
#line 213 "SEQ_11_09_2009.instr"
      10.5);
#line 13406 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide13 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposat_check1, mcposaguide13);
    mcposrguide13 = rot_apply(mcrotaguide13, mctc1);
    mcDEBUG_COMPONENT("guide13", mcposaguide13, mcrotaguide13)
    mccomp_posa[18] = mcposaguide13;
    mccomp_posr[18] = mcposrguide13;
    mcNCounter[18]  = mcPCounter[18] = mcP2Counter[18] = 0;
    mcAbsorbProp[18]= 0;
    /* Component guide14. */
    SIG_MESSAGE("guide14 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13423 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide14);
    rot_transpose(mcrotaguide13, mctr1);
    rot_mul(mcrotaguide14, mctr1, mcrotrguide14);
    mctc1 = coords_set(
#line 217 "SEQ_11_09_2009.instr"
      0,
#line 217 "SEQ_11_09_2009.instr"
      0,
#line 217 "SEQ_11_09_2009.instr"
      10.992);
#line 13434 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide14 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide13, mcposaguide14);
    mcposrguide14 = rot_apply(mcrotaguide14, mctc1);
    mcDEBUG_COMPONENT("guide14", mcposaguide14, mcrotaguide14)
    mccomp_posa[19] = mcposaguide14;
    mccomp_posr[19] = mcposrguide14;
    mcNCounter[19]  = mcPCounter[19] = mcP2Counter[19] = 0;
    mcAbsorbProp[19]= 0;
    /* Component guide15. */
    SIG_MESSAGE("guide15 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13451 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide15);
    rot_transpose(mcrotaguide14, mctr1);
    rot_mul(mcrotaguide15, mctr1, mcrotrguide15);
    mctc1 = coords_set(
#line 221 "SEQ_11_09_2009.instr"
      0,
#line 221 "SEQ_11_09_2009.instr"
      0,
#line 221 "SEQ_11_09_2009.instr"
      11.484);
#line 13462 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide15 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide14, mcposaguide15);
    mcposrguide15 = rot_apply(mcrotaguide15, mctc1);
    mcDEBUG_COMPONENT("guide15", mcposaguide15, mcrotaguide15)
    mccomp_posa[20] = mcposaguide15;
    mccomp_posr[20] = mcposrguide15;
    mcNCounter[20]  = mcPCounter[20] = mcP2Counter[20] = 0;
    mcAbsorbProp[20]= 0;
    /* Component guide16. */
    SIG_MESSAGE("guide16 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13479 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide16);
    rot_transpose(mcrotaguide15, mctr1);
    rot_mul(mcrotaguide16, mctr1, mcrotrguide16);
    mctc1 = coords_set(
#line 225 "SEQ_11_09_2009.instr"
      0,
#line 225 "SEQ_11_09_2009.instr"
      0,
#line 225 "SEQ_11_09_2009.instr"
      11.976);
#line 13490 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide16 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide15, mcposaguide16);
    mcposrguide16 = rot_apply(mcrotaguide16, mctc1);
    mcDEBUG_COMPONENT("guide16", mcposaguide16, mcrotaguide16)
    mccomp_posa[21] = mcposaguide16;
    mccomp_posr[21] = mcposrguide16;
    mcNCounter[21]  = mcPCounter[21] = mcP2Counter[21] = 0;
    mcAbsorbProp[21]= 0;
    /* Component guide17. */
    SIG_MESSAGE("guide17 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13507 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide17);
    rot_transpose(mcrotaguide16, mctr1);
    rot_mul(mcrotaguide17, mctr1, mcrotrguide17);
    mctc1 = coords_set(
#line 229 "SEQ_11_09_2009.instr"
      0,
#line 229 "SEQ_11_09_2009.instr"
      0,
#line 229 "SEQ_11_09_2009.instr"
      12.468);
#line 13518 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide17 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide16, mcposaguide17);
    mcposrguide17 = rot_apply(mcrotaguide17, mctc1);
    mcDEBUG_COMPONENT("guide17", mcposaguide17, mcrotaguide17)
    mccomp_posa[22] = mcposaguide17;
    mccomp_posr[22] = mcposrguide17;
    mcNCounter[22]  = mcPCounter[22] = mcP2Counter[22] = 0;
    mcAbsorbProp[22]= 0;
    /* Component guide18. */
    SIG_MESSAGE("guide18 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13535 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide18);
    rot_transpose(mcrotaguide17, mctr1);
    rot_mul(mcrotaguide18, mctr1, mcrotrguide18);
    mctc1 = coords_set(
#line 233 "SEQ_11_09_2009.instr"
      0,
#line 233 "SEQ_11_09_2009.instr"
      0,
#line 233 "SEQ_11_09_2009.instr"
      12.96);
#line 13546 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide18 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide17, mcposaguide18);
    mcposrguide18 = rot_apply(mcrotaguide18, mctc1);
    mcDEBUG_COMPONENT("guide18", mcposaguide18, mcrotaguide18)
    mccomp_posa[23] = mcposaguide18;
    mccomp_posr[23] = mcposrguide18;
    mcNCounter[23]  = mcPCounter[23] = mcP2Counter[23] = 0;
    mcAbsorbProp[23]= 0;
    /* Component guide19. */
    SIG_MESSAGE("guide19 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13563 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide19);
    rot_transpose(mcrotaguide18, mctr1);
    rot_mul(mcrotaguide19, mctr1, mcrotrguide19);
    mctc1 = coords_set(
#line 237 "SEQ_11_09_2009.instr"
      0,
#line 237 "SEQ_11_09_2009.instr"
      0,
#line 237 "SEQ_11_09_2009.instr"
      13.452);
#line 13574 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide19 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide18, mcposaguide19);
    mcposrguide19 = rot_apply(mcrotaguide19, mctc1);
    mcDEBUG_COMPONENT("guide19", mcposaguide19, mcrotaguide19)
    mccomp_posa[24] = mcposaguide19;
    mccomp_posr[24] = mcposrguide19;
    mcNCounter[24]  = mcPCounter[24] = mcP2Counter[24] = 0;
    mcAbsorbProp[24]= 0;
    /* Component guide20. */
    SIG_MESSAGE("guide20 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13591 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide20);
    rot_transpose(mcrotaguide19, mctr1);
    rot_mul(mcrotaguide20, mctr1, mcrotrguide20);
    mctc1 = coords_set(
#line 241 "SEQ_11_09_2009.instr"
      0,
#line 241 "SEQ_11_09_2009.instr"
      0,
#line 241 "SEQ_11_09_2009.instr"
      13.944);
#line 13602 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide20 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide19, mcposaguide20);
    mcposrguide20 = rot_apply(mcrotaguide20, mctc1);
    mcDEBUG_COMPONENT("guide20", mcposaguide20, mcrotaguide20)
    mccomp_posa[25] = mcposaguide20;
    mccomp_posr[25] = mcposrguide20;
    mcNCounter[25]  = mcPCounter[25] = mcP2Counter[25] = 0;
    mcAbsorbProp[25]= 0;
    /* Component guide21. */
    SIG_MESSAGE("guide21 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13619 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide21);
    rot_transpose(mcrotaguide20, mctr1);
    rot_mul(mcrotaguide21, mctr1, mcrotrguide21);
    mctc1 = coords_set(
#line 245 "SEQ_11_09_2009.instr"
      0,
#line 245 "SEQ_11_09_2009.instr"
      0,
#line 245 "SEQ_11_09_2009.instr"
      14.436);
#line 13630 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide21 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide20, mcposaguide21);
    mcposrguide21 = rot_apply(mcrotaguide21, mctc1);
    mcDEBUG_COMPONENT("guide21", mcposaguide21, mcrotaguide21)
    mccomp_posa[26] = mcposaguide21;
    mccomp_posr[26] = mcposrguide21;
    mcNCounter[26]  = mcPCounter[26] = mcP2Counter[26] = 0;
    mcAbsorbProp[26]= 0;
    /* Component guide22. */
    SIG_MESSAGE("guide22 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13647 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide22);
    rot_transpose(mcrotaguide21, mctr1);
    rot_mul(mcrotaguide22, mctr1, mcrotrguide22);
    mctc1 = coords_set(
#line 249 "SEQ_11_09_2009.instr"
      0,
#line 249 "SEQ_11_09_2009.instr"
      0,
#line 249 "SEQ_11_09_2009.instr"
      14.928);
#line 13658 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide22 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide21, mcposaguide22);
    mcposrguide22 = rot_apply(mcrotaguide22, mctc1);
    mcDEBUG_COMPONENT("guide22", mcposaguide22, mcrotaguide22)
    mccomp_posa[27] = mcposaguide22;
    mccomp_posr[27] = mcposrguide22;
    mcNCounter[27]  = mcPCounter[27] = mcP2Counter[27] = 0;
    mcAbsorbProp[27]= 0;
    /* Component guide23. */
    SIG_MESSAGE("guide23 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13675 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide23);
    rot_transpose(mcrotaguide22, mctr1);
    rot_mul(mcrotaguide23, mctr1, mcrotrguide23);
    mctc1 = coords_set(
#line 253 "SEQ_11_09_2009.instr"
      0,
#line 253 "SEQ_11_09_2009.instr"
      0,
#line 253 "SEQ_11_09_2009.instr"
      15.42);
#line 13686 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide23 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide22, mcposaguide23);
    mcposrguide23 = rot_apply(mcrotaguide23, mctc1);
    mcDEBUG_COMPONENT("guide23", mcposaguide23, mcrotaguide23)
    mccomp_posa[28] = mcposaguide23;
    mccomp_posr[28] = mcposrguide23;
    mcNCounter[28]  = mcPCounter[28] = mcP2Counter[28] = 0;
    mcAbsorbProp[28]= 0;
    /* Component guide24. */
    SIG_MESSAGE("guide24 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13703 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide24);
    rot_transpose(mcrotaguide23, mctr1);
    rot_mul(mcrotaguide24, mctr1, mcrotrguide24);
    mctc1 = coords_set(
#line 257 "SEQ_11_09_2009.instr"
      0,
#line 257 "SEQ_11_09_2009.instr"
      0,
#line 257 "SEQ_11_09_2009.instr"
      15.912);
#line 13714 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide24 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide23, mcposaguide24);
    mcposrguide24 = rot_apply(mcrotaguide24, mctc1);
    mcDEBUG_COMPONENT("guide24", mcposaguide24, mcrotaguide24)
    mccomp_posa[29] = mcposaguide24;
    mccomp_posr[29] = mcposrguide24;
    mcNCounter[29]  = mcPCounter[29] = mcP2Counter[29] = 0;
    mcAbsorbProp[29]= 0;
    /* Component guide25. */
    SIG_MESSAGE("guide25 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13731 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide25);
    rot_transpose(mcrotaguide24, mctr1);
    rot_mul(mcrotaguide25, mctr1, mcrotrguide25);
    mctc1 = coords_set(
#line 261 "SEQ_11_09_2009.instr"
      0,
#line 261 "SEQ_11_09_2009.instr"
      0,
#line 261 "SEQ_11_09_2009.instr"
      16.404);
#line 13742 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide25 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide24, mcposaguide25);
    mcposrguide25 = rot_apply(mcrotaguide25, mctc1);
    mcDEBUG_COMPONENT("guide25", mcposaguide25, mcrotaguide25)
    mccomp_posa[30] = mcposaguide25;
    mccomp_posr[30] = mcposrguide25;
    mcNCounter[30]  = mcPCounter[30] = mcP2Counter[30] = 0;
    mcAbsorbProp[30]= 0;
    /* Component guide26. */
    SIG_MESSAGE("guide26 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13759 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide26);
    rot_transpose(mcrotaguide25, mctr1);
    rot_mul(mcrotaguide26, mctr1, mcrotrguide26);
    mctc1 = coords_set(
#line 265 "SEQ_11_09_2009.instr"
      0,
#line 265 "SEQ_11_09_2009.instr"
      0,
#line 265 "SEQ_11_09_2009.instr"
      16.896);
#line 13770 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide26 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide25, mcposaguide26);
    mcposrguide26 = rot_apply(mcrotaguide26, mctc1);
    mcDEBUG_COMPONENT("guide26", mcposaguide26, mcrotaguide26)
    mccomp_posa[31] = mcposaguide26;
    mccomp_posr[31] = mcposrguide26;
    mcNCounter[31]  = mcPCounter[31] = mcP2Counter[31] = 0;
    mcAbsorbProp[31]= 0;
    /* Component guide27. */
    SIG_MESSAGE("guide27 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13787 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide27);
    rot_transpose(mcrotaguide26, mctr1);
    rot_mul(mcrotaguide27, mctr1, mcrotrguide27);
    mctc1 = coords_set(
#line 269 "SEQ_11_09_2009.instr"
      0,
#line 269 "SEQ_11_09_2009.instr"
      0,
#line 269 "SEQ_11_09_2009.instr"
      17.388);
#line 13798 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide27 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide26, mcposaguide27);
    mcposrguide27 = rot_apply(mcrotaguide27, mctc1);
    mcDEBUG_COMPONENT("guide27", mcposaguide27, mcrotaguide27)
    mccomp_posa[32] = mcposaguide27;
    mccomp_posr[32] = mcposrguide27;
    mcNCounter[32]  = mcPCounter[32] = mcP2Counter[32] = 0;
    mcAbsorbProp[32]= 0;
    /* Component fermi_chopp. */
    SIG_MESSAGE("fermi_chopp (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13815 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotafermi_chopp);
    rot_transpose(mcrotaguide27, mctr1);
    rot_mul(mcrotafermi_chopp, mctr1, mcrotrfermi_chopp);
    mctc1 = coords_set(
#line 274 "SEQ_11_09_2009.instr"
      0,
#line 274 "SEQ_11_09_2009.instr"
      0,
#line 274 "SEQ_11_09_2009.instr"
      L1);
#line 13826 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposafermi_chopp = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide27, mcposafermi_chopp);
    mcposrfermi_chopp = rot_apply(mcrotafermi_chopp, mctc1);
    mcDEBUG_COMPONENT("fermi_chopp", mcposafermi_chopp, mcrotafermi_chopp)
    mccomp_posa[33] = mcposafermi_chopp;
    mccomp_posr[33] = mcposrfermi_chopp;
    mcNCounter[33]  = mcPCounter[33] = mcP2Counter[33] = 0;
    mcAbsorbProp[33]= 0;
    /* Component adjustable_slits. */
    SIG_MESSAGE("adjustable_slits (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13843 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaadjustable_slits);
    rot_transpose(mcrotafermi_chopp, mctr1);
    rot_mul(mcrotaadjustable_slits, mctr1, mcrotradjustable_slits);
    mctc1 = coords_set(
#line 276 "SEQ_11_09_2009.instr"
      0,
#line 276 "SEQ_11_09_2009.instr"
      0,
#line 276 "SEQ_11_09_2009.instr"
      LM1 -0.01);
#line 13854 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaadjustable_slits = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposafermi_chopp, mcposaadjustable_slits);
    mcposradjustable_slits = rot_apply(mcrotaadjustable_slits, mctc1);
    mcDEBUG_COMPONENT("adjustable_slits", mcposaadjustable_slits, mcrotaadjustable_slits)
    mccomp_posa[34] = mcposaadjustable_slits;
    mccomp_posr[34] = mcposradjustable_slits;
    mcNCounter[34]  = mcPCounter[34] = mcP2Counter[34] = 0;
    mcAbsorbProp[34]= 0;
    /* Component Monitor1. */
    SIG_MESSAGE("Monitor1 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13871 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaMonitor1);
    rot_transpose(mcrotaadjustable_slits, mctr1);
    rot_mul(mcrotaMonitor1, mctr1, mcrotrMonitor1);
    mctc1 = coords_set(
#line 282 "SEQ_11_09_2009.instr"
      0,
#line 282 "SEQ_11_09_2009.instr"
      0,
#line 282 "SEQ_11_09_2009.instr"
      LM1);
#line 13882 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaMonitor1 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaadjustable_slits, mcposaMonitor1);
    mcposrMonitor1 = rot_apply(mcrotaMonitor1, mctc1);
    mcDEBUG_COMPONENT("Monitor1", mcposaMonitor1, mcrotaMonitor1)
    mccomp_posa[35] = mcposaMonitor1;
    mccomp_posr[35] = mcposrMonitor1;
    mcNCounter[35]  = mcPCounter[35] = mcP2Counter[35] = 0;
    mcAbsorbProp[35]= 0;
    /* Component guide29. */
    SIG_MESSAGE("guide29 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13899 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide29);
    rot_transpose(mcrotaMonitor1, mctr1);
    rot_mul(mcrotaguide29, mctr1, mcrotrguide29);
    mctc1 = coords_set(
#line 288 "SEQ_11_09_2009.instr"
      0,
#line 288 "SEQ_11_09_2009.instr"
      0,
#line 288 "SEQ_11_09_2009.instr"
      18.235 + .0254);
#line 13910 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide29 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaMonitor1, mcposaguide29);
    mcposrguide29 = rot_apply(mcrotaguide29, mctc1);
    mcDEBUG_COMPONENT("guide29", mcposaguide29, mcrotaguide29)
    mccomp_posa[36] = mcposaguide29;
    mccomp_posr[36] = mcposrguide29;
    mcNCounter[36]  = mcPCounter[36] = mcP2Counter[36] = 0;
    mcAbsorbProp[36]= 0;
    /* Component guide31. */
    SIG_MESSAGE("guide31 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13927 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide31);
    rot_transpose(mcrotaguide29, mctr1);
    rot_mul(mcrotaguide31, mctr1, mcrotrguide31);
    mctc1 = coords_set(
#line 293 "SEQ_11_09_2009.instr"
      0,
#line 293 "SEQ_11_09_2009.instr"
      0,
#line 293 "SEQ_11_09_2009.instr"
      18.473 + .0254);
#line 13938 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide31 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide29, mcposaguide31);
    mcposrguide31 = rot_apply(mcrotaguide31, mctc1);
    mcDEBUG_COMPONENT("guide31", mcposaguide31, mcrotaguide31)
    mccomp_posa[37] = mcposaguide31;
    mccomp_posr[37] = mcposrguide31;
    mcNCounter[37]  = mcPCounter[37] = mcP2Counter[37] = 0;
    mcAbsorbProp[37]= 0;
    /* Component guide32. */
    SIG_MESSAGE("guide32 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13955 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide32);
    rot_transpose(mcrotaguide31, mctr1);
    rot_mul(mcrotaguide32, mctr1, mcrotrguide32);
    mctc1 = coords_set(
#line 297 "SEQ_11_09_2009.instr"
      0,
#line 297 "SEQ_11_09_2009.instr"
      0,
#line 297 "SEQ_11_09_2009.instr"
      18.9315 + .0254);
#line 13966 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide32 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide31, mcposaguide32);
    mcposrguide32 = rot_apply(mcrotaguide32, mctc1);
    mcDEBUG_COMPONENT("guide32", mcposaguide32, mcrotaguide32)
    mccomp_posa[38] = mcposaguide32;
    mccomp_posr[38] = mcposrguide32;
    mcNCounter[38]  = mcPCounter[38] = mcP2Counter[38] = 0;
    mcAbsorbProp[38]= 0;
    /* Component guide34. */
    SIG_MESSAGE("guide34 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 13983 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaguide34);
    rot_transpose(mcrotaguide32, mctr1);
    rot_mul(mcrotaguide34, mctr1, mcrotrguide34);
    mctc1 = coords_set(
#line 302 "SEQ_11_09_2009.instr"
      0,
#line 302 "SEQ_11_09_2009.instr"
      0,
#line 302 "SEQ_11_09_2009.instr"
      19.391 + .0254);
#line 13994 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaguide34 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaguide32, mcposaguide34);
    mcposrguide34 = rot_apply(mcrotaguide34, mctc1);
    mcDEBUG_COMPONENT("guide34", mcposaguide34, mcrotaguide34)
    mccomp_posa[39] = mcposaguide34;
    mccomp_posr[39] = mcposrguide34;
    mcNCounter[39]  = mcPCounter[39] = mcP2Counter[39] = 0;
    mcAbsorbProp[39]= 0;
    /* Component E_det. */
    SIG_MESSAGE("E_det (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14011 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotafermi_chopp, mcrotaE_det);
    rot_transpose(mcrotaguide34, mctr1);
    rot_mul(mcrotaE_det, mctr1, mcrotrE_det);
    mctc1 = coords_set(
#line 307 "SEQ_11_09_2009.instr"
      0,
#line 307 "SEQ_11_09_2009.instr"
      0,
#line 307 "SEQ_11_09_2009.instr"
      L2 -.01);
#line 14022 "SEQ_11_09_2009.c"
    rot_transpose(mcrotafermi_chopp, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaE_det = coords_add(mcposafermi_chopp, mctc2);
    mctc1 = coords_sub(mcposaguide34, mcposaE_det);
    mcposrE_det = rot_apply(mcrotaE_det, mctc1);
    mcDEBUG_COMPONENT("E_det", mcposaE_det, mcrotaE_det)
    mccomp_posa[40] = mcposaE_det;
    mccomp_posr[40] = mcposrE_det;
    mcNCounter[40]  = mcPCounter[40] = mcP2Counter[40] = 0;
    mcAbsorbProp[40]= 0;
    /* Component Sample_Arm. */
    SIG_MESSAGE("Sample_Arm (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14039 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotaSample_Arm);
    rot_transpose(mcrotaE_det, mctr1);
    rot_mul(mcrotaSample_Arm, mctr1, mcrotrSample_Arm);
    mctc1 = coords_set(
#line 310 "SEQ_11_09_2009.instr"
      0,
#line 310 "SEQ_11_09_2009.instr"
      0,
#line 310 "SEQ_11_09_2009.instr"
      samp_pos);
#line 14050 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposaSample_Arm = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposaE_det, mcposaSample_Arm);
    mcposrSample_Arm = rot_apply(mcrotaSample_Arm, mctc1);
    mcDEBUG_COMPONENT("Sample_Arm", mcposaSample_Arm, mcrotaSample_Arm)
    mccomp_posa[41] = mcposaSample_Arm;
    mccomp_posr[41] = mcposrSample_Arm;
    mcNCounter[41]  = mcPCounter[41] = mcP2Counter[41] = 0;
    mcAbsorbProp[41]= 0;
    /* Component sample. */
    SIG_MESSAGE("sample (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14067 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotaSample_Arm, mcrotasample);
    rot_transpose(mcrotaSample_Arm, mctr1);
    rot_mul(mcrotasample, mctr1, mcrotrsample);
    mctc1 = coords_set(
#line 314 "SEQ_11_09_2009.instr"
      0.0,
#line 314 "SEQ_11_09_2009.instr"
      0.0,
#line 314 "SEQ_11_09_2009.instr"
      0.0);
#line 14078 "SEQ_11_09_2009.c"
    rot_transpose(mcrotaSample_Arm, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposasample = coords_add(mcposaSample_Arm, mctc2);
    mctc1 = coords_sub(mcposaSample_Arm, mcposasample);
    mcposrsample = rot_apply(mcrotasample, mctc1);
    mcDEBUG_COMPONENT("sample", mcposasample, mcrotasample)
    mccomp_posa[42] = mcposasample;
    mccomp_posr[42] = mcposrsample;
    mcNCounter[42]  = mcPCounter[42] = mcP2Counter[42] = 0;
    mcAbsorbProp[42]= 0;
    /* Component t_mon_detC. */
    SIG_MESSAGE("t_mon_detC (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14095 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotat_mon_detC);
    rot_transpose(mcrotasample, mctr1);
    rot_mul(mcrotat_mon_detC, mctr1, mcrotrt_mon_detC);
    mctc1 = coords_set(
#line 320 "SEQ_11_09_2009.instr"
      0,
#line 320 "SEQ_11_09_2009.instr"
      0,
#line 320 "SEQ_11_09_2009.instr"
      samp_pos + 0.00005);
#line 14106 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposat_mon_detC = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposasample, mcposat_mon_detC);
    mcposrt_mon_detC = rot_apply(mcrotat_mon_detC, mctc1);
    mcDEBUG_COMPONENT("t_mon_detC", mcposat_mon_detC, mcrotat_mon_detC)
    mccomp_posa[43] = mcposat_mon_detC;
    mccomp_posr[43] = mcposrt_mon_detC;
    mcNCounter[43]  = mcPCounter[43] = mcP2Counter[43] = 0;
    mcAbsorbProp[43]= 0;
    /* Component t_mon_detB. */
    SIG_MESSAGE("t_mon_detB (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14123 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotat_mon_detB);
    rot_transpose(mcrotat_mon_detC, mctr1);
    rot_mul(mcrotat_mon_detB, mctr1, mcrotrt_mon_detB);
    mctc1 = coords_set(
#line 324 "SEQ_11_09_2009.instr"
      0,
#line 324 "SEQ_11_09_2009.instr"
      0,
#line 324 "SEQ_11_09_2009.instr"
      samp_pos + 0.00005);
#line 14134 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposat_mon_detB = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposat_mon_detC, mcposat_mon_detB);
    mcposrt_mon_detB = rot_apply(mcrotat_mon_detB, mctc1);
    mcDEBUG_COMPONENT("t_mon_detB", mcposat_mon_detB, mcrotat_mon_detB)
    mccomp_posa[44] = mcposat_mon_detB;
    mccomp_posr[44] = mcposrt_mon_detB;
    mcNCounter[44]  = mcPCounter[44] = mcP2Counter[44] = 0;
    mcAbsorbProp[44]= 0;
    /* Component t_mon_detD. */
    SIG_MESSAGE("t_mon_detD (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14151 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotat_mon_detD);
    rot_transpose(mcrotat_mon_detB, mctr1);
    rot_mul(mcrotat_mon_detD, mctr1, mcrotrt_mon_detD);
    mctc1 = coords_set(
#line 328 "SEQ_11_09_2009.instr"
      0,
#line 328 "SEQ_11_09_2009.instr"
      0,
#line 328 "SEQ_11_09_2009.instr"
      samp_pos + 0.00005);
#line 14162 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposat_mon_detD = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposat_mon_detB, mcposat_mon_detD);
    mcposrt_mon_detD = rot_apply(mcrotat_mon_detD, mctc1);
    mcDEBUG_COMPONENT("t_mon_detD", mcposat_mon_detD, mcrotat_mon_detD)
    mccomp_posa[45] = mcposat_mon_detD;
    mccomp_posr[45] = mcposrt_mon_detD;
    mcNCounter[45]  = mcPCounter[45] = mcP2Counter[45] = 0;
    mcAbsorbProp[45]= 0;
    /* Component t_mon2. */
    SIG_MESSAGE("t_mon2 (Init:Place/Rotate)");
    rot_set_rotation(mctr1,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD,
      (0.0)*DEG2RAD);
#line 14179 "SEQ_11_09_2009.c"
    rot_mul(mctr1, mcrotamod, mcrotat_mon2);
    rot_transpose(mcrotat_mon_detD, mctr1);
    rot_mul(mcrotat_mon2, mctr1, mcrotrt_mon2);
    mctc1 = coords_set(
#line 335 "SEQ_11_09_2009.instr"
      0,
#line 335 "SEQ_11_09_2009.instr"
      0,
#line 335 "SEQ_11_09_2009.instr"
      LM2);
#line 14190 "SEQ_11_09_2009.c"
    rot_transpose(mcrotamod, mctr1);
    mctc2 = rot_apply(mctr1, mctc1);
    mcposat_mon2 = coords_add(mcposamod, mctc2);
    mctc1 = coords_sub(mcposat_mon_detD, mcposat_mon2);
    mcposrt_mon2 = rot_apply(mcrotat_mon2, mctc1);
    mcDEBUG_COMPONENT("t_mon2", mcposat_mon2, mcrotat_mon2)
    mccomp_posa[46] = mcposat_mon2;
    mccomp_posr[46] = mcposrt_mon2;
    mcNCounter[46]  = mcPCounter[46] = mcP2Counter[46] = 0;
    mcAbsorbProp[46]= 0;
  /* Component initializations. */
  /* Initializations for component arm1. */
  SIG_MESSAGE("arm1 (Init)");
#line 42 "SEQ_11_09_2009.instr"
  mccarm1_percent = 10;
#line 42 "SEQ_11_09_2009.instr"
  mccarm1_flag_save = 0;
#line 42 "SEQ_11_09_2009.instr"
  mccarm1_minutes = 0;
#line 14210 "SEQ_11_09_2009.c"

#define mccompcurname  arm1
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define profile mccarm1_profile
#define IntermediateCnts mccarm1_IntermediateCnts
#define StartTime mccarm1_StartTime
#define EndTime mccarm1_EndTime
#define percent mccarm1_percent
#define flag_save mccarm1_flag_save
#define minutes mccarm1_minutes
#line 61 "/usr/local/lib/mcstas/misc/Progress_bar.comp"
{
  fprintf(stdout, "[%s] Initialize\n", mcinstrument_name);
  if (percent*mcget_ncount()/100 < 1e5) {
    percent=1e5*100.0/mcget_ncount();
  }
}
#line 14229 "SEQ_11_09_2009.c"
#undef minutes
#undef flag_save
#undef percent
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef profile
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component mod. */
  SIG_MESSAGE("mod (Init)");
#line 135 "SEQ_11_09_2009.instr"
  mccmod_width = 0.0923;
#line 136 "SEQ_11_09_2009.instr"
  mccmod_height = 0.1113;
#line 137 "SEQ_11_09_2009.instr"
  mccmod_dist = 0.995;
#line 138 "SEQ_11_09_2009.instr"
  mccmod_xw = 0.1;
#line 139 "SEQ_11_09_2009.instr"
  mccmod_yh = 0.12;
#line 140 "SEQ_11_09_2009.instr"
  mccmod_Emin = Emin;
#line 141 "SEQ_11_09_2009.instr"
  mccmod_Emax = Emax;
#line 14257 "SEQ_11_09_2009.c"

#define mccompcurname  mod
#define mccompcurtype  SNS_source
#define mccompcurindex 2
#define S_filename mccmod_S_filename
#define hdiv mccmod_hdiv
#define vdiv mccmod_vdiv
#define p_in mccmod_p_in
#define width mccmod_width
#define height mccmod_height
#define dist mccmod_dist
#define xw mccmod_xw
#define yh mccmod_yh
#define Emin mccmod_Emin
#define Emax mccmod_Emax
#line 407 "SNS_source.comp"
{
  FILE *fp;
  double llim, hlim,ltlim,htlim,junk;  
  double tycol[200];
  double **Imat;
  int idx1,idx2;
  Pvec=malloc(500*sizeof(double));
  inxvec=malloc(500*sizeof(double));
  inyvec=malloc(500*sizeof(double));
  tcol=malloc(200*sizeof(double));
  Ecol=malloc(200*sizeof(double));
  tyval=malloc(500*sizeof(double));
  txval=malloc(500*sizeof(double));
  tPvec=malloc(500*sizeof(double));
  Ptmat=malloc(200*sizeof(double *));
  for(idx1=0;idx1<200;idx1++){
    Ptmat[idx1]=malloc(200*sizeof(double));
  } 
  Imat=malloc(200*sizeof(double*));
  for(idx1=0;idx1<200;idx1++){
    Imat[idx1]=malloc(500*sizeof(double));
  }
  ltlim=0.1;
  htlim=1.8e3;
 /* read file */
  printf("%s%s\n","Loading moderator file ",S_filename);
   sns_source_load(S_filename,inxvec,inyvec,0,2,&xylength,tcol,Ecol,Imat,&ntvals,&nEvals);
 /* calculate probabilty distribution function points for use in interpolation routine */

 llim=inxvec[1];hlim=inxvec[xylength];
 printf("Start calculating probability distribution\n");
 /* calculate total number of neutrons in specified energy window */
 INorm2=integ1(xonly,Emin/1000.0,Emax/1000.0,0.001);
  Pcalc(xonly,llim,hlim,inxvec,Pvec,xylength,&idxstart,&idxstop);
  /*calculate probability distribution as a function of t for each energy value */
  tyval[0]=Imat[0][0]; 
  //printf("outntvals %i\n",ntvals); 
  //printf("%g \n",tyval[0]); 
  for(idx1=0;idx1<nEvals;idx1++){
      for(idx2=0;idx2<ntvals;idx2++){
        //printf("idx2 %d idx1 %d tyval: %g\n",idx2,idx1,Imat[idx2][idx1]);
        tyval[idx2]=Imat[idx2][idx1];
        txval[idx2]=tcol[idx2];        
      }
      tPcalc(txonly,ltlim,htlim,tcol,tPvec,ntvals,&tidxstart,&tidxstop);
      for(idx2=0;idx2<ntvals;idx2++){
        Ptmat[idx2][idx1]=tPvec[idx2];
      }   
   }
  /* Generate min and max Prob values corresponding to specified energy window*/ 
    /* use quadratic interpolation  */
   EPmax=quadfuncint(Emax/1000.0,xylength,inxvec,Pvec);
   EPmin=quadfuncint(Emin/1000.0,xylength,inxvec,Pvec);
  /* Calculate solid Angle */
  p_in = xw*yh/(dist*dist);
  for(idx1=0;idx1<200;idx1++){
    free(Imat[idx1]);
  }
  free(Imat);
printf("Finished calculating probability distribution\n");

}
#line 14336 "SEQ_11_09_2009.c"
#undef Emax
#undef Emin
#undef yh
#undef xw
#undef dist
#undef height
#undef width
#undef p_in
#undef vdiv
#undef hdiv
#undef S_filename
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component core_ves. */
  SIG_MESSAGE("core_ves (Init)");
#line 143 "SEQ_11_09_2009.instr"
  mcccore_ves_w1 = 0.094285;
#line 143 "SEQ_11_09_2009.instr"
  mcccore_ves_h1 = 0.11323;
#line 143 "SEQ_11_09_2009.instr"
  mcccore_ves_w2 = 0.084684;
#line 143 "SEQ_11_09_2009.instr"
  mcccore_ves_h2 = 0.102362;
#line 143 "SEQ_11_09_2009.instr"
  mcccore_ves_l = 1.2444;
#line 144 "SEQ_11_09_2009.instr"
  mcccore_ves_R0 = 0.0;
#line 144 "SEQ_11_09_2009.instr"
  mcccore_ves_Qcx = Gu_Qc;
#line 144 "SEQ_11_09_2009.instr"
  mcccore_ves_Qcy = Gu_Qc;
#line 145 "SEQ_11_09_2009.instr"
  mcccore_ves_alphax = Gu_alpha;
#line 145 "SEQ_11_09_2009.instr"
  mcccore_ves_alphay = Gu_alpha;
#line 145 "SEQ_11_09_2009.instr"
  mcccore_ves_W = Gu_W;
#line 145 "SEQ_11_09_2009.instr"
  mcccore_ves_k = 1;
#line 145 "SEQ_11_09_2009.instr"
  mcccore_ves_d = 0.0;
#line 144 "SEQ_11_09_2009.instr"
  mcccore_ves_mx = Gu_m;
#line 144 "SEQ_11_09_2009.instr"
  mcccore_ves_my = Gu_m;
#line 14384 "SEQ_11_09_2009.c"

#define mccompcurname  core_ves
#define mccompcurtype  Channeled_guide
#define mccompcurindex 3
#define w1c mcccore_ves_w1c
#define w2c mcccore_ves_w2c
#define ww mcccore_ves_ww
#define hh mcccore_ves_hh
#define whalf mcccore_ves_whalf
#define hhalf mcccore_ves_hhalf
#define lwhalf mcccore_ves_lwhalf
#define lhhalf mcccore_ves_lhhalf
#define w1 mcccore_ves_w1
#define h1 mcccore_ves_h1
#define w2 mcccore_ves_w2
#define h2 mcccore_ves_h2
#define l mcccore_ves_l
#define R0 mcccore_ves_R0
#define Qcx mcccore_ves_Qcx
#define Qcy mcccore_ves_Qcy
#define alphax mcccore_ves_alphax
#define alphay mcccore_ves_alphay
#define W mcccore_ves_W
#define k mcccore_ves_k
#define d mcccore_ves_d
#define mx mcccore_ves_mx
#define my mcccore_ves_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 14435 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component shutter_guide. */
  SIG_MESSAGE("shutter_guide (Init)");
#line 147 "SEQ_11_09_2009.instr"
  mccshutter_guide_w1 = ws;
#line 147 "SEQ_11_09_2009.instr"
  mccshutter_guide_h1 = hs;
#line 147 "SEQ_11_09_2009.instr"
  mccshutter_guide_w2 = sh_end_w;
#line 147 "SEQ_11_09_2009.instr"
  mccshutter_guide_h2 = sh_end_h;
#line 148 "SEQ_11_09_2009.instr"
  mccshutter_guide_l = 1.83743;
#line 149 "SEQ_11_09_2009.instr"
  mccshutter_guide_R0 = Gu_R;
#line 149 "SEQ_11_09_2009.instr"
  mccshutter_guide_Qcx = Gu_Qc;
#line 149 "SEQ_11_09_2009.instr"
  mccshutter_guide_Qcy = Gu_Qc;
#line 150 "SEQ_11_09_2009.instr"
  mccshutter_guide_alphax = Gu_alpha;
#line 150 "SEQ_11_09_2009.instr"
  mccshutter_guide_alphay = Gu_alpha;
#line 150 "SEQ_11_09_2009.instr"
  mccshutter_guide_W = Gu_W;
#line 150 "SEQ_11_09_2009.instr"
  mccshutter_guide_k = 1;
#line 150 "SEQ_11_09_2009.instr"
  mccshutter_guide_d = 0.0;
#line 149 "SEQ_11_09_2009.instr"
  mccshutter_guide_mx = 2.5;
#line 149 "SEQ_11_09_2009.instr"
  mccshutter_guide_my = 2.5;
#line 14495 "SEQ_11_09_2009.c"

#define mccompcurname  shutter_guide
#define mccompcurtype  Channeled_guide
#define mccompcurindex 4
#define w1c mccshutter_guide_w1c
#define w2c mccshutter_guide_w2c
#define ww mccshutter_guide_ww
#define hh mccshutter_guide_hh
#define whalf mccshutter_guide_whalf
#define hhalf mccshutter_guide_hhalf
#define lwhalf mccshutter_guide_lwhalf
#define lhhalf mccshutter_guide_lhhalf
#define w1 mccshutter_guide_w1
#define h1 mccshutter_guide_h1
#define w2 mccshutter_guide_w2
#define h2 mccshutter_guide_h2
#define l mccshutter_guide_l
#define R0 mccshutter_guide_R0
#define Qcx mccshutter_guide_Qcx
#define Qcy mccshutter_guide_Qcy
#define alphax mccshutter_guide_alphax
#define alphay mccshutter_guide_alphay
#define W mccshutter_guide_W
#define k mccshutter_guide_k
#define d mccshutter_guide_d
#define mx mccshutter_guide_mx
#define my mccshutter_guide_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 14546 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide1. */
  SIG_MESSAGE("guide1 (Init)");
#line 154 "SEQ_11_09_2009.instr"
  mccguide1_w1 = 0.0794;
#line 154 "SEQ_11_09_2009.instr"
  mccguide1_h1 = 0.09456;
#line 154 "SEQ_11_09_2009.instr"
  mccguide1_w2 = 0.07898;
#line 154 "SEQ_11_09_2009.instr"
  mccguide1_h2 = 0.09398;
#line 155 "SEQ_11_09_2009.instr"
  mccguide1_l = 0.482;
#line 155 "SEQ_11_09_2009.instr"
  mccguide1_R0 = Gu_R;
#line 155 "SEQ_11_09_2009.instr"
  mccguide1_Qcx = Gu_Qc;
#line 155 "SEQ_11_09_2009.instr"
  mccguide1_Qcy = Gu_Qc;
#line 156 "SEQ_11_09_2009.instr"
  mccguide1_alphax = Gu_alpha;
#line 156 "SEQ_11_09_2009.instr"
  mccguide1_alphay = Gu_alpha;
#line 156 "SEQ_11_09_2009.instr"
  mccguide1_W = Gu_W;
#line 156 "SEQ_11_09_2009.instr"
  mccguide1_k = 1;
#line 156 "SEQ_11_09_2009.instr"
  mccguide1_d = 0;
#line 155 "SEQ_11_09_2009.instr"
  mccguide1_mx = Gu_m2;
#line 155 "SEQ_11_09_2009.instr"
  mccguide1_my = Gu_m2;
#line 14606 "SEQ_11_09_2009.c"

#define mccompcurname  guide1
#define mccompcurtype  Channeled_guide
#define mccompcurindex 5
#define w1c mccguide1_w1c
#define w2c mccguide1_w2c
#define ww mccguide1_ww
#define hh mccguide1_hh
#define whalf mccguide1_whalf
#define hhalf mccguide1_hhalf
#define lwhalf mccguide1_lwhalf
#define lhhalf mccguide1_lhhalf
#define w1 mccguide1_w1
#define h1 mccguide1_h1
#define w2 mccguide1_w2
#define h2 mccguide1_h2
#define l mccguide1_l
#define R0 mccguide1_R0
#define Qcx mccguide1_Qcx
#define Qcy mccguide1_Qcy
#define alphax mccguide1_alphax
#define alphay mccguide1_alphay
#define W mccguide1_W
#define k mccguide1_k
#define d mccguide1_d
#define mx mccguide1_mx
#define my mccguide1_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 14657 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide2. */
  SIG_MESSAGE("guide2 (Init)");
#line 158 "SEQ_11_09_2009.instr"
  mccguide2_w1 = 0.07898;
#line 158 "SEQ_11_09_2009.instr"
  mccguide2_h1 = 0.09398;
#line 158 "SEQ_11_09_2009.instr"
  mccguide2_w2 = 0.07854;
#line 158 "SEQ_11_09_2009.instr"
  mccguide2_h2 = 0.09337;
#line 159 "SEQ_11_09_2009.instr"
  mccguide2_l = 0.482;
#line 159 "SEQ_11_09_2009.instr"
  mccguide2_R0 = Gu_R;
#line 159 "SEQ_11_09_2009.instr"
  mccguide2_Qcx = Gu_Qc;
#line 159 "SEQ_11_09_2009.instr"
  mccguide2_Qcy = Gu_Qc;
#line 160 "SEQ_11_09_2009.instr"
  mccguide2_alphax = Gu_alpha;
#line 160 "SEQ_11_09_2009.instr"
  mccguide2_alphay = Gu_alpha;
#line 160 "SEQ_11_09_2009.instr"
  mccguide2_W = Gu_W;
#line 160 "SEQ_11_09_2009.instr"
  mccguide2_k = 1;
#line 160 "SEQ_11_09_2009.instr"
  mccguide2_d = 0;
#line 159 "SEQ_11_09_2009.instr"
  mccguide2_mx = Gu_m2;
#line 159 "SEQ_11_09_2009.instr"
  mccguide2_my = Gu_m2;
#line 14717 "SEQ_11_09_2009.c"

#define mccompcurname  guide2
#define mccompcurtype  Channeled_guide
#define mccompcurindex 6
#define w1c mccguide2_w1c
#define w2c mccguide2_w2c
#define ww mccguide2_ww
#define hh mccguide2_hh
#define whalf mccguide2_whalf
#define hhalf mccguide2_hhalf
#define lwhalf mccguide2_lwhalf
#define lhhalf mccguide2_lhhalf
#define w1 mccguide2_w1
#define h1 mccguide2_h1
#define w2 mccguide2_w2
#define h2 mccguide2_h2
#define l mccguide2_l
#define R0 mccguide2_R0
#define Qcx mccguide2_Qcx
#define Qcy mccguide2_Qcy
#define alphax mccguide2_alphax
#define alphay mccguide2_alphay
#define W mccguide2_W
#define k mccguide2_k
#define d mccguide2_d
#define mx mccguide2_mx
#define my mccguide2_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 14768 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide3. */
  SIG_MESSAGE("guide3 (Init)");
#line 162 "SEQ_11_09_2009.instr"
  mccguide3_w1 = 0.07854;
#line 162 "SEQ_11_09_2009.instr"
  mccguide3_h1 = 0.09337;
#line 162 "SEQ_11_09_2009.instr"
  mccguide3_w2 = 0.07807;
#line 162 "SEQ_11_09_2009.instr"
  mccguide3_h2 = 0.09274;
#line 163 "SEQ_11_09_2009.instr"
  mccguide3_l = 0.482;
#line 163 "SEQ_11_09_2009.instr"
  mccguide3_R0 = Gu_R;
#line 163 "SEQ_11_09_2009.instr"
  mccguide3_Qcx = Gu_Qc;
#line 163 "SEQ_11_09_2009.instr"
  mccguide3_Qcy = Gu_Qc;
#line 164 "SEQ_11_09_2009.instr"
  mccguide3_alphax = Gu_alpha;
#line 164 "SEQ_11_09_2009.instr"
  mccguide3_alphay = Gu_alpha;
#line 164 "SEQ_11_09_2009.instr"
  mccguide3_W = Gu_W;
#line 164 "SEQ_11_09_2009.instr"
  mccguide3_k = 1;
#line 164 "SEQ_11_09_2009.instr"
  mccguide3_d = 0;
#line 163 "SEQ_11_09_2009.instr"
  mccguide3_mx = Gu_m2;
#line 163 "SEQ_11_09_2009.instr"
  mccguide3_my = Gu_m2;
#line 14828 "SEQ_11_09_2009.c"

#define mccompcurname  guide3
#define mccompcurtype  Channeled_guide
#define mccompcurindex 7
#define w1c mccguide3_w1c
#define w2c mccguide3_w2c
#define ww mccguide3_ww
#define hh mccguide3_hh
#define whalf mccguide3_whalf
#define hhalf mccguide3_hhalf
#define lwhalf mccguide3_lwhalf
#define lhhalf mccguide3_lhhalf
#define w1 mccguide3_w1
#define h1 mccguide3_h1
#define w2 mccguide3_w2
#define h2 mccguide3_h2
#define l mccguide3_l
#define R0 mccguide3_R0
#define Qcx mccguide3_Qcx
#define Qcy mccguide3_Qcy
#define alphax mccguide3_alphax
#define alphay mccguide3_alphay
#define W mccguide3_W
#define k mccguide3_k
#define d mccguide3_d
#define mx mccguide3_mx
#define my mccguide3_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 14879 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide4. */
  SIG_MESSAGE("guide4 (Init)");
#line 166 "SEQ_11_09_2009.instr"
  mccguide4_w1 = 0.07807;
#line 166 "SEQ_11_09_2009.instr"
  mccguide4_h1 = 0.09274;
#line 166 "SEQ_11_09_2009.instr"
  mccguide4_w2 = 0.07758;
#line 166 "SEQ_11_09_2009.instr"
  mccguide4_h2 = 0.09207;
#line 167 "SEQ_11_09_2009.instr"
  mccguide4_l = 0.482;
#line 167 "SEQ_11_09_2009.instr"
  mccguide4_R0 = Gu_R;
#line 167 "SEQ_11_09_2009.instr"
  mccguide4_Qcx = Gu_Qc;
#line 167 "SEQ_11_09_2009.instr"
  mccguide4_Qcy = Gu_Qc;
#line 168 "SEQ_11_09_2009.instr"
  mccguide4_alphax = Gu_alpha;
#line 168 "SEQ_11_09_2009.instr"
  mccguide4_alphay = Gu_alpha;
#line 168 "SEQ_11_09_2009.instr"
  mccguide4_W = Gu_W;
#line 168 "SEQ_11_09_2009.instr"
  mccguide4_k = 1;
#line 168 "SEQ_11_09_2009.instr"
  mccguide4_d = 0;
#line 167 "SEQ_11_09_2009.instr"
  mccguide4_mx = Gu_m2;
#line 167 "SEQ_11_09_2009.instr"
  mccguide4_my = Gu_m2;
#line 14939 "SEQ_11_09_2009.c"

#define mccompcurname  guide4
#define mccompcurtype  Channeled_guide
#define mccompcurindex 8
#define w1c mccguide4_w1c
#define w2c mccguide4_w2c
#define ww mccguide4_ww
#define hh mccguide4_hh
#define whalf mccguide4_whalf
#define hhalf mccguide4_hhalf
#define lwhalf mccguide4_lwhalf
#define lhhalf mccguide4_lhhalf
#define w1 mccguide4_w1
#define h1 mccguide4_h1
#define w2 mccguide4_w2
#define h2 mccguide4_h2
#define l mccguide4_l
#define R0 mccguide4_R0
#define Qcx mccguide4_Qcx
#define Qcy mccguide4_Qcy
#define alphax mccguide4_alphax
#define alphay mccguide4_alphay
#define W mccguide4_W
#define k mccguide4_k
#define d mccguide4_d
#define mx mccguide4_mx
#define my mccguide4_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 14990 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide5. */
  SIG_MESSAGE("guide5 (Init)");
#line 170 "SEQ_11_09_2009.instr"
  mccguide5_w1 = 0.07758;
#line 170 "SEQ_11_09_2009.instr"
  mccguide5_h1 = 0.09207;
#line 170 "SEQ_11_09_2009.instr"
  mccguide5_w2 = 0.07707;
#line 170 "SEQ_11_09_2009.instr"
  mccguide5_h2 = 0.09137;
#line 171 "SEQ_11_09_2009.instr"
  mccguide5_l = 0.482;
#line 171 "SEQ_11_09_2009.instr"
  mccguide5_R0 = Gu_R;
#line 171 "SEQ_11_09_2009.instr"
  mccguide5_Qcx = Gu_Qc;
#line 171 "SEQ_11_09_2009.instr"
  mccguide5_Qcy = Gu_Qc;
#line 172 "SEQ_11_09_2009.instr"
  mccguide5_alphax = Gu_alpha;
#line 172 "SEQ_11_09_2009.instr"
  mccguide5_alphay = Gu_alpha;
#line 172 "SEQ_11_09_2009.instr"
  mccguide5_W = Gu_W;
#line 172 "SEQ_11_09_2009.instr"
  mccguide5_k = 1;
#line 172 "SEQ_11_09_2009.instr"
  mccguide5_d = 0;
#line 171 "SEQ_11_09_2009.instr"
  mccguide5_mx = Gu_m2;
#line 171 "SEQ_11_09_2009.instr"
  mccguide5_my = Gu_m2;
#line 15050 "SEQ_11_09_2009.c"

#define mccompcurname  guide5
#define mccompcurtype  Channeled_guide
#define mccompcurindex 9
#define w1c mccguide5_w1c
#define w2c mccguide5_w2c
#define ww mccguide5_ww
#define hh mccguide5_hh
#define whalf mccguide5_whalf
#define hhalf mccguide5_hhalf
#define lwhalf mccguide5_lwhalf
#define lhhalf mccguide5_lhhalf
#define w1 mccguide5_w1
#define h1 mccguide5_h1
#define w2 mccguide5_w2
#define h2 mccguide5_h2
#define l mccguide5_l
#define R0 mccguide5_R0
#define Qcx mccguide5_Qcx
#define Qcy mccguide5_Qcy
#define alphax mccguide5_alphax
#define alphay mccguide5_alphay
#define W mccguide5_W
#define k mccguide5_k
#define d mccguide5_d
#define mx mccguide5_mx
#define my mccguide5_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15101 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide6. */
  SIG_MESSAGE("guide6 (Init)");
#line 174 "SEQ_11_09_2009.instr"
  mccguide6_w1 = 0.07707;
#line 174 "SEQ_11_09_2009.instr"
  mccguide6_h1 = 0.09137;
#line 174 "SEQ_11_09_2009.instr"
  mccguide6_w2 = 0.07653;
#line 174 "SEQ_11_09_2009.instr"
  mccguide6_h2 = 0.09064;
#line 175 "SEQ_11_09_2009.instr"
  mccguide6_l = 0.482;
#line 175 "SEQ_11_09_2009.instr"
  mccguide6_R0 = Gu_R;
#line 175 "SEQ_11_09_2009.instr"
  mccguide6_Qcx = Gu_Qc;
#line 175 "SEQ_11_09_2009.instr"
  mccguide6_Qcy = Gu_Qc;
#line 176 "SEQ_11_09_2009.instr"
  mccguide6_alphax = Gu_alpha;
#line 176 "SEQ_11_09_2009.instr"
  mccguide6_alphay = Gu_alpha;
#line 176 "SEQ_11_09_2009.instr"
  mccguide6_W = Gu_W;
#line 176 "SEQ_11_09_2009.instr"
  mccguide6_k = 1;
#line 176 "SEQ_11_09_2009.instr"
  mccguide6_d = 0;
#line 175 "SEQ_11_09_2009.instr"
  mccguide6_mx = Gu_m2;
#line 175 "SEQ_11_09_2009.instr"
  mccguide6_my = Gu_m2;
#line 15161 "SEQ_11_09_2009.c"

#define mccompcurname  guide6
#define mccompcurtype  Channeled_guide
#define mccompcurindex 10
#define w1c mccguide6_w1c
#define w2c mccguide6_w2c
#define ww mccguide6_ww
#define hh mccguide6_hh
#define whalf mccguide6_whalf
#define hhalf mccguide6_hhalf
#define lwhalf mccguide6_lwhalf
#define lhhalf mccguide6_lhhalf
#define w1 mccguide6_w1
#define h1 mccguide6_h1
#define w2 mccguide6_w2
#define h2 mccguide6_h2
#define l mccguide6_l
#define R0 mccguide6_R0
#define Qcx mccguide6_Qcx
#define Qcy mccguide6_Qcy
#define alphax mccguide6_alphax
#define alphay mccguide6_alphay
#define W mccguide6_W
#define k mccguide6_k
#define d mccguide6_d
#define mx mccguide6_mx
#define my mccguide6_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15212 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide7. */
  SIG_MESSAGE("guide7 (Init)");
#line 178 "SEQ_11_09_2009.instr"
  mccguide7_w1 = 0.07653;
#line 178 "SEQ_11_09_2009.instr"
  mccguide7_h1 = 0.09064;
#line 178 "SEQ_11_09_2009.instr"
  mccguide7_w2 = 0.07597;
#line 178 "SEQ_11_09_2009.instr"
  mccguide7_h2 = 0.08988;
#line 179 "SEQ_11_09_2009.instr"
  mccguide7_l = 0.482;
#line 179 "SEQ_11_09_2009.instr"
  mccguide7_R0 = Gu_R;
#line 179 "SEQ_11_09_2009.instr"
  mccguide7_Qcx = Gu_Qc;
#line 179 "SEQ_11_09_2009.instr"
  mccguide7_Qcy = Gu_Qc;
#line 180 "SEQ_11_09_2009.instr"
  mccguide7_alphax = Gu_alpha;
#line 180 "SEQ_11_09_2009.instr"
  mccguide7_alphay = Gu_alpha;
#line 180 "SEQ_11_09_2009.instr"
  mccguide7_W = Gu_W;
#line 180 "SEQ_11_09_2009.instr"
  mccguide7_k = 1;
#line 180 "SEQ_11_09_2009.instr"
  mccguide7_d = 0;
#line 179 "SEQ_11_09_2009.instr"
  mccguide7_mx = Gu_m2;
#line 179 "SEQ_11_09_2009.instr"
  mccguide7_my = Gu_m2;
#line 15272 "SEQ_11_09_2009.c"

#define mccompcurname  guide7
#define mccompcurtype  Channeled_guide
#define mccompcurindex 11
#define w1c mccguide7_w1c
#define w2c mccguide7_w2c
#define ww mccguide7_ww
#define hh mccguide7_hh
#define whalf mccguide7_whalf
#define hhalf mccguide7_hhalf
#define lwhalf mccguide7_lwhalf
#define lhhalf mccguide7_lhhalf
#define w1 mccguide7_w1
#define h1 mccguide7_h1
#define w2 mccguide7_w2
#define h2 mccguide7_h2
#define l mccguide7_l
#define R0 mccguide7_R0
#define Qcx mccguide7_Qcx
#define Qcy mccguide7_Qcy
#define alphax mccguide7_alphax
#define alphay mccguide7_alphay
#define W mccguide7_W
#define k mccguide7_k
#define d mccguide7_d
#define mx mccguide7_mx
#define my mccguide7_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15323 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide8. */
  SIG_MESSAGE("guide8 (Init)");
#line 182 "SEQ_11_09_2009.instr"
  mccguide8_w1 = 0.07597;
#line 182 "SEQ_11_09_2009.instr"
  mccguide8_h1 = 0.08988;
#line 182 "SEQ_11_09_2009.instr"
  mccguide8_w2 = 0.07538;
#line 182 "SEQ_11_09_2009.instr"
  mccguide8_h2 = 0.08908;
#line 183 "SEQ_11_09_2009.instr"
  mccguide8_l = 0.482;
#line 183 "SEQ_11_09_2009.instr"
  mccguide8_R0 = Gu_R;
#line 183 "SEQ_11_09_2009.instr"
  mccguide8_Qcx = Gu_Qc;
#line 183 "SEQ_11_09_2009.instr"
  mccguide8_Qcy = Gu_Qc;
#line 184 "SEQ_11_09_2009.instr"
  mccguide8_alphax = Gu_alpha;
#line 184 "SEQ_11_09_2009.instr"
  mccguide8_alphay = Gu_alpha;
#line 184 "SEQ_11_09_2009.instr"
  mccguide8_W = Gu_W;
#line 184 "SEQ_11_09_2009.instr"
  mccguide8_k = 1;
#line 184 "SEQ_11_09_2009.instr"
  mccguide8_d = 0;
#line 183 "SEQ_11_09_2009.instr"
  mccguide8_mx = Gu_m2;
#line 183 "SEQ_11_09_2009.instr"
  mccguide8_my = Gu_m2;
#line 15383 "SEQ_11_09_2009.c"

#define mccompcurname  guide8
#define mccompcurtype  Channeled_guide
#define mccompcurindex 12
#define w1c mccguide8_w1c
#define w2c mccguide8_w2c
#define ww mccguide8_ww
#define hh mccguide8_hh
#define whalf mccguide8_whalf
#define hhalf mccguide8_hhalf
#define lwhalf mccguide8_lwhalf
#define lhhalf mccguide8_lhhalf
#define w1 mccguide8_w1
#define h1 mccguide8_h1
#define w2 mccguide8_w2
#define h2 mccguide8_h2
#define l mccguide8_l
#define R0 mccguide8_R0
#define Qcx mccguide8_Qcx
#define Qcy mccguide8_Qcy
#define alphax mccguide8_alphax
#define alphay mccguide8_alphay
#define W mccguide8_W
#define k mccguide8_k
#define d mccguide8_d
#define mx mccguide8_mx
#define my mccguide8_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15434 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide9. */
  SIG_MESSAGE("guide9 (Init)");
#line 186 "SEQ_11_09_2009.instr"
  mccguide9_w1 = 0.07538;
#line 186 "SEQ_11_09_2009.instr"
  mccguide9_h1 = 0.08908;
#line 186 "SEQ_11_09_2009.instr"
  mccguide9_w2 = 0.07477;
#line 186 "SEQ_11_09_2009.instr"
  mccguide9_h2 = 0.08825;
#line 187 "SEQ_11_09_2009.instr"
  mccguide9_l = 0.482;
#line 187 "SEQ_11_09_2009.instr"
  mccguide9_R0 = Gu_R;
#line 187 "SEQ_11_09_2009.instr"
  mccguide9_Qcx = Gu_Qc;
#line 187 "SEQ_11_09_2009.instr"
  mccguide9_Qcy = Gu_Qc;
#line 188 "SEQ_11_09_2009.instr"
  mccguide9_alphax = Gu_alpha;
#line 188 "SEQ_11_09_2009.instr"
  mccguide9_alphay = Gu_alpha;
#line 188 "SEQ_11_09_2009.instr"
  mccguide9_W = Gu_W;
#line 188 "SEQ_11_09_2009.instr"
  mccguide9_k = 1;
#line 188 "SEQ_11_09_2009.instr"
  mccguide9_d = 0;
#line 187 "SEQ_11_09_2009.instr"
  mccguide9_mx = Gu_m;
#line 187 "SEQ_11_09_2009.instr"
  mccguide9_my = Gu_m;
#line 15494 "SEQ_11_09_2009.c"

#define mccompcurname  guide9
#define mccompcurtype  Channeled_guide
#define mccompcurindex 13
#define w1c mccguide9_w1c
#define w2c mccguide9_w2c
#define ww mccguide9_ww
#define hh mccguide9_hh
#define whalf mccguide9_whalf
#define hhalf mccguide9_hhalf
#define lwhalf mccguide9_lwhalf
#define lhhalf mccguide9_lhhalf
#define w1 mccguide9_w1
#define h1 mccguide9_h1
#define w2 mccguide9_w2
#define h2 mccguide9_h2
#define l mccguide9_l
#define R0 mccguide9_R0
#define Qcx mccguide9_Qcx
#define Qcy mccguide9_Qcy
#define alphax mccguide9_alphax
#define alphay mccguide9_alphay
#define W mccguide9_W
#define k mccguide9_k
#define d mccguide9_d
#define mx mccguide9_mx
#define my mccguide9_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15545 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide10. */
  SIG_MESSAGE("guide10 (Init)");
#line 190 "SEQ_11_09_2009.instr"
  mccguide10_w1 = 0.07477;
#line 190 "SEQ_11_09_2009.instr"
  mccguide10_h1 = 0.08825;
#line 190 "SEQ_11_09_2009.instr"
  mccguide10_w2 = 0.07413;
#line 190 "SEQ_11_09_2009.instr"
  mccguide10_h2 = 0.08738;
#line 191 "SEQ_11_09_2009.instr"
  mccguide10_l = 0.482;
#line 191 "SEQ_11_09_2009.instr"
  mccguide10_R0 = Gu_R;
#line 191 "SEQ_11_09_2009.instr"
  mccguide10_Qcx = Gu_Qc;
#line 191 "SEQ_11_09_2009.instr"
  mccguide10_Qcy = Gu_Qc;
#line 192 "SEQ_11_09_2009.instr"
  mccguide10_alphax = Gu_alpha;
#line 192 "SEQ_11_09_2009.instr"
  mccguide10_alphay = Gu_alpha;
#line 192 "SEQ_11_09_2009.instr"
  mccguide10_W = Gu_W;
#line 192 "SEQ_11_09_2009.instr"
  mccguide10_k = 1;
#line 192 "SEQ_11_09_2009.instr"
  mccguide10_d = 0;
#line 191 "SEQ_11_09_2009.instr"
  mccguide10_mx = Gu_m;
#line 191 "SEQ_11_09_2009.instr"
  mccguide10_my = Gu_m;
#line 15605 "SEQ_11_09_2009.c"

#define mccompcurname  guide10
#define mccompcurtype  Channeled_guide
#define mccompcurindex 14
#define w1c mccguide10_w1c
#define w2c mccguide10_w2c
#define ww mccguide10_ww
#define hh mccguide10_hh
#define whalf mccguide10_whalf
#define hhalf mccguide10_hhalf
#define lwhalf mccguide10_lwhalf
#define lhhalf mccguide10_lhhalf
#define w1 mccguide10_w1
#define h1 mccguide10_h1
#define w2 mccguide10_w2
#define h2 mccguide10_h2
#define l mccguide10_l
#define R0 mccguide10_R0
#define Qcx mccguide10_Qcx
#define Qcy mccguide10_Qcy
#define alphax mccguide10_alphax
#define alphay mccguide10_alphay
#define W mccguide10_W
#define k mccguide10_k
#define d mccguide10_d
#define mx mccguide10_mx
#define my mccguide10_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15656 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide11. */
  SIG_MESSAGE("guide11 (Init)");
#line 194 "SEQ_11_09_2009.instr"
  mccguide11_w1 = 0.07413;
#line 194 "SEQ_11_09_2009.instr"
  mccguide11_h1 = 0.08738;
#line 194 "SEQ_11_09_2009.instr"
  mccguide11_w2 = 0.07346;
#line 194 "SEQ_11_09_2009.instr"
  mccguide11_h2 = 0.08648;
#line 195 "SEQ_11_09_2009.instr"
  mccguide11_l = 0.482;
#line 195 "SEQ_11_09_2009.instr"
  mccguide11_R0 = Gu_R;
#line 195 "SEQ_11_09_2009.instr"
  mccguide11_Qcx = Gu_Qc;
#line 195 "SEQ_11_09_2009.instr"
  mccguide11_Qcy = Gu_Qc;
#line 196 "SEQ_11_09_2009.instr"
  mccguide11_alphax = Gu_alpha;
#line 196 "SEQ_11_09_2009.instr"
  mccguide11_alphay = Gu_alpha;
#line 196 "SEQ_11_09_2009.instr"
  mccguide11_W = Gu_W;
#line 196 "SEQ_11_09_2009.instr"
  mccguide11_k = 1;
#line 196 "SEQ_11_09_2009.instr"
  mccguide11_d = 0;
#line 195 "SEQ_11_09_2009.instr"
  mccguide11_mx = Gu_m;
#line 195 "SEQ_11_09_2009.instr"
  mccguide11_my = Gu_m;
#line 15716 "SEQ_11_09_2009.c"

#define mccompcurname  guide11
#define mccompcurtype  Channeled_guide
#define mccompcurindex 15
#define w1c mccguide11_w1c
#define w2c mccguide11_w2c
#define ww mccguide11_ww
#define hh mccguide11_hh
#define whalf mccguide11_whalf
#define hhalf mccguide11_hhalf
#define lwhalf mccguide11_lwhalf
#define lhhalf mccguide11_lhhalf
#define w1 mccguide11_w1
#define h1 mccguide11_h1
#define w2 mccguide11_w2
#define h2 mccguide11_h2
#define l mccguide11_l
#define R0 mccguide11_R0
#define Qcx mccguide11_Qcx
#define Qcy mccguide11_Qcy
#define alphax mccguide11_alphax
#define alphay mccguide11_alphay
#define W mccguide11_W
#define k mccguide11_k
#define d mccguide11_d
#define mx mccguide11_mx
#define my mccguide11_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15767 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component t0_chopp. */
  SIG_MESSAGE("t0_chopp (Init)");

#define mccompcurname  t0_chopp
#define mccompcurtype  Vertical_T0a
#define mccompcurindex 16
#define len mcct0_chopp_len
#define w1 mcct0_chopp_w1
#define w2 mcct0_chopp_w2
#define nu mcct0_chopp_nu
#define delta mcct0_chopp_delta
#define tc mcct0_chopp_tc
#define ymin mcct0_chopp_ymin
#define ymax mcct0_chopp_ymax
#define omega mcct0_chopp_omega
#define r_blade mcct0_chopp_r_blade
#define x_width mcct0_chopp_x_width
#define nn mcct0_chopp_nn
#define tdr mcct0_chopp_tdr
#line 82 "Vertical_T0a.comp"
{
   splen=len/2.0;
   omega=2.0*PI*nu;
   rad=sqrt(w2*w2/4.0+splen*splen); //radius of cylinder containing slit package.
}
#line 15820 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w2
#undef w1
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component t_check1. */
  SIG_MESSAGE("t_check1 (Init)");
#line 203 "SEQ_11_09_2009.instr"
  mcct_check1_xmin = - T0wd2;
#line 203 "SEQ_11_09_2009.instr"
  mcct_check1_xmax = T0wd2;
#line 203 "SEQ_11_09_2009.instr"
  mcct_check1_ymin = -0.045;
#line 203 "SEQ_11_09_2009.instr"
  mcct_check1_ymax = 0.045;
#line 204 "SEQ_11_09_2009.instr"
  mcct_check1_tmin = ( tplotmin - toffset ) * z_T0 / LM1 + toffset;
#line 205 "SEQ_11_09_2009.instr"
  mcct_check1_tmax = ( tplotmax - toffset ) * z_T0 / LM1 + toffset;
#line 207 "SEQ_11_09_2009.instr"
  if(dett0optstr) strncpy(mcct_check1_filename,dett0optstr, 1024); else mcct_check1_filename[0]='\0';
#line 15854 "SEQ_11_09_2009.c"

#define mccompcurname  t_check1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 17
#define nchan mcct_check1_nchan
#define TOF_N mcct_check1_TOF_N
#define TOF_p mcct_check1_TOF_p
#define TOF_p2 mcct_check1_TOF_p2
#define xmin mcct_check1_xmin
#define xmax mcct_check1_xmax
#define ymin mcct_check1_ymin
#define ymax mcct_check1_ymax
#define tmin mcct_check1_tmin
#define tmax mcct_check1_tmax
#define filename mcct_check1_filename
#line 49 "TOF_monitor2.comp"
{
    int i;
    for (i=0; i<nchan; i++)
    {
      TOF_N[i] = 0;
      TOF_p[i] = 0;
      TOF_p2[i] = 0;
    }
}
#line 15880 "SEQ_11_09_2009.c"
#undef filename
#undef tmax
#undef tmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide13. */
  SIG_MESSAGE("guide13 (Init)");
#line 210 "SEQ_11_09_2009.instr"
  mccguide13_w1 = 0.07199;
#line 210 "SEQ_11_09_2009.instr"
  mccguide13_h1 = 0.08449;
#line 210 "SEQ_11_09_2009.instr"
  mccguide13_w2 = 0.07123;
#line 210 "SEQ_11_09_2009.instr"
  mccguide13_h2 = 0.08344;
#line 211 "SEQ_11_09_2009.instr"
  mccguide13_l = 0.492;
#line 211 "SEQ_11_09_2009.instr"
  mccguide13_R0 = Gu_R;
#line 211 "SEQ_11_09_2009.instr"
  mccguide13_Qcx = Gu_Qc;
#line 211 "SEQ_11_09_2009.instr"
  mccguide13_Qcy = Gu_Qc;
#line 212 "SEQ_11_09_2009.instr"
  mccguide13_alphax = Gu_alpha;
#line 212 "SEQ_11_09_2009.instr"
  mccguide13_alphay = Gu_alpha;
#line 212 "SEQ_11_09_2009.instr"
  mccguide13_W = Gu_W;
#line 212 "SEQ_11_09_2009.instr"
  mccguide13_k = 1;
#line 212 "SEQ_11_09_2009.instr"
  mccguide13_d = 0;
#line 211 "SEQ_11_09_2009.instr"
  mccguide13_mx = Gu_m;
#line 211 "SEQ_11_09_2009.instr"
  mccguide13_my = Gu_m;
#line 15928 "SEQ_11_09_2009.c"

#define mccompcurname  guide13
#define mccompcurtype  Channeled_guide
#define mccompcurindex 18
#define w1c mccguide13_w1c
#define w2c mccguide13_w2c
#define ww mccguide13_ww
#define hh mccguide13_hh
#define whalf mccguide13_whalf
#define hhalf mccguide13_hhalf
#define lwhalf mccguide13_lwhalf
#define lhhalf mccguide13_lhhalf
#define w1 mccguide13_w1
#define h1 mccguide13_h1
#define w2 mccguide13_w2
#define h2 mccguide13_h2
#define l mccguide13_l
#define R0 mccguide13_R0
#define Qcx mccguide13_Qcx
#define Qcy mccguide13_Qcy
#define alphax mccguide13_alphax
#define alphay mccguide13_alphay
#define W mccguide13_W
#define k mccguide13_k
#define d mccguide13_d
#define mx mccguide13_mx
#define my mccguide13_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 15979 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide14. */
  SIG_MESSAGE("guide14 (Init)");
#line 214 "SEQ_11_09_2009.instr"
  mccguide14_w1 = 0.07123;
#line 214 "SEQ_11_09_2009.instr"
  mccguide14_h1 = 0.08344;
#line 214 "SEQ_11_09_2009.instr"
  mccguide14_w2 = 0.07042;
#line 214 "SEQ_11_09_2009.instr"
  mccguide14_h2 = 0.08235;
#line 215 "SEQ_11_09_2009.instr"
  mccguide14_l = 0.492;
#line 215 "SEQ_11_09_2009.instr"
  mccguide14_R0 = Gu_R;
#line 215 "SEQ_11_09_2009.instr"
  mccguide14_Qcx = Gu_Qc;
#line 215 "SEQ_11_09_2009.instr"
  mccguide14_Qcy = Gu_Qc;
#line 216 "SEQ_11_09_2009.instr"
  mccguide14_alphax = Gu_alpha;
#line 216 "SEQ_11_09_2009.instr"
  mccguide14_alphay = Gu_alpha;
#line 216 "SEQ_11_09_2009.instr"
  mccguide14_W = Gu_W;
#line 216 "SEQ_11_09_2009.instr"
  mccguide14_k = 1;
#line 216 "SEQ_11_09_2009.instr"
  mccguide14_d = 0;
#line 215 "SEQ_11_09_2009.instr"
  mccguide14_mx = Gu_m;
#line 215 "SEQ_11_09_2009.instr"
  mccguide14_my = Gu_m;
#line 16039 "SEQ_11_09_2009.c"

#define mccompcurname  guide14
#define mccompcurtype  Channeled_guide
#define mccompcurindex 19
#define w1c mccguide14_w1c
#define w2c mccguide14_w2c
#define ww mccguide14_ww
#define hh mccguide14_hh
#define whalf mccguide14_whalf
#define hhalf mccguide14_hhalf
#define lwhalf mccguide14_lwhalf
#define lhhalf mccguide14_lhhalf
#define w1 mccguide14_w1
#define h1 mccguide14_h1
#define w2 mccguide14_w2
#define h2 mccguide14_h2
#define l mccguide14_l
#define R0 mccguide14_R0
#define Qcx mccguide14_Qcx
#define Qcy mccguide14_Qcy
#define alphax mccguide14_alphax
#define alphay mccguide14_alphay
#define W mccguide14_W
#define k mccguide14_k
#define d mccguide14_d
#define mx mccguide14_mx
#define my mccguide14_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16090 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide15. */
  SIG_MESSAGE("guide15 (Init)");
#line 218 "SEQ_11_09_2009.instr"
  mccguide15_w1 = 0.07042;
#line 218 "SEQ_11_09_2009.instr"
  mccguide15_h1 = 0.08235;
#line 218 "SEQ_11_09_2009.instr"
  mccguide15_w2 = 0.06959;
#line 218 "SEQ_11_09_2009.instr"
  mccguide15_h2 = 0.08122;
#line 219 "SEQ_11_09_2009.instr"
  mccguide15_l = 0.492;
#line 219 "SEQ_11_09_2009.instr"
  mccguide15_R0 = Gu_R;
#line 219 "SEQ_11_09_2009.instr"
  mccguide15_Qcx = Gu_Qc;
#line 219 "SEQ_11_09_2009.instr"
  mccguide15_Qcy = Gu_Qc;
#line 220 "SEQ_11_09_2009.instr"
  mccguide15_alphax = Gu_alpha;
#line 220 "SEQ_11_09_2009.instr"
  mccguide15_alphay = Gu_alpha;
#line 220 "SEQ_11_09_2009.instr"
  mccguide15_W = Gu_W;
#line 220 "SEQ_11_09_2009.instr"
  mccguide15_k = 1;
#line 220 "SEQ_11_09_2009.instr"
  mccguide15_d = 0;
#line 219 "SEQ_11_09_2009.instr"
  mccguide15_mx = Gu_m;
#line 219 "SEQ_11_09_2009.instr"
  mccguide15_my = Gu_m;
#line 16150 "SEQ_11_09_2009.c"

#define mccompcurname  guide15
#define mccompcurtype  Channeled_guide
#define mccompcurindex 20
#define w1c mccguide15_w1c
#define w2c mccguide15_w2c
#define ww mccguide15_ww
#define hh mccguide15_hh
#define whalf mccguide15_whalf
#define hhalf mccguide15_hhalf
#define lwhalf mccguide15_lwhalf
#define lhhalf mccguide15_lhhalf
#define w1 mccguide15_w1
#define h1 mccguide15_h1
#define w2 mccguide15_w2
#define h2 mccguide15_h2
#define l mccguide15_l
#define R0 mccguide15_R0
#define Qcx mccguide15_Qcx
#define Qcy mccguide15_Qcy
#define alphax mccguide15_alphax
#define alphay mccguide15_alphay
#define W mccguide15_W
#define k mccguide15_k
#define d mccguide15_d
#define mx mccguide15_mx
#define my mccguide15_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16201 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide16. */
  SIG_MESSAGE("guide16 (Init)");
#line 222 "SEQ_11_09_2009.instr"
  mccguide16_w1 = 0.06959;
#line 222 "SEQ_11_09_2009.instr"
  mccguide16_h1 = 0.08122;
#line 222 "SEQ_11_09_2009.instr"
  mccguide16_w2 = 0.06872;
#line 222 "SEQ_11_09_2009.instr"
  mccguide16_h2 = 0.08004;
#line 223 "SEQ_11_09_2009.instr"
  mccguide16_l = 0.492;
#line 223 "SEQ_11_09_2009.instr"
  mccguide16_R0 = Gu_R;
#line 223 "SEQ_11_09_2009.instr"
  mccguide16_Qcx = Gu_Qc;
#line 223 "SEQ_11_09_2009.instr"
  mccguide16_Qcy = Gu_Qc;
#line 224 "SEQ_11_09_2009.instr"
  mccguide16_alphax = Gu_alpha;
#line 224 "SEQ_11_09_2009.instr"
  mccguide16_alphay = Gu_alpha;
#line 224 "SEQ_11_09_2009.instr"
  mccguide16_W = Gu_W;
#line 224 "SEQ_11_09_2009.instr"
  mccguide16_k = 1;
#line 224 "SEQ_11_09_2009.instr"
  mccguide16_d = 0;
#line 223 "SEQ_11_09_2009.instr"
  mccguide16_mx = Gu_m;
#line 223 "SEQ_11_09_2009.instr"
  mccguide16_my = Gu_m;
#line 16261 "SEQ_11_09_2009.c"

#define mccompcurname  guide16
#define mccompcurtype  Channeled_guide
#define mccompcurindex 21
#define w1c mccguide16_w1c
#define w2c mccguide16_w2c
#define ww mccguide16_ww
#define hh mccguide16_hh
#define whalf mccguide16_whalf
#define hhalf mccguide16_hhalf
#define lwhalf mccguide16_lwhalf
#define lhhalf mccguide16_lhhalf
#define w1 mccguide16_w1
#define h1 mccguide16_h1
#define w2 mccguide16_w2
#define h2 mccguide16_h2
#define l mccguide16_l
#define R0 mccguide16_R0
#define Qcx mccguide16_Qcx
#define Qcy mccguide16_Qcy
#define alphax mccguide16_alphax
#define alphay mccguide16_alphay
#define W mccguide16_W
#define k mccguide16_k
#define d mccguide16_d
#define mx mccguide16_mx
#define my mccguide16_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16312 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide17. */
  SIG_MESSAGE("guide17 (Init)");
#line 226 "SEQ_11_09_2009.instr"
  mccguide17_w1 = 0.06872;
#line 226 "SEQ_11_09_2009.instr"
  mccguide17_h1 = 0.08004;
#line 226 "SEQ_11_09_2009.instr"
  mccguide17_w2 = 0.06782;
#line 226 "SEQ_11_09_2009.instr"
  mccguide17_h2 = 0.07881;
#line 227 "SEQ_11_09_2009.instr"
  mccguide17_l = 0.492;
#line 227 "SEQ_11_09_2009.instr"
  mccguide17_R0 = Gu_R;
#line 227 "SEQ_11_09_2009.instr"
  mccguide17_Qcx = Gu_Qc;
#line 227 "SEQ_11_09_2009.instr"
  mccguide17_Qcy = Gu_Qc;
#line 228 "SEQ_11_09_2009.instr"
  mccguide17_alphax = Gu_alpha;
#line 228 "SEQ_11_09_2009.instr"
  mccguide17_alphay = Gu_alpha;
#line 228 "SEQ_11_09_2009.instr"
  mccguide17_W = Gu_W;
#line 228 "SEQ_11_09_2009.instr"
  mccguide17_k = 1;
#line 228 "SEQ_11_09_2009.instr"
  mccguide17_d = 0;
#line 227 "SEQ_11_09_2009.instr"
  mccguide17_mx = Gu_m;
#line 227 "SEQ_11_09_2009.instr"
  mccguide17_my = Gu_m;
#line 16372 "SEQ_11_09_2009.c"

#define mccompcurname  guide17
#define mccompcurtype  Channeled_guide
#define mccompcurindex 22
#define w1c mccguide17_w1c
#define w2c mccguide17_w2c
#define ww mccguide17_ww
#define hh mccguide17_hh
#define whalf mccguide17_whalf
#define hhalf mccguide17_hhalf
#define lwhalf mccguide17_lwhalf
#define lhhalf mccguide17_lhhalf
#define w1 mccguide17_w1
#define h1 mccguide17_h1
#define w2 mccguide17_w2
#define h2 mccguide17_h2
#define l mccguide17_l
#define R0 mccguide17_R0
#define Qcx mccguide17_Qcx
#define Qcy mccguide17_Qcy
#define alphax mccguide17_alphax
#define alphay mccguide17_alphay
#define W mccguide17_W
#define k mccguide17_k
#define d mccguide17_d
#define mx mccguide17_mx
#define my mccguide17_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16423 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide18. */
  SIG_MESSAGE("guide18 (Init)");
#line 230 "SEQ_11_09_2009.instr"
  mccguide18_w1 = 0.06782;
#line 230 "SEQ_11_09_2009.instr"
  mccguide18_h1 = 0.07881;
#line 230 "SEQ_11_09_2009.instr"
  mccguide18_w2 = 0.06688;
#line 230 "SEQ_11_09_2009.instr"
  mccguide18_h2 = 0.07753;
#line 231 "SEQ_11_09_2009.instr"
  mccguide18_l = 0.492;
#line 231 "SEQ_11_09_2009.instr"
  mccguide18_R0 = Gu_R;
#line 231 "SEQ_11_09_2009.instr"
  mccguide18_Qcx = Gu_Qc;
#line 231 "SEQ_11_09_2009.instr"
  mccguide18_Qcy = Gu_Qc;
#line 232 "SEQ_11_09_2009.instr"
  mccguide18_alphax = Gu_alpha;
#line 232 "SEQ_11_09_2009.instr"
  mccguide18_alphay = Gu_alpha;
#line 232 "SEQ_11_09_2009.instr"
  mccguide18_W = Gu_W;
#line 232 "SEQ_11_09_2009.instr"
  mccguide18_k = 1;
#line 232 "SEQ_11_09_2009.instr"
  mccguide18_d = 0;
#line 231 "SEQ_11_09_2009.instr"
  mccguide18_mx = Gu_m;
#line 231 "SEQ_11_09_2009.instr"
  mccguide18_my = Gu_m;
#line 16483 "SEQ_11_09_2009.c"

#define mccompcurname  guide18
#define mccompcurtype  Channeled_guide
#define mccompcurindex 23
#define w1c mccguide18_w1c
#define w2c mccguide18_w2c
#define ww mccguide18_ww
#define hh mccguide18_hh
#define whalf mccguide18_whalf
#define hhalf mccguide18_hhalf
#define lwhalf mccguide18_lwhalf
#define lhhalf mccguide18_lhhalf
#define w1 mccguide18_w1
#define h1 mccguide18_h1
#define w2 mccguide18_w2
#define h2 mccguide18_h2
#define l mccguide18_l
#define R0 mccguide18_R0
#define Qcx mccguide18_Qcx
#define Qcy mccguide18_Qcy
#define alphax mccguide18_alphax
#define alphay mccguide18_alphay
#define W mccguide18_W
#define k mccguide18_k
#define d mccguide18_d
#define mx mccguide18_mx
#define my mccguide18_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16534 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide19. */
  SIG_MESSAGE("guide19 (Init)");
#line 234 "SEQ_11_09_2009.instr"
  mccguide19_w1 = 0.06688;
#line 234 "SEQ_11_09_2009.instr"
  mccguide19_h1 = 0.07753;
#line 234 "SEQ_11_09_2009.instr"
  mccguide19_w2 = 0.0659;
#line 234 "SEQ_11_09_2009.instr"
  mccguide19_h2 = 0.07619;
#line 235 "SEQ_11_09_2009.instr"
  mccguide19_l = 0.492;
#line 235 "SEQ_11_09_2009.instr"
  mccguide19_R0 = Gu_R;
#line 235 "SEQ_11_09_2009.instr"
  mccguide19_Qcx = Gu_Qc;
#line 235 "SEQ_11_09_2009.instr"
  mccguide19_Qcy = Gu_Qc;
#line 236 "SEQ_11_09_2009.instr"
  mccguide19_alphax = Gu_alpha;
#line 236 "SEQ_11_09_2009.instr"
  mccguide19_alphay = Gu_alpha;
#line 236 "SEQ_11_09_2009.instr"
  mccguide19_W = Gu_W;
#line 236 "SEQ_11_09_2009.instr"
  mccguide19_k = 1;
#line 236 "SEQ_11_09_2009.instr"
  mccguide19_d = 0;
#line 235 "SEQ_11_09_2009.instr"
  mccguide19_mx = Gu_m;
#line 235 "SEQ_11_09_2009.instr"
  mccguide19_my = Gu_m;
#line 16594 "SEQ_11_09_2009.c"

#define mccompcurname  guide19
#define mccompcurtype  Channeled_guide
#define mccompcurindex 24
#define w1c mccguide19_w1c
#define w2c mccguide19_w2c
#define ww mccguide19_ww
#define hh mccguide19_hh
#define whalf mccguide19_whalf
#define hhalf mccguide19_hhalf
#define lwhalf mccguide19_lwhalf
#define lhhalf mccguide19_lhhalf
#define w1 mccguide19_w1
#define h1 mccguide19_h1
#define w2 mccguide19_w2
#define h2 mccguide19_h2
#define l mccguide19_l
#define R0 mccguide19_R0
#define Qcx mccguide19_Qcx
#define Qcy mccguide19_Qcy
#define alphax mccguide19_alphax
#define alphay mccguide19_alphay
#define W mccguide19_W
#define k mccguide19_k
#define d mccguide19_d
#define mx mccguide19_mx
#define my mccguide19_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16645 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide20. */
  SIG_MESSAGE("guide20 (Init)");
#line 238 "SEQ_11_09_2009.instr"
  mccguide20_w1 = 0.0659;
#line 238 "SEQ_11_09_2009.instr"
  mccguide20_h1 = 0.07619;
#line 238 "SEQ_11_09_2009.instr"
  mccguide20_w2 = 0.06488;
#line 238 "SEQ_11_09_2009.instr"
  mccguide20_h2 = 0.0748;
#line 239 "SEQ_11_09_2009.instr"
  mccguide20_l = 0.492;
#line 239 "SEQ_11_09_2009.instr"
  mccguide20_R0 = Gu_R;
#line 239 "SEQ_11_09_2009.instr"
  mccguide20_Qcx = Gu_Qc;
#line 239 "SEQ_11_09_2009.instr"
  mccguide20_Qcy = Gu_Qc;
#line 240 "SEQ_11_09_2009.instr"
  mccguide20_alphax = Gu_alpha;
#line 240 "SEQ_11_09_2009.instr"
  mccguide20_alphay = Gu_alpha;
#line 240 "SEQ_11_09_2009.instr"
  mccguide20_W = Gu_W;
#line 240 "SEQ_11_09_2009.instr"
  mccguide20_k = 1;
#line 240 "SEQ_11_09_2009.instr"
  mccguide20_d = 0;
#line 239 "SEQ_11_09_2009.instr"
  mccguide20_mx = Gu_m;
#line 239 "SEQ_11_09_2009.instr"
  mccguide20_my = Gu_m;
#line 16705 "SEQ_11_09_2009.c"

#define mccompcurname  guide20
#define mccompcurtype  Channeled_guide
#define mccompcurindex 25
#define w1c mccguide20_w1c
#define w2c mccguide20_w2c
#define ww mccguide20_ww
#define hh mccguide20_hh
#define whalf mccguide20_whalf
#define hhalf mccguide20_hhalf
#define lwhalf mccguide20_lwhalf
#define lhhalf mccguide20_lhhalf
#define w1 mccguide20_w1
#define h1 mccguide20_h1
#define w2 mccguide20_w2
#define h2 mccguide20_h2
#define l mccguide20_l
#define R0 mccguide20_R0
#define Qcx mccguide20_Qcx
#define Qcy mccguide20_Qcy
#define alphax mccguide20_alphax
#define alphay mccguide20_alphay
#define W mccguide20_W
#define k mccguide20_k
#define d mccguide20_d
#define mx mccguide20_mx
#define my mccguide20_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16756 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide21. */
  SIG_MESSAGE("guide21 (Init)");
#line 242 "SEQ_11_09_2009.instr"
  mccguide21_w1 = 0.06488;
#line 242 "SEQ_11_09_2009.instr"
  mccguide21_h1 = 0.0748;
#line 242 "SEQ_11_09_2009.instr"
  mccguide21_w2 = 0.06382;
#line 242 "SEQ_11_09_2009.instr"
  mccguide21_h2 = 0.07335;
#line 243 "SEQ_11_09_2009.instr"
  mccguide21_l = 0.492;
#line 243 "SEQ_11_09_2009.instr"
  mccguide21_R0 = Gu_R;
#line 243 "SEQ_11_09_2009.instr"
  mccguide21_Qcx = Gu_Qc;
#line 243 "SEQ_11_09_2009.instr"
  mccguide21_Qcy = Gu_Qc;
#line 244 "SEQ_11_09_2009.instr"
  mccguide21_alphax = Gu_alpha;
#line 244 "SEQ_11_09_2009.instr"
  mccguide21_alphay = Gu_alpha;
#line 244 "SEQ_11_09_2009.instr"
  mccguide21_W = Gu_W;
#line 244 "SEQ_11_09_2009.instr"
  mccguide21_k = 1;
#line 244 "SEQ_11_09_2009.instr"
  mccguide21_d = 0;
#line 243 "SEQ_11_09_2009.instr"
  mccguide21_mx = Gu_m;
#line 243 "SEQ_11_09_2009.instr"
  mccguide21_my = Gu_m;
#line 16816 "SEQ_11_09_2009.c"

#define mccompcurname  guide21
#define mccompcurtype  Channeled_guide
#define mccompcurindex 26
#define w1c mccguide21_w1c
#define w2c mccguide21_w2c
#define ww mccguide21_ww
#define hh mccguide21_hh
#define whalf mccguide21_whalf
#define hhalf mccguide21_hhalf
#define lwhalf mccguide21_lwhalf
#define lhhalf mccguide21_lhhalf
#define w1 mccguide21_w1
#define h1 mccguide21_h1
#define w2 mccguide21_w2
#define h2 mccguide21_h2
#define l mccguide21_l
#define R0 mccguide21_R0
#define Qcx mccguide21_Qcx
#define Qcy mccguide21_Qcy
#define alphax mccguide21_alphax
#define alphay mccguide21_alphay
#define W mccguide21_W
#define k mccguide21_k
#define d mccguide21_d
#define mx mccguide21_mx
#define my mccguide21_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16867 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide22. */
  SIG_MESSAGE("guide22 (Init)");
#line 246 "SEQ_11_09_2009.instr"
  mccguide22_w1 = 0.06382;
#line 246 "SEQ_11_09_2009.instr"
  mccguide22_h1 = 0.07335;
#line 246 "SEQ_11_09_2009.instr"
  mccguide22_w2 = 0.06271;
#line 246 "SEQ_11_09_2009.instr"
  mccguide22_h2 = 0.07183;
#line 247 "SEQ_11_09_2009.instr"
  mccguide22_l = 0.492;
#line 247 "SEQ_11_09_2009.instr"
  mccguide22_R0 = Gu_R;
#line 247 "SEQ_11_09_2009.instr"
  mccguide22_Qcx = Gu_Qc;
#line 247 "SEQ_11_09_2009.instr"
  mccguide22_Qcy = Gu_Qc;
#line 248 "SEQ_11_09_2009.instr"
  mccguide22_alphax = Gu_alpha;
#line 248 "SEQ_11_09_2009.instr"
  mccguide22_alphay = Gu_alpha;
#line 248 "SEQ_11_09_2009.instr"
  mccguide22_W = Gu_W;
#line 248 "SEQ_11_09_2009.instr"
  mccguide22_k = 1;
#line 248 "SEQ_11_09_2009.instr"
  mccguide22_d = 0;
#line 247 "SEQ_11_09_2009.instr"
  mccguide22_mx = Gu_m;
#line 247 "SEQ_11_09_2009.instr"
  mccguide22_my = Gu_m;
#line 16927 "SEQ_11_09_2009.c"

#define mccompcurname  guide22
#define mccompcurtype  Channeled_guide
#define mccompcurindex 27
#define w1c mccguide22_w1c
#define w2c mccguide22_w2c
#define ww mccguide22_ww
#define hh mccguide22_hh
#define whalf mccguide22_whalf
#define hhalf mccguide22_hhalf
#define lwhalf mccguide22_lwhalf
#define lhhalf mccguide22_lhhalf
#define w1 mccguide22_w1
#define h1 mccguide22_h1
#define w2 mccguide22_w2
#define h2 mccguide22_h2
#define l mccguide22_l
#define R0 mccguide22_R0
#define Qcx mccguide22_Qcx
#define Qcy mccguide22_Qcy
#define alphax mccguide22_alphax
#define alphay mccguide22_alphay
#define W mccguide22_W
#define k mccguide22_k
#define d mccguide22_d
#define mx mccguide22_mx
#define my mccguide22_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 16978 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide23. */
  SIG_MESSAGE("guide23 (Init)");
#line 250 "SEQ_11_09_2009.instr"
  mccguide23_w1 = 0.06271;
#line 250 "SEQ_11_09_2009.instr"
  mccguide23_h1 = 0.07183;
#line 250 "SEQ_11_09_2009.instr"
  mccguide23_w2 = 0.06156;
#line 250 "SEQ_11_09_2009.instr"
  mccguide23_h2 = 0.07024;
#line 251 "SEQ_11_09_2009.instr"
  mccguide23_l = 0.492;
#line 251 "SEQ_11_09_2009.instr"
  mccguide23_R0 = Gu_R;
#line 251 "SEQ_11_09_2009.instr"
  mccguide23_Qcx = Gu_Qc;
#line 251 "SEQ_11_09_2009.instr"
  mccguide23_Qcy = Gu_Qc;
#line 252 "SEQ_11_09_2009.instr"
  mccguide23_alphax = Gu_alpha;
#line 252 "SEQ_11_09_2009.instr"
  mccguide23_alphay = Gu_alpha;
#line 252 "SEQ_11_09_2009.instr"
  mccguide23_W = Gu_W;
#line 252 "SEQ_11_09_2009.instr"
  mccguide23_k = 1;
#line 252 "SEQ_11_09_2009.instr"
  mccguide23_d = 0;
#line 251 "SEQ_11_09_2009.instr"
  mccguide23_mx = Gu_m;
#line 251 "SEQ_11_09_2009.instr"
  mccguide23_my = Gu_m;
#line 17038 "SEQ_11_09_2009.c"

#define mccompcurname  guide23
#define mccompcurtype  Channeled_guide
#define mccompcurindex 28
#define w1c mccguide23_w1c
#define w2c mccguide23_w2c
#define ww mccguide23_ww
#define hh mccguide23_hh
#define whalf mccguide23_whalf
#define hhalf mccguide23_hhalf
#define lwhalf mccguide23_lwhalf
#define lhhalf mccguide23_lhhalf
#define w1 mccguide23_w1
#define h1 mccguide23_h1
#define w2 mccguide23_w2
#define h2 mccguide23_h2
#define l mccguide23_l
#define R0 mccguide23_R0
#define Qcx mccguide23_Qcx
#define Qcy mccguide23_Qcy
#define alphax mccguide23_alphax
#define alphay mccguide23_alphay
#define W mccguide23_W
#define k mccguide23_k
#define d mccguide23_d
#define mx mccguide23_mx
#define my mccguide23_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17089 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide24. */
  SIG_MESSAGE("guide24 (Init)");
#line 254 "SEQ_11_09_2009.instr"
  mccguide24_w1 = 0.06156;
#line 254 "SEQ_11_09_2009.instr"
  mccguide24_h1 = 0.07024;
#line 254 "SEQ_11_09_2009.instr"
  mccguide24_w2 = 0.06036;
#line 254 "SEQ_11_09_2009.instr"
  mccguide24_h2 = 0.06858;
#line 255 "SEQ_11_09_2009.instr"
  mccguide24_l = 0.492;
#line 255 "SEQ_11_09_2009.instr"
  mccguide24_R0 = Gu_R;
#line 255 "SEQ_11_09_2009.instr"
  mccguide24_Qcx = Gu_Qc;
#line 255 "SEQ_11_09_2009.instr"
  mccguide24_Qcy = Gu_Qc;
#line 256 "SEQ_11_09_2009.instr"
  mccguide24_alphax = Gu_alpha;
#line 256 "SEQ_11_09_2009.instr"
  mccguide24_alphay = Gu_alpha;
#line 256 "SEQ_11_09_2009.instr"
  mccguide24_W = Gu_W;
#line 256 "SEQ_11_09_2009.instr"
  mccguide24_k = 1;
#line 256 "SEQ_11_09_2009.instr"
  mccguide24_d = 0;
#line 255 "SEQ_11_09_2009.instr"
  mccguide24_mx = Gu_m;
#line 255 "SEQ_11_09_2009.instr"
  mccguide24_my = Gu_m;
#line 17149 "SEQ_11_09_2009.c"

#define mccompcurname  guide24
#define mccompcurtype  Channeled_guide
#define mccompcurindex 29
#define w1c mccguide24_w1c
#define w2c mccguide24_w2c
#define ww mccguide24_ww
#define hh mccguide24_hh
#define whalf mccguide24_whalf
#define hhalf mccguide24_hhalf
#define lwhalf mccguide24_lwhalf
#define lhhalf mccguide24_lhhalf
#define w1 mccguide24_w1
#define h1 mccguide24_h1
#define w2 mccguide24_w2
#define h2 mccguide24_h2
#define l mccguide24_l
#define R0 mccguide24_R0
#define Qcx mccguide24_Qcx
#define Qcy mccguide24_Qcy
#define alphax mccguide24_alphax
#define alphay mccguide24_alphay
#define W mccguide24_W
#define k mccguide24_k
#define d mccguide24_d
#define mx mccguide24_mx
#define my mccguide24_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17200 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide25. */
  SIG_MESSAGE("guide25 (Init)");
#line 258 "SEQ_11_09_2009.instr"
  mccguide25_w1 = 0.06036;
#line 258 "SEQ_11_09_2009.instr"
  mccguide25_h1 = 0.06858;
#line 258 "SEQ_11_09_2009.instr"
  mccguide25_w2 = 0.05911;
#line 258 "SEQ_11_09_2009.instr"
  mccguide25_h2 = 0.06684;
#line 259 "SEQ_11_09_2009.instr"
  mccguide25_l = 0.492;
#line 259 "SEQ_11_09_2009.instr"
  mccguide25_R0 = Gu_R;
#line 259 "SEQ_11_09_2009.instr"
  mccguide25_Qcx = Gu_Qc;
#line 259 "SEQ_11_09_2009.instr"
  mccguide25_Qcy = Gu_Qc;
#line 260 "SEQ_11_09_2009.instr"
  mccguide25_alphax = Gu_alpha;
#line 260 "SEQ_11_09_2009.instr"
  mccguide25_alphay = Gu_alpha;
#line 260 "SEQ_11_09_2009.instr"
  mccguide25_W = Gu_W;
#line 260 "SEQ_11_09_2009.instr"
  mccguide25_k = 1;
#line 260 "SEQ_11_09_2009.instr"
  mccguide25_d = 0;
#line 259 "SEQ_11_09_2009.instr"
  mccguide25_mx = Gu_m;
#line 259 "SEQ_11_09_2009.instr"
  mccguide25_my = Gu_m;
#line 17260 "SEQ_11_09_2009.c"

#define mccompcurname  guide25
#define mccompcurtype  Channeled_guide
#define mccompcurindex 30
#define w1c mccguide25_w1c
#define w2c mccguide25_w2c
#define ww mccguide25_ww
#define hh mccguide25_hh
#define whalf mccguide25_whalf
#define hhalf mccguide25_hhalf
#define lwhalf mccguide25_lwhalf
#define lhhalf mccguide25_lhhalf
#define w1 mccguide25_w1
#define h1 mccguide25_h1
#define w2 mccguide25_w2
#define h2 mccguide25_h2
#define l mccguide25_l
#define R0 mccguide25_R0
#define Qcx mccguide25_Qcx
#define Qcy mccguide25_Qcy
#define alphax mccguide25_alphax
#define alphay mccguide25_alphay
#define W mccguide25_W
#define k mccguide25_k
#define d mccguide25_d
#define mx mccguide25_mx
#define my mccguide25_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17311 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide26. */
  SIG_MESSAGE("guide26 (Init)");
#line 262 "SEQ_11_09_2009.instr"
  mccguide26_w1 = 0.05911;
#line 262 "SEQ_11_09_2009.instr"
  mccguide26_h1 = 0.06684;
#line 262 "SEQ_11_09_2009.instr"
  mccguide26_w2 = 0.0578;
#line 262 "SEQ_11_09_2009.instr"
  mccguide26_h2 = 0.06502;
#line 263 "SEQ_11_09_2009.instr"
  mccguide26_l = 0.492;
#line 263 "SEQ_11_09_2009.instr"
  mccguide26_R0 = Gu_R;
#line 263 "SEQ_11_09_2009.instr"
  mccguide26_Qcx = Gu_Qc;
#line 263 "SEQ_11_09_2009.instr"
  mccguide26_Qcy = Gu_Qc;
#line 264 "SEQ_11_09_2009.instr"
  mccguide26_alphax = Gu_alpha;
#line 264 "SEQ_11_09_2009.instr"
  mccguide26_alphay = Gu_alpha;
#line 264 "SEQ_11_09_2009.instr"
  mccguide26_W = Gu_W;
#line 264 "SEQ_11_09_2009.instr"
  mccguide26_k = 1;
#line 264 "SEQ_11_09_2009.instr"
  mccguide26_d = 0;
#line 263 "SEQ_11_09_2009.instr"
  mccguide26_mx = Gu_m;
#line 263 "SEQ_11_09_2009.instr"
  mccguide26_my = Gu_m;
#line 17371 "SEQ_11_09_2009.c"

#define mccompcurname  guide26
#define mccompcurtype  Channeled_guide
#define mccompcurindex 31
#define w1c mccguide26_w1c
#define w2c mccguide26_w2c
#define ww mccguide26_ww
#define hh mccguide26_hh
#define whalf mccguide26_whalf
#define hhalf mccguide26_hhalf
#define lwhalf mccguide26_lwhalf
#define lhhalf mccguide26_lhhalf
#define w1 mccguide26_w1
#define h1 mccguide26_h1
#define w2 mccguide26_w2
#define h2 mccguide26_h2
#define l mccguide26_l
#define R0 mccguide26_R0
#define Qcx mccguide26_Qcx
#define Qcy mccguide26_Qcy
#define alphax mccguide26_alphax
#define alphay mccguide26_alphay
#define W mccguide26_W
#define k mccguide26_k
#define d mccguide26_d
#define mx mccguide26_mx
#define my mccguide26_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17422 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide27. */
  SIG_MESSAGE("guide27 (Init)");
#line 266 "SEQ_11_09_2009.instr"
  mccguide27_w1 = 0.0578;
#line 266 "SEQ_11_09_2009.instr"
  mccguide27_h1 = 0.06502;
#line 266 "SEQ_11_09_2009.instr"
  mccguide27_w2 = 0.05643;
#line 266 "SEQ_11_09_2009.instr"
  mccguide27_h2 = 0.0631;
#line 267 "SEQ_11_09_2009.instr"
  mccguide27_l = 0.492;
#line 267 "SEQ_11_09_2009.instr"
  mccguide27_R0 = Gu_R;
#line 267 "SEQ_11_09_2009.instr"
  mccguide27_Qcx = Gu_Qc;
#line 267 "SEQ_11_09_2009.instr"
  mccguide27_Qcy = Gu_Qc;
#line 268 "SEQ_11_09_2009.instr"
  mccguide27_alphax = Gu_alpha;
#line 268 "SEQ_11_09_2009.instr"
  mccguide27_alphay = Gu_alpha;
#line 268 "SEQ_11_09_2009.instr"
  mccguide27_W = Gu_W;
#line 268 "SEQ_11_09_2009.instr"
  mccguide27_k = 1;
#line 268 "SEQ_11_09_2009.instr"
  mccguide27_d = 0;
#line 267 "SEQ_11_09_2009.instr"
  mccguide27_mx = Gu_m;
#line 267 "SEQ_11_09_2009.instr"
  mccguide27_my = Gu_m;
#line 17482 "SEQ_11_09_2009.c"

#define mccompcurname  guide27
#define mccompcurtype  Channeled_guide
#define mccompcurindex 32
#define w1c mccguide27_w1c
#define w2c mccguide27_w2c
#define ww mccguide27_ww
#define hh mccguide27_hh
#define whalf mccguide27_whalf
#define hhalf mccguide27_hhalf
#define lwhalf mccguide27_lwhalf
#define lhhalf mccguide27_lhhalf
#define w1 mccguide27_w1
#define h1 mccguide27_h1
#define w2 mccguide27_w2
#define h2 mccguide27_h2
#define l mccguide27_l
#define R0 mccguide27_R0
#define Qcx mccguide27_Qcx
#define Qcy mccguide27_Qcy
#define alphax mccguide27_alphax
#define alphay mccguide27_alphay
#define W mccguide27_W
#define k mccguide27_k
#define d mccguide27_d
#define mx mccguide27_mx
#define my mccguide27_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17533 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component fermi_chopp. */
  SIG_MESSAGE("fermi_chopp (Init)");

#define mccompcurname  fermi_chopp
#define mccompcurtype  Fermi_chop2a
#define mccompcurindex 33
#define len mccfermi_chopp_len
#define w mccfermi_chopp_w
#define nu mccfermi_chopp_nu
#define delta mccfermi_chopp_delta
#define tc mccfermi_chopp_tc
#define ymin mccfermi_chopp_ymin
#define ymax mccfermi_chopp_ymax
#define nchan mccfermi_chopp_nchan
#define bw mccfermi_chopp_bw
#define blader mccfermi_chopp_blader
#define omega mccfermi_chopp_omega
#define r_blade mccfermi_chopp_r_blade
#define x_width mccfermi_chopp_x_width
#define nn mccfermi_chopp_nn
#define tdr mccfermi_chopp_tdr
#line 99 "Fermi_chop2a.comp"
{
   splen=len/2.0;
   omega=2.0*PI*nu;
   off=blader*(1-cos(asin(splen/fabs(blader))));// the additional width needed to accomodate the curvature of the blade
   tw=(w+2.0*off);  //the total width needed to contain the slit package
   rad=sqrt(tw*tw/4.0+splen*splen); //radius of cylinder containing slit package.
   sw=(w-bw)/nchan-bw;
   printf("sw: %g rad: %g\n",sw,rad);

}
#line 17593 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef blader
#undef bw
#undef nchan
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component adjustable_slits. */
  SIG_MESSAGE("adjustable_slits (Init)");
#line 275 "SEQ_11_09_2009.instr"
  mccadjustable_slits_xmin = mcipsxmin;
#line 275 "SEQ_11_09_2009.instr"
  mccadjustable_slits_xmax = mcipsxmax;
#line 275 "SEQ_11_09_2009.instr"
  mccadjustable_slits_ymin = mcipsymin;
#line 275 "SEQ_11_09_2009.instr"
  mccadjustable_slits_ymax = mcipsymax;
#line 46 "SEQ_11_09_2009.instr"
  mccadjustable_slits_radius = 0;
#line 46 "SEQ_11_09_2009.instr"
  mccadjustable_slits_cut = 0;
#line 46 "SEQ_11_09_2009.instr"
  mccadjustable_slits_width = 0;
#line 46 "SEQ_11_09_2009.instr"
  mccadjustable_slits_height = 0;
#line 17631 "SEQ_11_09_2009.c"

#define mccompcurname  adjustable_slits
#define mccompcurtype  Slit
#define mccompcurindex 34
#define xmin mccadjustable_slits_xmin
#define xmax mccadjustable_slits_xmax
#define ymin mccadjustable_slits_ymin
#define ymax mccadjustable_slits_ymax
#define radius mccadjustable_slits_radius
#define cut mccadjustable_slits_cut
#define width mccadjustable_slits_width
#define height mccadjustable_slits_height
#line 51 "/usr/local/lib/mcstas/optics/Slit.comp"
{
  if (width > 0)  { xmax=width/2;  xmin=-xmax; }
  if (height > 0) { ymax=height/2; ymin=-ymax; }
  if (xmin == 0 && xmax == 0 && ymin == 0 && ymax == 0 && radius == 0)
    { fprintf(stderr,"Slit: %s: Error: give geometry\n", NAME_CURRENT_COMP); exit(-1); }

}
#line 17652 "SEQ_11_09_2009.c"
#undef height
#undef width
#undef cut
#undef radius
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component Monitor1. */
  SIG_MESSAGE("Monitor1 (Init)");
#line 277 "SEQ_11_09_2009.instr"
  mccMonitor1_xmin = -0.035;
#line 277 "SEQ_11_09_2009.instr"
  mccMonitor1_xmax = 0.035;
#line 277 "SEQ_11_09_2009.instr"
  mccMonitor1_ymin = -0.035;
#line 277 "SEQ_11_09_2009.instr"
  mccMonitor1_ymax = 0.035;
#line 278 "SEQ_11_09_2009.instr"
  mccMonitor1_tmin = tplotmin;
#line 279 "SEQ_11_09_2009.instr"
  mccMonitor1_tmax = tplotmax;
#line 281 "SEQ_11_09_2009.instr"
  if(mon1optstr) strncpy(mccMonitor1_filename,mon1optstr, 1024); else mccMonitor1_filename[0]='\0';
#line 17681 "SEQ_11_09_2009.c"

#define mccompcurname  Monitor1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 35
#define nchan mccMonitor1_nchan
#define TOF_N mccMonitor1_TOF_N
#define TOF_p mccMonitor1_TOF_p
#define TOF_p2 mccMonitor1_TOF_p2
#define xmin mccMonitor1_xmin
#define xmax mccMonitor1_xmax
#define ymin mccMonitor1_ymin
#define ymax mccMonitor1_ymax
#define tmin mccMonitor1_tmin
#define tmax mccMonitor1_tmax
#define filename mccMonitor1_filename
#line 49 "TOF_monitor2.comp"
{
    int i;
    for (i=0; i<nchan; i++)
    {
      TOF_N[i] = 0;
      TOF_p[i] = 0;
      TOF_p2[i] = 0;
    }
}
#line 17707 "SEQ_11_09_2009.c"
#undef filename
#undef tmax
#undef tmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide29. */
  SIG_MESSAGE("guide29 (Init)");
#line 285 "SEQ_11_09_2009.instr"
  mccguide29_w1 = 0.0554;
#line 285 "SEQ_11_09_2009.instr"
  mccguide29_h1 = 0.06166;
#line 285 "SEQ_11_09_2009.instr"
  mccguide29_w2 = 0.05473;
#line 285 "SEQ_11_09_2009.instr"
  mccguide29_h2 = 0.0607;
#line 286 "SEQ_11_09_2009.instr"
  mccguide29_l = 0.228;
#line 286 "SEQ_11_09_2009.instr"
  mccguide29_R0 = Gu_R;
#line 286 "SEQ_11_09_2009.instr"
  mccguide29_Qcx = Gu_Qc;
#line 286 "SEQ_11_09_2009.instr"
  mccguide29_Qcy = Gu_Qc;
#line 287 "SEQ_11_09_2009.instr"
  mccguide29_alphax = Gu_alpha;
#line 287 "SEQ_11_09_2009.instr"
  mccguide29_alphay = Gu_alpha;
#line 287 "SEQ_11_09_2009.instr"
  mccguide29_W = Gu_W;
#line 287 "SEQ_11_09_2009.instr"
  mccguide29_k = 1;
#line 287 "SEQ_11_09_2009.instr"
  mccguide29_d = 0;
#line 286 "SEQ_11_09_2009.instr"
  mccguide29_mx = Gu_m;
#line 286 "SEQ_11_09_2009.instr"
  mccguide29_my = Gu_m;
#line 17755 "SEQ_11_09_2009.c"

#define mccompcurname  guide29
#define mccompcurtype  Channeled_guide
#define mccompcurindex 36
#define w1c mccguide29_w1c
#define w2c mccguide29_w2c
#define ww mccguide29_ww
#define hh mccguide29_hh
#define whalf mccguide29_whalf
#define hhalf mccguide29_hhalf
#define lwhalf mccguide29_lwhalf
#define lhhalf mccguide29_lhhalf
#define w1 mccguide29_w1
#define h1 mccguide29_h1
#define w2 mccguide29_w2
#define h2 mccguide29_h2
#define l mccguide29_l
#define R0 mccguide29_R0
#define Qcx mccguide29_Qcx
#define Qcy mccguide29_Qcy
#define alphax mccguide29_alphax
#define alphay mccguide29_alphay
#define W mccguide29_W
#define k mccguide29_k
#define d mccguide29_d
#define mx mccguide29_mx
#define my mccguide29_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17806 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide31. */
  SIG_MESSAGE("guide31 (Init)");
#line 290 "SEQ_11_09_2009.instr"
  mccguide31_w1 = 0.0547;
#line 290 "SEQ_11_09_2009.instr"
  mccguide31_h1 = 0.06066;
#line 290 "SEQ_11_09_2009.instr"
  mccguide31_w2 = 0.05328;
#line 290 "SEQ_11_09_2009.instr"
  mccguide31_h2 = 0.05866;
#line 291 "SEQ_11_09_2009.instr"
  mccguide31_l = 0.4585;
#line 291 "SEQ_11_09_2009.instr"
  mccguide31_R0 = Gu_R;
#line 291 "SEQ_11_09_2009.instr"
  mccguide31_Qcx = Gu_Qc;
#line 291 "SEQ_11_09_2009.instr"
  mccguide31_Qcy = Gu_Qc;
#line 292 "SEQ_11_09_2009.instr"
  mccguide31_alphax = Gu_alpha;
#line 292 "SEQ_11_09_2009.instr"
  mccguide31_alphay = Gu_alpha;
#line 292 "SEQ_11_09_2009.instr"
  mccguide31_W = Gu_W;
#line 292 "SEQ_11_09_2009.instr"
  mccguide31_k = 1;
#line 292 "SEQ_11_09_2009.instr"
  mccguide31_d = 0;
#line 291 "SEQ_11_09_2009.instr"
  mccguide31_mx = Gu_m;
#line 291 "SEQ_11_09_2009.instr"
  mccguide31_my = Gu_m;
#line 17866 "SEQ_11_09_2009.c"

#define mccompcurname  guide31
#define mccompcurtype  Channeled_guide
#define mccompcurindex 37
#define w1c mccguide31_w1c
#define w2c mccguide31_w2c
#define ww mccguide31_ww
#define hh mccguide31_hh
#define whalf mccguide31_whalf
#define hhalf mccguide31_hhalf
#define lwhalf mccguide31_lwhalf
#define lhhalf mccguide31_lhhalf
#define w1 mccguide31_w1
#define h1 mccguide31_h1
#define w2 mccguide31_w2
#define h2 mccguide31_h2
#define l mccguide31_l
#define R0 mccguide31_R0
#define Qcx mccguide31_Qcx
#define Qcy mccguide31_Qcy
#define alphax mccguide31_alphax
#define alphay mccguide31_alphay
#define W mccguide31_W
#define k mccguide31_k
#define d mccguide31_d
#define mx mccguide31_mx
#define my mccguide31_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 17917 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide32. */
  SIG_MESSAGE("guide32 (Init)");
#line 294 "SEQ_11_09_2009.instr"
  mccguide32_w1 = 0.05328;
#line 294 "SEQ_11_09_2009.instr"
  mccguide32_h1 = 0.05866;
#line 294 "SEQ_11_09_2009.instr"
  mccguide32_w2 = 0.05181;
#line 294 "SEQ_11_09_2009.instr"
  mccguide32_h2 = 0.05655;
#line 295 "SEQ_11_09_2009.instr"
  mccguide32_l = 0.4585;
#line 295 "SEQ_11_09_2009.instr"
  mccguide32_R0 = Gu_R;
#line 295 "SEQ_11_09_2009.instr"
  mccguide32_Qcx = Gu_Qc;
#line 295 "SEQ_11_09_2009.instr"
  mccguide32_Qcy = Gu_Qc;
#line 296 "SEQ_11_09_2009.instr"
  mccguide32_alphax = Gu_alpha;
#line 296 "SEQ_11_09_2009.instr"
  mccguide32_alphay = Gu_alpha;
#line 296 "SEQ_11_09_2009.instr"
  mccguide32_W = Gu_W;
#line 296 "SEQ_11_09_2009.instr"
  mccguide32_k = 1;
#line 296 "SEQ_11_09_2009.instr"
  mccguide32_d = 0;
#line 295 "SEQ_11_09_2009.instr"
  mccguide32_mx = Gu_m;
#line 295 "SEQ_11_09_2009.instr"
  mccguide32_my = Gu_m;
#line 17977 "SEQ_11_09_2009.c"

#define mccompcurname  guide32
#define mccompcurtype  Channeled_guide
#define mccompcurindex 38
#define w1c mccguide32_w1c
#define w2c mccguide32_w2c
#define ww mccguide32_ww
#define hh mccguide32_hh
#define whalf mccguide32_whalf
#define hhalf mccguide32_hhalf
#define lwhalf mccguide32_lwhalf
#define lhhalf mccguide32_lhhalf
#define w1 mccguide32_w1
#define h1 mccguide32_h1
#define w2 mccguide32_w2
#define h2 mccguide32_h2
#define l mccguide32_l
#define R0 mccguide32_R0
#define Qcx mccguide32_Qcx
#define Qcy mccguide32_Qcy
#define alphax mccguide32_alphax
#define alphay mccguide32_alphay
#define W mccguide32_W
#define k mccguide32_k
#define d mccguide32_d
#define mx mccguide32_mx
#define my mccguide32_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 18028 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component guide34. */
  SIG_MESSAGE("guide34 (Init)");
#line 299 "SEQ_11_09_2009.instr"
  mccguide34_w1 = 0.05181;
#line 299 "SEQ_11_09_2009.instr"
  mccguide34_h1 = 0.05654;
#line 299 "SEQ_11_09_2009.instr"
  mccguide34_w2 = 0.05043;
#line 299 "SEQ_11_09_2009.instr"
  mccguide34_h2 = 0.05456;
#line 300 "SEQ_11_09_2009.instr"
  mccguide34_l = 0.409;
#line 300 "SEQ_11_09_2009.instr"
  mccguide34_R0 = Gu_R;
#line 300 "SEQ_11_09_2009.instr"
  mccguide34_Qcx = Gu_Qc;
#line 300 "SEQ_11_09_2009.instr"
  mccguide34_Qcy = Gu_Qc;
#line 301 "SEQ_11_09_2009.instr"
  mccguide34_alphax = Gu_alpha;
#line 301 "SEQ_11_09_2009.instr"
  mccguide34_alphay = Gu_alpha;
#line 301 "SEQ_11_09_2009.instr"
  mccguide34_W = Gu_W;
#line 301 "SEQ_11_09_2009.instr"
  mccguide34_k = 1;
#line 301 "SEQ_11_09_2009.instr"
  mccguide34_d = 0;
#line 300 "SEQ_11_09_2009.instr"
  mccguide34_mx = Gu_m;
#line 300 "SEQ_11_09_2009.instr"
  mccguide34_my = Gu_m;
#line 18088 "SEQ_11_09_2009.c"

#define mccompcurname  guide34
#define mccompcurtype  Channeled_guide
#define mccompcurindex 39
#define w1c mccguide34_w1c
#define w2c mccguide34_w2c
#define ww mccguide34_ww
#define hh mccguide34_hh
#define whalf mccguide34_whalf
#define hhalf mccguide34_hhalf
#define lwhalf mccguide34_lwhalf
#define lhhalf mccguide34_lhhalf
#define w1 mccguide34_w1
#define h1 mccguide34_h1
#define w2 mccguide34_w2
#define h2 mccguide34_h2
#define l mccguide34_l
#define R0 mccguide34_R0
#define Qcx mccguide34_Qcx
#define Qcy mccguide34_Qcy
#define alphax mccguide34_alphax
#define alphay mccguide34_alphay
#define W mccguide34_W
#define k mccguide34_k
#define d mccguide34_d
#define mx mccguide34_mx
#define my mccguide34_my
#line 75 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{

  if (k <= 0 || W <=0)
  { fprintf(stderr,"Channeled_guide: %s: k abd W must be positive\n", NAME_CURRENT_COMP);
    exit(-1); }
  w1c = (w1 + d)/(double)k;
  w2c = (w2 + d)/(double)k;
  ww = .5*(w2c - w1c);
  hh = .5*(h2 - h1);
  whalf = .5*(w1c - d);
  hhalf = .5*h1;
  lwhalf = l*whalf;
  lhhalf = l*hhalf;

  if ((k > 1) && (w1 != w2))
  {
    fprintf(stderr,"Channeled_guide: This component does not work with\n");
    fprintf(stderr,"                 multichannel focusing guide\n");
    fprintf(stderr,"                 Use Gravity_guide for that.\n");
    exit(-1);
  }
}
#line 18139 "SEQ_11_09_2009.c"
#undef my
#undef mx
#undef d
#undef k
#undef W
#undef alphay
#undef alphax
#undef Qcy
#undef Qcx
#undef R0
#undef l
#undef h2
#undef w2
#undef h1
#undef w1
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component E_det. */
  SIG_MESSAGE("E_det (Init)");
#line 304 "SEQ_11_09_2009.instr"
  mccE_det_xmin = -.025;
#line 304 "SEQ_11_09_2009.instr"
  mccE_det_xmax = .025;
#line 304 "SEQ_11_09_2009.instr"
  mccE_det_ymin = -.025;
#line 304 "SEQ_11_09_2009.instr"
  mccE_det_ymax = .025;
#line 54 "SEQ_11_09_2009.instr"
  mccE_det_xwidth = 0;
#line 54 "SEQ_11_09_2009.instr"
  mccE_det_yheight = 0;
#line 305 "SEQ_11_09_2009.instr"
  mccE_det_Emin = Emin;
#line 305 "SEQ_11_09_2009.instr"
  mccE_det_Emax = Emax;
#line 18185 "SEQ_11_09_2009.c"

#define mccompcurname  E_det
#define mccompcurtype  E_monitor
#define mccompcurindex 40
#define nchan mccE_det_nchan
#define filename mccE_det_filename
#define restore_neutron mccE_det_restore_neutron
#define E_N mccE_det_E_N
#define E_p mccE_det_E_p
#define E_p2 mccE_det_E_p2
#define S_p mccE_det_S_p
#define S_pE mccE_det_S_pE
#define S_pE2 mccE_det_S_pE2
#define xmin mccE_det_xmin
#define xmax mccE_det_xmax
#define ymin mccE_det_ymin
#define ymax mccE_det_ymax
#define xwidth mccE_det_xwidth
#define yheight mccE_det_yheight
#define Emin mccE_det_Emin
#define Emax mccE_det_Emax
#line 65 "/usr/local/lib/mcstas/monitors/E_monitor.comp"
{
    int i;

    if (xwidth  > 0) { xmax = xwidth/2;  xmin = -xmax; }
    if (yheight > 0) { ymax = yheight/2; ymin = -ymax; }

    if ((xmin >= xmax) || (ymin >= ymax)) {
            printf("E_monitor: %s: Null detection area !\n"
                   "ERROR      (xwidth,yheight,xmin,xmax,ymin,ymax). Exiting",
           NAME_CURRENT_COMP);
      exit(0);
    }

    for (i=0; i<nchan; i++)
    {
      E_N[i] = 0;
      E_p[i] = 0;
      E_p2[i] = 0;
    }
    S_p = S_pE = S_pE2 = 0;
}
#line 18229 "SEQ_11_09_2009.c"
#undef Emax
#undef Emin
#undef yheight
#undef xwidth
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef restore_neutron
#undef filename
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component Sample_Arm. */
  SIG_MESSAGE("Sample_Arm (Init)");


  /* Initializations for component sample. */
  SIG_MESSAGE("sample (Init)");
#line 312 "SEQ_11_09_2009.instr"
  mccsample_radius_i = 0.0005;
#line 312 "SEQ_11_09_2009.instr"
  mccsample_radius_o = 0.00635;
#line 312 "SEQ_11_09_2009.instr"
  mccsample_h = 0.2;
#line 312 "SEQ_11_09_2009.instr"
  mccsample_focus_r = 0;
#line 94 "SEQ_11_09_2009.instr"
  mccsample_pack = 1;
#line 94 "SEQ_11_09_2009.instr"
  mccsample_frac = 1;
#line 94 "SEQ_11_09_2009.instr"
  mccsample_f_QE = 0;
#line 94 "SEQ_11_09_2009.instr"
  mccsample_gamma = 0;
#line 312 "SEQ_11_09_2009.instr"
  mccsample_target_x = 4.5;
#line 312 "SEQ_11_09_2009.instr"
  mccsample_target_y = 0.0;
#line 312 "SEQ_11_09_2009.instr"
  mccsample_target_z = 0.0;
#line 95 "SEQ_11_09_2009.instr"
  mccsample_focus_xw = 0;
#line 95 "SEQ_11_09_2009.instr"
  mccsample_focus_yh = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_focus_aw = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_focus_ah = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_xwidth = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_yheight = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_zthick = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_rad_sphere = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_sig_a = 5.08;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_sig_i = 5.08;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_V0 = 13.827;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_target_index = 0;
#line 96 "SEQ_11_09_2009.instr"
  mccsample_multiples = 1;
#line 18305 "SEQ_11_09_2009.c"

#define mccompcurname  sample
#define mccompcurtype  V_sample
#define mccompcurindex 42
#define StructVarsV mccsample_StructVarsV
#define VarsV mccsample_VarsV
#define radius_i mccsample_radius_i
#define radius_o mccsample_radius_o
#define h mccsample_h
#define focus_r mccsample_focus_r
#define pack mccsample_pack
#define frac mccsample_frac
#define f_QE mccsample_f_QE
#define gamma mccsample_gamma
#define target_x mccsample_target_x
#define target_y mccsample_target_y
#define target_z mccsample_target_z
#define focus_xw mccsample_focus_xw
#define focus_yh mccsample_focus_yh
#define focus_aw mccsample_focus_aw
#define focus_ah mccsample_focus_ah
#define xwidth mccsample_xwidth
#define yheight mccsample_yheight
#define zthick mccsample_zthick
#define rad_sphere mccsample_rad_sphere
#define sig_a mccsample_sig_a
#define sig_i mccsample_sig_i
#define V0 mccsample_V0
#define target_index mccsample_target_index
#define multiples mccsample_multiples
#line 119 "/usr/local/lib/mcstas/samples/V_sample.comp"
{
  if ( (rad_sphere && (xwidth || yheight || zthick)) || (rad_sphere && (radius_o || h)) || ((xwidth || yheight || zthick) && (radius_o || h)) )
        exit(fprintf(stderr,"V_sample: %s: multiple and imcompatible sample shape definitions\n", NAME_CURRENT_COMP));
	
  if (!rad_sphere)                      /* Cannot define a sphere */
    if (!xwidth || !yheight || !zthick) /* Cannot define a rectangle */
      if (!radius_o || !h)              /* Cannot define a cylinder either */
        exit(fprintf(stderr,"V_sample: %s: sample has no volume (zero dimensions)\n", NAME_CURRENT_COMP));
      else                              /* It is a cylinder */
        VarsV.shapetyp=0;
    else                                /* It is a rectangle */
      VarsV.shapetyp=1;
  else 
      VarsV.shapetyp=2;
  

/*  if(VarsV.isrect) printf("isrect"); else printf("not isrect"); */

  VarsV.sigma_a=sig_a;
  VarsV.sigma_i=sig_i;
  VarsV.rho = (pack/V0);
  VarsV.my_s=(VarsV.rho * 100 * VarsV.sigma_i);
  VarsV.my_a_v=(VarsV.rho * 100 * VarsV.sigma_a);

  /* now compute target coords if a component index is supplied */
  VarsV.tx= VarsV.ty=VarsV.tz=0;
  if (target_index)
  {
    Coords ToTarget;
    ToTarget = coords_sub(POS_A_COMP_INDEX(INDEX_CURRENT_COMP+target_index),POS_A_CURRENT_COMP);
    ToTarget = rot_apply(ROT_A_CURRENT_COMP, ToTarget);
    coords_get(ToTarget, &VarsV.tx, &VarsV.ty, &VarsV.tz);
  }
  else
  { VarsV.tx = target_x; VarsV.ty = target_y; VarsV.tz = target_z; }

  if (!(VarsV.tx || VarsV.ty || VarsV.tz))
    printf("V_sample: %s: The target is not defined. Using direct beam (Z-axis).\n",
      NAME_CURRENT_COMP);

  VarsV.distance=sqrt(VarsV.tx*VarsV.tx+VarsV.ty*VarsV.ty+VarsV.tz*VarsV.tz);

  /* different ways of setting rectangular area */
  VarsV.aw  = VarsV.ah = 0;
  if (focus_xw) {
  VarsV.xw = focus_xw;
  }
  if (focus_yh) {
    VarsV.yh = focus_yh;
  }
  if (focus_aw) {
    VarsV.aw = DEG2RAD*focus_aw;
  }
  if (focus_ah) {
    VarsV.ah = DEG2RAD*focus_ah;
  }
}
#line 18394 "SEQ_11_09_2009.c"
#undef multiples
#undef target_index
#undef V0
#undef sig_i
#undef sig_a
#undef rad_sphere
#undef zthick
#undef yheight
#undef xwidth
#undef focus_ah
#undef focus_aw
#undef focus_yh
#undef focus_xw
#undef target_z
#undef target_y
#undef target_x
#undef gamma
#undef f_QE
#undef frac
#undef pack
#undef focus_r
#undef h
#undef radius_o
#undef radius_i
#undef VarsV
#undef StructVarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component t_mon_detC. */
  SIG_MESSAGE("t_mon_detC (Init)");
#line 318 "SEQ_11_09_2009.instr"
  mcct_mon_detC_xwidth = 11.024;
#line 318 "SEQ_11_09_2009.instr"
  mcct_mon_detC_yheight = 7.0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_zthick = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_xmin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_xmax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_ymin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_ymax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_zmin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_zmax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_bins = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_min = -1e40;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detC_max = 1e40;
#line 318 "SEQ_11_09_2009.instr"
  mcct_mon_detC_restore_neutron = 1;
#line 18453 "SEQ_11_09_2009.c"

#define mccompcurname  t_mon_detC
#define mccompcurtype  Monitor_nD
#define mccompcurindex 43
#define options mcct_mon_detC_options
#define filename mcct_mon_detC_filename
#define user1 mcct_mon_detC_user1
#define user2 mcct_mon_detC_user2
#define user3 mcct_mon_detC_user3
#define username1 mcct_mon_detC_username1
#define username2 mcct_mon_detC_username2
#define username3 mcct_mon_detC_username3
#define DEFS mcct_mon_detC_DEFS
#define Vars mcct_mon_detC_Vars
#define xwidth mcct_mon_detC_xwidth
#define yheight mcct_mon_detC_yheight
#define zthick mcct_mon_detC_zthick
#define xmin mcct_mon_detC_xmin
#define xmax mcct_mon_detC_xmax
#define ymin mcct_mon_detC_ymin
#define ymax mcct_mon_detC_ymax
#define zmin mcct_mon_detC_zmin
#define zmax mcct_mon_detC_zmax
#define bins mcct_mon_detC_bins
#define min mcct_mon_detC_min
#define max mcct_mon_detC_max
#define restore_neutron mcct_mon_detC_restore_neutron
#line 225 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  char tmp[256];
  strcpy(Vars.compcurname, NAME_CURRENT_COMP);
  if (options != NULL)
    strncpy(Vars.option, options, 1024);
  else {
    strcpy(Vars.option, "x y");
    printf("Monitor_nD: %s has no option specified. Setting to PSD ('x y') monitor.\n", NAME_CURRENT_COMP);
  }
  Vars.compcurpos = POS_A_CURRENT_COMP;

  if (strstr(Vars.option, "source"))
    strcat(Vars.option, " list, x y z vx vy vz t sx sy sz ");

  if (bins) { sprintf(tmp, " all bins=%ld ", (long)bins); strcat(Vars.option, tmp); }
  if (min > -FLT_MAX && max < FLT_MAX) { sprintf(tmp, " all limits=[%g %g]", min, max); strcat(Vars.option, tmp); }
  else if (min > -FLT_MAX) { sprintf(tmp, " all min=%g", min); strcat(Vars.option, tmp); }
  else if (max <  FLT_MAX) { sprintf(tmp, " all max=%g", max); strcat(Vars.option, tmp); }

  strncpy(Vars.UserName1, username1 && strlen(username1) ? username1 : "", 32);
  strncpy(Vars.UserName2, username2 && strlen(username2) ? username2 : "", 32);
  strncpy(Vars.UserName3, username3 && strlen(username3) ? username3 : "", 32);

  Monitor_nD_Init(&DEFS, &Vars, xwidth, yheight, zthick, xmin,xmax,ymin,ymax,zmin,zmax);

  if (filename != NULL) strncpy(Vars.Mon_File, filename, 128);

  /* check if user given filename with ext will be used more than once */
  if ( ((Vars.Flag_Multiple && Vars.Coord_Number > 1) || Vars.Flag_List) && strchr(Vars.Mon_File,'.') )
  { char *XY; XY = strrchr(Vars.Mon_File,'.'); *XY='_'; }
  
  if (restore_neutron) Vars.Flag_parallel=1;
}
#line 18515 "SEQ_11_09_2009.c"
#undef restore_neutron
#undef max
#undef min
#undef bins
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef zthick
#undef yheight
#undef xwidth
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component t_mon_detB. */
  SIG_MESSAGE("t_mon_detB (Init)");
#line 322 "SEQ_11_09_2009.instr"
  mcct_mon_detB_xwidth = 10.742;
#line 322 "SEQ_11_09_2009.instr"
  mcct_mon_detB_yheight = 7.0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_zthick = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_xmin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_xmax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_ymin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_ymax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_zmin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_zmax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_bins = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_min = -1e40;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detB_max = 1e40;
#line 322 "SEQ_11_09_2009.instr"
  mcct_mon_detB_restore_neutron = 1;
#line 18571 "SEQ_11_09_2009.c"

#define mccompcurname  t_mon_detB
#define mccompcurtype  Monitor_nD
#define mccompcurindex 44
#define options mcct_mon_detB_options
#define filename mcct_mon_detB_filename
#define user1 mcct_mon_detB_user1
#define user2 mcct_mon_detB_user2
#define user3 mcct_mon_detB_user3
#define username1 mcct_mon_detB_username1
#define username2 mcct_mon_detB_username2
#define username3 mcct_mon_detB_username3
#define DEFS mcct_mon_detB_DEFS
#define Vars mcct_mon_detB_Vars
#define xwidth mcct_mon_detB_xwidth
#define yheight mcct_mon_detB_yheight
#define zthick mcct_mon_detB_zthick
#define xmin mcct_mon_detB_xmin
#define xmax mcct_mon_detB_xmax
#define ymin mcct_mon_detB_ymin
#define ymax mcct_mon_detB_ymax
#define zmin mcct_mon_detB_zmin
#define zmax mcct_mon_detB_zmax
#define bins mcct_mon_detB_bins
#define min mcct_mon_detB_min
#define max mcct_mon_detB_max
#define restore_neutron mcct_mon_detB_restore_neutron
#line 225 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  char tmp[256];
  strcpy(Vars.compcurname, NAME_CURRENT_COMP);
  if (options != NULL)
    strncpy(Vars.option, options, 1024);
  else {
    strcpy(Vars.option, "x y");
    printf("Monitor_nD: %s has no option specified. Setting to PSD ('x y') monitor.\n", NAME_CURRENT_COMP);
  }
  Vars.compcurpos = POS_A_CURRENT_COMP;

  if (strstr(Vars.option, "source"))
    strcat(Vars.option, " list, x y z vx vy vz t sx sy sz ");

  if (bins) { sprintf(tmp, " all bins=%ld ", (long)bins); strcat(Vars.option, tmp); }
  if (min > -FLT_MAX && max < FLT_MAX) { sprintf(tmp, " all limits=[%g %g]", min, max); strcat(Vars.option, tmp); }
  else if (min > -FLT_MAX) { sprintf(tmp, " all min=%g", min); strcat(Vars.option, tmp); }
  else if (max <  FLT_MAX) { sprintf(tmp, " all max=%g", max); strcat(Vars.option, tmp); }

  strncpy(Vars.UserName1, username1 && strlen(username1) ? username1 : "", 32);
  strncpy(Vars.UserName2, username2 && strlen(username2) ? username2 : "", 32);
  strncpy(Vars.UserName3, username3 && strlen(username3) ? username3 : "", 32);

  Monitor_nD_Init(&DEFS, &Vars, xwidth, yheight, zthick, xmin,xmax,ymin,ymax,zmin,zmax);

  if (filename != NULL) strncpy(Vars.Mon_File, filename, 128);

  /* check if user given filename with ext will be used more than once */
  if ( ((Vars.Flag_Multiple && Vars.Coord_Number > 1) || Vars.Flag_List) && strchr(Vars.Mon_File,'.') )
  { char *XY; XY = strrchr(Vars.Mon_File,'.'); *XY='_'; }
  
  if (restore_neutron) Vars.Flag_parallel=1;
}
#line 18633 "SEQ_11_09_2009.c"
#undef restore_neutron
#undef max
#undef min
#undef bins
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef zthick
#undef yheight
#undef xwidth
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component t_mon_detD. */
  SIG_MESSAGE("t_mon_detD (Init)");
#line 326 "SEQ_11_09_2009.instr"
  mcct_mon_detD_xwidth = 10.742;
#line 326 "SEQ_11_09_2009.instr"
  mcct_mon_detD_yheight = 7.0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_zthick = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_xmin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_xmax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_ymin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_ymax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_zmin = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_zmax = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_bins = 0;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_min = -1e40;
#line 207 "SEQ_11_09_2009.instr"
  mcct_mon_detD_max = 1e40;
#line 326 "SEQ_11_09_2009.instr"
  mcct_mon_detD_restore_neutron = 1;
#line 18689 "SEQ_11_09_2009.c"

#define mccompcurname  t_mon_detD
#define mccompcurtype  Monitor_nD
#define mccompcurindex 45
#define options mcct_mon_detD_options
#define filename mcct_mon_detD_filename
#define user1 mcct_mon_detD_user1
#define user2 mcct_mon_detD_user2
#define user3 mcct_mon_detD_user3
#define username1 mcct_mon_detD_username1
#define username2 mcct_mon_detD_username2
#define username3 mcct_mon_detD_username3
#define DEFS mcct_mon_detD_DEFS
#define Vars mcct_mon_detD_Vars
#define xwidth mcct_mon_detD_xwidth
#define yheight mcct_mon_detD_yheight
#define zthick mcct_mon_detD_zthick
#define xmin mcct_mon_detD_xmin
#define xmax mcct_mon_detD_xmax
#define ymin mcct_mon_detD_ymin
#define ymax mcct_mon_detD_ymax
#define zmin mcct_mon_detD_zmin
#define zmax mcct_mon_detD_zmax
#define bins mcct_mon_detD_bins
#define min mcct_mon_detD_min
#define max mcct_mon_detD_max
#define restore_neutron mcct_mon_detD_restore_neutron
#line 225 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  char tmp[256];
  strcpy(Vars.compcurname, NAME_CURRENT_COMP);
  if (options != NULL)
    strncpy(Vars.option, options, 1024);
  else {
    strcpy(Vars.option, "x y");
    printf("Monitor_nD: %s has no option specified. Setting to PSD ('x y') monitor.\n", NAME_CURRENT_COMP);
  }
  Vars.compcurpos = POS_A_CURRENT_COMP;

  if (strstr(Vars.option, "source"))
    strcat(Vars.option, " list, x y z vx vy vz t sx sy sz ");

  if (bins) { sprintf(tmp, " all bins=%ld ", (long)bins); strcat(Vars.option, tmp); }
  if (min > -FLT_MAX && max < FLT_MAX) { sprintf(tmp, " all limits=[%g %g]", min, max); strcat(Vars.option, tmp); }
  else if (min > -FLT_MAX) { sprintf(tmp, " all min=%g", min); strcat(Vars.option, tmp); }
  else if (max <  FLT_MAX) { sprintf(tmp, " all max=%g", max); strcat(Vars.option, tmp); }

  strncpy(Vars.UserName1, username1 && strlen(username1) ? username1 : "", 32);
  strncpy(Vars.UserName2, username2 && strlen(username2) ? username2 : "", 32);
  strncpy(Vars.UserName3, username3 && strlen(username3) ? username3 : "", 32);

  Monitor_nD_Init(&DEFS, &Vars, xwidth, yheight, zthick, xmin,xmax,ymin,ymax,zmin,zmax);

  if (filename != NULL) strncpy(Vars.Mon_File, filename, 128);

  /* check if user given filename with ext will be used more than once */
  if ( ((Vars.Flag_Multiple && Vars.Coord_Number > 1) || Vars.Flag_List) && strchr(Vars.Mon_File,'.') )
  { char *XY; XY = strrchr(Vars.Mon_File,'.'); *XY='_'; }
  
  if (restore_neutron) Vars.Flag_parallel=1;
}
#line 18751 "SEQ_11_09_2009.c"
#undef restore_neutron
#undef max
#undef min
#undef bins
#undef zmax
#undef zmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef zthick
#undef yheight
#undef xwidth
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* Initializations for component t_mon2. */
  SIG_MESSAGE("t_mon2 (Init)");
#line 330 "SEQ_11_09_2009.instr"
  mcct_mon2_xmin = -0.035;
#line 330 "SEQ_11_09_2009.instr"
  mcct_mon2_xmax = 0.035;
#line 330 "SEQ_11_09_2009.instr"
  mcct_mon2_ymin = -0.035;
#line 330 "SEQ_11_09_2009.instr"
  mcct_mon2_ymax = 0.035;
#line 331 "SEQ_11_09_2009.instr"
  mcct_mon2_tmin = ( tplotmin - toffset ) * LM2 / LM1 + toffset;
#line 332 "SEQ_11_09_2009.instr"
  mcct_mon2_tmax = ( tplotmax - toffset ) * LM2 / LM1 + toffset;
#line 334 "SEQ_11_09_2009.instr"
  if(mon2optstr) strncpy(mcct_mon2_filename,mon2optstr, 1024); else mcct_mon2_filename[0]='\0';
#line 18795 "SEQ_11_09_2009.c"

#define mccompcurname  t_mon2
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 46
#define nchan mcct_mon2_nchan
#define TOF_N mcct_mon2_TOF_N
#define TOF_p mcct_mon2_TOF_p
#define TOF_p2 mcct_mon2_TOF_p2
#define xmin mcct_mon2_xmin
#define xmax mcct_mon2_xmax
#define ymin mcct_mon2_ymin
#define ymax mcct_mon2_ymax
#define tmin mcct_mon2_tmin
#define tmax mcct_mon2_tmax
#define filename mcct_mon2_filename
#line 49 "TOF_monitor2.comp"
{
    int i;
    for (i=0; i<nchan; i++)
    {
      TOF_N[i] = 0;
      TOF_p[i] = 0;
      TOF_p2[i] = 0;
    }
}
#line 18821 "SEQ_11_09_2009.c"
#undef filename
#undef tmax
#undef tmin
#undef ymax
#undef ymin
#undef xmax
#undef xmin
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if(mcdotrace) mcdisplay();
    mcDEBUG_INSTR_END()
  }

/* NeXus support */

#ifdef USE_NEXUS

strncmp(mcnxversion,"5 zip",128);

#endif

} /* end init */

void mcraytrace(void) {
  /* Copy neutron state to local variables. */
  MCNUM mcnlx = mcnx;
  MCNUM mcnly = mcny;
  MCNUM mcnlz = mcnz;
  MCNUM mcnlvx = mcnvx;
  MCNUM mcnlvy = mcnvy;
  MCNUM mcnlvz = mcnvz;
  MCNUM mcnlt = mcnt;
  MCNUM mcnlsx = mcnsx;
  MCNUM mcnlsy = mcnsy;
  MCNUM mcnlsz = mcnsz;
  MCNUM mcnlp = mcnp;

  mcDEBUG_ENTER()
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define mcabsorb mcabsorbAll
  /* SPLIT counter for component sample */
  int mcSplit_sample=0;
  /* TRACE Component arm1 [1] */
  mccoordschange(mcposrarm1, mcrotrarm1,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrarm1, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component arm1 (without coords transformations) */
  mcJumpTrace_arm1:
  SIG_MESSAGE("arm1 (Trace)");
  mcDEBUG_COMP("arm1")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(1,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[1]++;
  mcPCounter[1] += p;
  mcP2Counter[1] += p*p;
#define mccompcurname  arm1
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define profile mccarm1_profile
#define IntermediateCnts mccarm1_IntermediateCnts
#define StartTime mccarm1_StartTime
#define EndTime mccarm1_EndTime
{   /* Declarations of SETTING parameters. */
MCNUM percent = mccarm1_percent;
MCNUM flag_save = mccarm1_flag_save;
MCNUM minutes = mccarm1_minutes;
#line 69 "/usr/local/lib/mcstas/misc/Progress_bar.comp"
{
  double ncount;
  ncount = mcget_run_num();
  if (!StartTime) {
    time(&StartTime); /* compute starting time */
    IntermediateCnts = 1e3;
  }
  time_t NowTime;
  time(&NowTime);
  if (!EndTime && ncount >= IntermediateCnts) {
    CurrentTime = NowTime;
    if (difftime(NowTime,StartTime) > 10) { /* wait 10 sec before writing ETA */
      EndTime = StartTime + (time_t)(difftime(NowTime,StartTime)
                           *mcget_ncount()/ncount);
      IntermediateCnts = 0;
      fprintf(stdout, "\nTrace ETA ");
      if (difftime(EndTime,StartTime) < 60.0)
        fprintf(stdout, "%g [s] %% ", difftime(EndTime,StartTime));
      else if (difftime(EndTime,StartTime) > 3600.0)
        fprintf(stdout, "%g [h] %% ", difftime(EndTime,StartTime));
      else
        fprintf(stdout, "%g [min] %% ", difftime(EndTime,StartTime)/60.0);
    } else IntermediateCnts += 1e3;
    fflush(stdout);
  }

  if (EndTime &&
    (    (minutes && difftime(NowTime,CurrentTime) > minutes*60)
      || (percent && !minutes && ncount >= IntermediateCnts))   )
  {
    fprintf(stdout, "%d ", (int)(ncount*100/mcget_ncount())); fflush(stdout);
    CurrentTime = NowTime;
    IntermediateCnts = ncount + percent*mcget_ncount()/100;
    if (IntermediateCnts >= mcget_ncount()) fprintf(stdout, "\n");
    if (flag_save) mcsave(NULL);
  }
}
#line 18941 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef profile
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component mod [2] */
  mccoordschange(mcposrmod, mcrotrmod,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrmod, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component mod (without coords transformations) */
  mcJumpTrace_mod:
  SIG_MESSAGE("mod (Trace)");
  mcDEBUG_COMP("mod")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(2,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[2]++;
  mcPCounter[2] += p;
  mcP2Counter[2] += p*p;
#define mccompcurname  mod
#define mccompcurtype  SNS_source
#define mccompcurindex 2
#define S_filename mccmod_S_filename
#define hdiv mccmod_hdiv
#define vdiv mccmod_vdiv
#define p_in mccmod_p_in
{   /* Declarations of SETTING parameters. */
MCNUM width = mccmod_width;
MCNUM height = mccmod_height;
MCNUM dist = mccmod_dist;
MCNUM xw = mccmod_xw;
MCNUM yh = mccmod_yh;
MCNUM Emin = mccmod_Emin;
MCNUM Emax = mccmod_Emax;
#line 470 "SNS_source.comp"
{
  double theta,phi,v,tauv,E,Eval,tval,randp;
  double hdivmin,hdivmax,vdivmin,vdivmax;
  int idx1,idx3,Eidxl,Eidxh;
  p=p_in;
  z=0;
 
  x = (rand01()-0.5)*width; /* choose points uniformly distributed on the source */
  y = (rand01()-0.5)*height;

 hdivmax=atan((xw/2.0-x)/dist);
 hdivmin=atan(-(xw/2.0+x)/dist);
 vdivmax=atan((yh/2.0-y)/dist);
 vdivmin=atan(-(yh/2.0+y)/dist);

  theta = hdivmin + (hdivmax-hdivmin)*rand01(); /* Small angle approx. */ 
  phi = vdivmin + (vdivmax-vdivmin)*rand01();
  hdiv=theta;
  vdiv=phi;
  /* generate random numbers*/

   /*First generate E random value */
    randp=EPmin+rand01()*(EPmax-EPmin);
    /* find E value corresponding to random probability */
    Eval=zero_find(Pfunc,randp,inxvec[idxstart],inxvec[idxstop],1e-5);
   /* from a known E value generate an emission time value */
   /* find the index of the E values that bracket the random E value */
   idx1=0;
   while((idx1<nEvals)&&(Ecol[idx1]<Eval)){
     idx1++;     
   }
   Eidxh=idx1;
   Eidxl=idx1-1;
   /*calculate the interpolated t, P curve to determine t value from uniform random value*/
   for (idx3=0;idx3<ntvals;idx3++){
     tyval[idx3]=linint(Eval,Ecol[Eidxl],Ecol[Eidxh],Ptmat[idx3][Eidxl],Ptmat[idx3][Eidxh]);
     txval[idx3]=tcol[idx3];
   }
   randp=tyval[tidxstart]+rand01()*(tyval[tidxstop-1]-tyval[tidxstart]);
   if (randp>0.0){
      tval=zero_find(tPfunc,randp,txval[tidxstart],txval[tidxstop-1],1e-5);}
    else{
       tval=0;}
  E = Eval*1000.0;  /* Convert Energy from Ev to meV */
  t = tval*1e-6;      /* Convert time from mus to S */
  v = SE2V*sqrt(E);
  /* Calculate components of velocity vector such that the neutron is within the focusing rectangle */
  vz = v*cos(phi)*cos(theta);   /* Small angle approx. */
  vy = v*sin(phi);
  vx = v*cos(phi)*sin(theta);
  p*=INorm2/mcget_ncount();
}
#line 19056 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef p_in
#undef vdiv
#undef hdiv
#undef S_filename
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component core_ves [3] */
  mccoordschange(mcposrcore_ves, mcrotrcore_ves,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrcore_ves, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component core_ves (without coords transformations) */
  mcJumpTrace_core_ves:
  SIG_MESSAGE("core_ves (Trace)");
  mcDEBUG_COMP("core_ves")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(3,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[3]++;
  mcPCounter[3] += p;
  mcP2Counter[3] += p*p;
#define mccompcurname  core_ves
#define mccompcurtype  Channeled_guide
#define mccompcurindex 3
#define w1c mcccore_ves_w1c
#define w2c mcccore_ves_w2c
#define ww mcccore_ves_ww
#define hh mcccore_ves_hh
#define whalf mcccore_ves_whalf
#define hhalf mcccore_ves_hhalf
#define lwhalf mcccore_ves_lwhalf
#define lhhalf mcccore_ves_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mcccore_ves_w1;
MCNUM h1 = mcccore_ves_h1;
MCNUM w2 = mcccore_ves_w2;
MCNUM h2 = mcccore_ves_h2;
MCNUM l = mcccore_ves_l;
MCNUM R0 = mcccore_ves_R0;
MCNUM Qcx = mcccore_ves_Qcx;
MCNUM Qcy = mcccore_ves_Qcy;
MCNUM alphax = mcccore_ves_alphax;
MCNUM alphay = mcccore_ves_alphay;
MCNUM W = mcccore_ves_W;
MCNUM k = mcccore_ves_k;
MCNUM d = mcccore_ves_d;
MCNUM mx = mcccore_ves_mx;
MCNUM my = mcccore_ves_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 19258 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component shutter_guide [4] */
  mccoordschange(mcposrshutter_guide, mcrotrshutter_guide,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrshutter_guide, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component shutter_guide (without coords transformations) */
  mcJumpTrace_shutter_guide:
  SIG_MESSAGE("shutter_guide (Trace)");
  mcDEBUG_COMP("shutter_guide")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(4,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[4]++;
  mcPCounter[4] += p;
  mcP2Counter[4] += p*p;
#define mccompcurname  shutter_guide
#define mccompcurtype  Channeled_guide
#define mccompcurindex 4
#define w1c mccshutter_guide_w1c
#define w2c mccshutter_guide_w2c
#define ww mccshutter_guide_ww
#define hh mccshutter_guide_hh
#define whalf mccshutter_guide_whalf
#define hhalf mccshutter_guide_hhalf
#define lwhalf mccshutter_guide_lwhalf
#define lhhalf mccshutter_guide_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccshutter_guide_w1;
MCNUM h1 = mccshutter_guide_h1;
MCNUM w2 = mccshutter_guide_w2;
MCNUM h2 = mccshutter_guide_h2;
MCNUM l = mccshutter_guide_l;
MCNUM R0 = mccshutter_guide_R0;
MCNUM Qcx = mccshutter_guide_Qcx;
MCNUM Qcy = mccshutter_guide_Qcy;
MCNUM alphax = mccshutter_guide_alphax;
MCNUM alphay = mccshutter_guide_alphay;
MCNUM W = mccshutter_guide_W;
MCNUM k = mccshutter_guide_k;
MCNUM d = mccshutter_guide_d;
MCNUM mx = mccshutter_guide_mx;
MCNUM my = mccshutter_guide_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 19464 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide1 [5] */
  mccoordschange(mcposrguide1, mcrotrguide1,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide1, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide1 (without coords transformations) */
  mcJumpTrace_guide1:
  SIG_MESSAGE("guide1 (Trace)");
  mcDEBUG_COMP("guide1")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(5,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[5]++;
  mcPCounter[5] += p;
  mcP2Counter[5] += p*p;
#define mccompcurname  guide1
#define mccompcurtype  Channeled_guide
#define mccompcurindex 5
#define w1c mccguide1_w1c
#define w2c mccguide1_w2c
#define ww mccguide1_ww
#define hh mccguide1_hh
#define whalf mccguide1_whalf
#define hhalf mccguide1_hhalf
#define lwhalf mccguide1_lwhalf
#define lhhalf mccguide1_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide1_w1;
MCNUM h1 = mccguide1_h1;
MCNUM w2 = mccguide1_w2;
MCNUM h2 = mccguide1_h2;
MCNUM l = mccguide1_l;
MCNUM R0 = mccguide1_R0;
MCNUM Qcx = mccguide1_Qcx;
MCNUM Qcy = mccguide1_Qcy;
MCNUM alphax = mccguide1_alphax;
MCNUM alphay = mccguide1_alphay;
MCNUM W = mccguide1_W;
MCNUM k = mccguide1_k;
MCNUM d = mccguide1_d;
MCNUM mx = mccguide1_mx;
MCNUM my = mccguide1_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 19670 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide2 [6] */
  mccoordschange(mcposrguide2, mcrotrguide2,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide2, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide2 (without coords transformations) */
  mcJumpTrace_guide2:
  SIG_MESSAGE("guide2 (Trace)");
  mcDEBUG_COMP("guide2")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(6,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[6]++;
  mcPCounter[6] += p;
  mcP2Counter[6] += p*p;
#define mccompcurname  guide2
#define mccompcurtype  Channeled_guide
#define mccompcurindex 6
#define w1c mccguide2_w1c
#define w2c mccguide2_w2c
#define ww mccguide2_ww
#define hh mccguide2_hh
#define whalf mccguide2_whalf
#define hhalf mccguide2_hhalf
#define lwhalf mccguide2_lwhalf
#define lhhalf mccguide2_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide2_w1;
MCNUM h1 = mccguide2_h1;
MCNUM w2 = mccguide2_w2;
MCNUM h2 = mccguide2_h2;
MCNUM l = mccguide2_l;
MCNUM R0 = mccguide2_R0;
MCNUM Qcx = mccguide2_Qcx;
MCNUM Qcy = mccguide2_Qcy;
MCNUM alphax = mccguide2_alphax;
MCNUM alphay = mccguide2_alphay;
MCNUM W = mccguide2_W;
MCNUM k = mccguide2_k;
MCNUM d = mccguide2_d;
MCNUM mx = mccguide2_mx;
MCNUM my = mccguide2_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 19876 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide3 [7] */
  mccoordschange(mcposrguide3, mcrotrguide3,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide3, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide3 (without coords transformations) */
  mcJumpTrace_guide3:
  SIG_MESSAGE("guide3 (Trace)");
  mcDEBUG_COMP("guide3")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(7,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[7]++;
  mcPCounter[7] += p;
  mcP2Counter[7] += p*p;
#define mccompcurname  guide3
#define mccompcurtype  Channeled_guide
#define mccompcurindex 7
#define w1c mccguide3_w1c
#define w2c mccguide3_w2c
#define ww mccguide3_ww
#define hh mccguide3_hh
#define whalf mccguide3_whalf
#define hhalf mccguide3_hhalf
#define lwhalf mccguide3_lwhalf
#define lhhalf mccguide3_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide3_w1;
MCNUM h1 = mccguide3_h1;
MCNUM w2 = mccguide3_w2;
MCNUM h2 = mccguide3_h2;
MCNUM l = mccguide3_l;
MCNUM R0 = mccguide3_R0;
MCNUM Qcx = mccguide3_Qcx;
MCNUM Qcy = mccguide3_Qcy;
MCNUM alphax = mccguide3_alphax;
MCNUM alphay = mccguide3_alphay;
MCNUM W = mccguide3_W;
MCNUM k = mccguide3_k;
MCNUM d = mccguide3_d;
MCNUM mx = mccguide3_mx;
MCNUM my = mccguide3_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 20082 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide4 [8] */
  mccoordschange(mcposrguide4, mcrotrguide4,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide4, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide4 (without coords transformations) */
  mcJumpTrace_guide4:
  SIG_MESSAGE("guide4 (Trace)");
  mcDEBUG_COMP("guide4")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(8,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[8]++;
  mcPCounter[8] += p;
  mcP2Counter[8] += p*p;
#define mccompcurname  guide4
#define mccompcurtype  Channeled_guide
#define mccompcurindex 8
#define w1c mccguide4_w1c
#define w2c mccguide4_w2c
#define ww mccguide4_ww
#define hh mccguide4_hh
#define whalf mccguide4_whalf
#define hhalf mccguide4_hhalf
#define lwhalf mccguide4_lwhalf
#define lhhalf mccguide4_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide4_w1;
MCNUM h1 = mccguide4_h1;
MCNUM w2 = mccguide4_w2;
MCNUM h2 = mccguide4_h2;
MCNUM l = mccguide4_l;
MCNUM R0 = mccguide4_R0;
MCNUM Qcx = mccguide4_Qcx;
MCNUM Qcy = mccguide4_Qcy;
MCNUM alphax = mccguide4_alphax;
MCNUM alphay = mccguide4_alphay;
MCNUM W = mccguide4_W;
MCNUM k = mccguide4_k;
MCNUM d = mccguide4_d;
MCNUM mx = mccguide4_mx;
MCNUM my = mccguide4_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 20288 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide5 [9] */
  mccoordschange(mcposrguide5, mcrotrguide5,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide5, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide5 (without coords transformations) */
  mcJumpTrace_guide5:
  SIG_MESSAGE("guide5 (Trace)");
  mcDEBUG_COMP("guide5")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(9,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[9]++;
  mcPCounter[9] += p;
  mcP2Counter[9] += p*p;
#define mccompcurname  guide5
#define mccompcurtype  Channeled_guide
#define mccompcurindex 9
#define w1c mccguide5_w1c
#define w2c mccguide5_w2c
#define ww mccguide5_ww
#define hh mccguide5_hh
#define whalf mccguide5_whalf
#define hhalf mccguide5_hhalf
#define lwhalf mccguide5_lwhalf
#define lhhalf mccguide5_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide5_w1;
MCNUM h1 = mccguide5_h1;
MCNUM w2 = mccguide5_w2;
MCNUM h2 = mccguide5_h2;
MCNUM l = mccguide5_l;
MCNUM R0 = mccguide5_R0;
MCNUM Qcx = mccguide5_Qcx;
MCNUM Qcy = mccguide5_Qcy;
MCNUM alphax = mccguide5_alphax;
MCNUM alphay = mccguide5_alphay;
MCNUM W = mccguide5_W;
MCNUM k = mccguide5_k;
MCNUM d = mccguide5_d;
MCNUM mx = mccguide5_mx;
MCNUM my = mccguide5_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 20494 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide6 [10] */
  mccoordschange(mcposrguide6, mcrotrguide6,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide6, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide6 (without coords transformations) */
  mcJumpTrace_guide6:
  SIG_MESSAGE("guide6 (Trace)");
  mcDEBUG_COMP("guide6")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(10,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[10]++;
  mcPCounter[10] += p;
  mcP2Counter[10] += p*p;
#define mccompcurname  guide6
#define mccompcurtype  Channeled_guide
#define mccompcurindex 10
#define w1c mccguide6_w1c
#define w2c mccguide6_w2c
#define ww mccguide6_ww
#define hh mccguide6_hh
#define whalf mccguide6_whalf
#define hhalf mccguide6_hhalf
#define lwhalf mccguide6_lwhalf
#define lhhalf mccguide6_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide6_w1;
MCNUM h1 = mccguide6_h1;
MCNUM w2 = mccguide6_w2;
MCNUM h2 = mccguide6_h2;
MCNUM l = mccguide6_l;
MCNUM R0 = mccguide6_R0;
MCNUM Qcx = mccguide6_Qcx;
MCNUM Qcy = mccguide6_Qcy;
MCNUM alphax = mccguide6_alphax;
MCNUM alphay = mccguide6_alphay;
MCNUM W = mccguide6_W;
MCNUM k = mccguide6_k;
MCNUM d = mccguide6_d;
MCNUM mx = mccguide6_mx;
MCNUM my = mccguide6_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 20700 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide7 [11] */
  mccoordschange(mcposrguide7, mcrotrguide7,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide7, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide7 (without coords transformations) */
  mcJumpTrace_guide7:
  SIG_MESSAGE("guide7 (Trace)");
  mcDEBUG_COMP("guide7")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(11,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[11]++;
  mcPCounter[11] += p;
  mcP2Counter[11] += p*p;
#define mccompcurname  guide7
#define mccompcurtype  Channeled_guide
#define mccompcurindex 11
#define w1c mccguide7_w1c
#define w2c mccguide7_w2c
#define ww mccguide7_ww
#define hh mccguide7_hh
#define whalf mccguide7_whalf
#define hhalf mccguide7_hhalf
#define lwhalf mccguide7_lwhalf
#define lhhalf mccguide7_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide7_w1;
MCNUM h1 = mccguide7_h1;
MCNUM w2 = mccguide7_w2;
MCNUM h2 = mccguide7_h2;
MCNUM l = mccguide7_l;
MCNUM R0 = mccguide7_R0;
MCNUM Qcx = mccguide7_Qcx;
MCNUM Qcy = mccguide7_Qcy;
MCNUM alphax = mccguide7_alphax;
MCNUM alphay = mccguide7_alphay;
MCNUM W = mccguide7_W;
MCNUM k = mccguide7_k;
MCNUM d = mccguide7_d;
MCNUM mx = mccguide7_mx;
MCNUM my = mccguide7_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 20906 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide8 [12] */
  mccoordschange(mcposrguide8, mcrotrguide8,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide8, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide8 (without coords transformations) */
  mcJumpTrace_guide8:
  SIG_MESSAGE("guide8 (Trace)");
  mcDEBUG_COMP("guide8")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(12,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[12]++;
  mcPCounter[12] += p;
  mcP2Counter[12] += p*p;
#define mccompcurname  guide8
#define mccompcurtype  Channeled_guide
#define mccompcurindex 12
#define w1c mccguide8_w1c
#define w2c mccguide8_w2c
#define ww mccguide8_ww
#define hh mccguide8_hh
#define whalf mccguide8_whalf
#define hhalf mccguide8_hhalf
#define lwhalf mccguide8_lwhalf
#define lhhalf mccguide8_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide8_w1;
MCNUM h1 = mccguide8_h1;
MCNUM w2 = mccguide8_w2;
MCNUM h2 = mccguide8_h2;
MCNUM l = mccguide8_l;
MCNUM R0 = mccguide8_R0;
MCNUM Qcx = mccguide8_Qcx;
MCNUM Qcy = mccguide8_Qcy;
MCNUM alphax = mccguide8_alphax;
MCNUM alphay = mccguide8_alphay;
MCNUM W = mccguide8_W;
MCNUM k = mccguide8_k;
MCNUM d = mccguide8_d;
MCNUM mx = mccguide8_mx;
MCNUM my = mccguide8_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 21112 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide9 [13] */
  mccoordschange(mcposrguide9, mcrotrguide9,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide9, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide9 (without coords transformations) */
  mcJumpTrace_guide9:
  SIG_MESSAGE("guide9 (Trace)");
  mcDEBUG_COMP("guide9")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(13,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[13]++;
  mcPCounter[13] += p;
  mcP2Counter[13] += p*p;
#define mccompcurname  guide9
#define mccompcurtype  Channeled_guide
#define mccompcurindex 13
#define w1c mccguide9_w1c
#define w2c mccguide9_w2c
#define ww mccguide9_ww
#define hh mccguide9_hh
#define whalf mccguide9_whalf
#define hhalf mccguide9_hhalf
#define lwhalf mccguide9_lwhalf
#define lhhalf mccguide9_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide9_w1;
MCNUM h1 = mccguide9_h1;
MCNUM w2 = mccguide9_w2;
MCNUM h2 = mccguide9_h2;
MCNUM l = mccguide9_l;
MCNUM R0 = mccguide9_R0;
MCNUM Qcx = mccguide9_Qcx;
MCNUM Qcy = mccguide9_Qcy;
MCNUM alphax = mccguide9_alphax;
MCNUM alphay = mccguide9_alphay;
MCNUM W = mccguide9_W;
MCNUM k = mccguide9_k;
MCNUM d = mccguide9_d;
MCNUM mx = mccguide9_mx;
MCNUM my = mccguide9_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 21318 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide10 [14] */
  mccoordschange(mcposrguide10, mcrotrguide10,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide10, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide10 (without coords transformations) */
  mcJumpTrace_guide10:
  SIG_MESSAGE("guide10 (Trace)");
  mcDEBUG_COMP("guide10")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(14,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[14]++;
  mcPCounter[14] += p;
  mcP2Counter[14] += p*p;
#define mccompcurname  guide10
#define mccompcurtype  Channeled_guide
#define mccompcurindex 14
#define w1c mccguide10_w1c
#define w2c mccguide10_w2c
#define ww mccguide10_ww
#define hh mccguide10_hh
#define whalf mccguide10_whalf
#define hhalf mccguide10_hhalf
#define lwhalf mccguide10_lwhalf
#define lhhalf mccguide10_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide10_w1;
MCNUM h1 = mccguide10_h1;
MCNUM w2 = mccguide10_w2;
MCNUM h2 = mccguide10_h2;
MCNUM l = mccguide10_l;
MCNUM R0 = mccguide10_R0;
MCNUM Qcx = mccguide10_Qcx;
MCNUM Qcy = mccguide10_Qcy;
MCNUM alphax = mccguide10_alphax;
MCNUM alphay = mccguide10_alphay;
MCNUM W = mccguide10_W;
MCNUM k = mccguide10_k;
MCNUM d = mccguide10_d;
MCNUM mx = mccguide10_mx;
MCNUM my = mccguide10_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 21524 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide11 [15] */
  mccoordschange(mcposrguide11, mcrotrguide11,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide11, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide11 (without coords transformations) */
  mcJumpTrace_guide11:
  SIG_MESSAGE("guide11 (Trace)");
  mcDEBUG_COMP("guide11")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(15,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[15]++;
  mcPCounter[15] += p;
  mcP2Counter[15] += p*p;
#define mccompcurname  guide11
#define mccompcurtype  Channeled_guide
#define mccompcurindex 15
#define w1c mccguide11_w1c
#define w2c mccguide11_w2c
#define ww mccguide11_ww
#define hh mccguide11_hh
#define whalf mccguide11_whalf
#define hhalf mccguide11_hhalf
#define lwhalf mccguide11_lwhalf
#define lhhalf mccguide11_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide11_w1;
MCNUM h1 = mccguide11_h1;
MCNUM w2 = mccguide11_w2;
MCNUM h2 = mccguide11_h2;
MCNUM l = mccguide11_l;
MCNUM R0 = mccguide11_R0;
MCNUM Qcx = mccguide11_Qcx;
MCNUM Qcy = mccguide11_Qcy;
MCNUM alphax = mccguide11_alphax;
MCNUM alphay = mccguide11_alphay;
MCNUM W = mccguide11_W;
MCNUM k = mccguide11_k;
MCNUM d = mccguide11_d;
MCNUM mx = mccguide11_mx;
MCNUM my = mccguide11_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 21730 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component t0_chopp [16] */
  mccoordschange(mcposrt0_chopp, mcrotrt0_chopp,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrt0_chopp, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component t0_chopp (without coords transformations) */
  mcJumpTrace_t0_chopp:
  SIG_MESSAGE("t0_chopp (Trace)");
  mcDEBUG_COMP("t0_chopp")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(16,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[16]++;
  mcPCounter[16] += p;
  mcP2Counter[16] += p*p;
#define mccompcurname  t0_chopp
#define mccompcurtype  Vertical_T0a
#define mccompcurindex 16
#define len mcct0_chopp_len
#define w1 mcct0_chopp_w1
#define w2 mcct0_chopp_w2
#define nu mcct0_chopp_nu
#define delta mcct0_chopp_delta
#define tc mcct0_chopp_tc
#define ymin mcct0_chopp_ymin
#define ymax mcct0_chopp_ymax
#define omega mcct0_chopp_omega
#define r_blade mcct0_chopp_r_blade
#define x_width mcct0_chopp_x_width
#define nn mcct0_chopp_nn
#define tdr mcct0_chopp_tdr
#line 88 "Vertical_T0a.comp"
{
 
  double t0,t1,dphi,dt2,tneuzr,tneuxr,nrad;
  double phivec[200],tpt[3],xpt[3],ypt[3],zpt[3],zr[3],xr[3],yr[3],theta[3],c[2];
  int chan_num,chan_num0,idx1,idx3;
  if (cylinder_intersect (&t0, &t1, x, y, z, vx, vy, vz, rad, ymax-ymin)){
    if (t0 < 0)			/*Neutron started inside cylinder */
        ABSORB;
    dt2=t1-t0;	
    PROP_DT(t0);                /*propagate neutron to edge of chopper*/
    /*calculate neutron position and velocity in chopper frame 
      calculate 3 points in the instrument frame and put them into the
      chopper frame inorder to determine the radius and center of a circle 
       that describes the path of the neutron in the chopper frame. */
    tpt[1]=t;
    tpt[2]=t+dt2;
    tpt[0]=t+dt2/2.0;
     //set local 0 in time as tc and calculate angle of rotation for each point
    for(idx3=0;idx3<3;idx3++){
      theta[idx3]=(tpt[idx3]-tc)*omega;
    }
    zpt[1]=-sqrt(rad*rad-x*x);  xpt[1]=x; ypt[1]=y;   /* point where neutron intersects chopper */
    zpt[2]=zpt[1]+vz*(dt2); xpt[2]=xpt[1]+vx*(dt2); ypt[2]=ypt[1]+vy*(dt2);  /* point where neutron leaves the chopper */
    xpt[0]=xpt[1]+vx*(dt2/2.0); ypt[0]=ypt[1]+vy*(dt2/2.0); zpt[0]=zpt[1]+vz*(dt2/2.0); /*point half way between in time */
   /* do the rotation */ 
   for(idx3=0;idx3<3;idx3++){
       rotate(xr[idx3],yr[idx3],zr[idx3],xpt[idx3],ypt[idx3],zpt[idx3],theta[idx3],0,1,0);     
    }       
    calccenter(c,zr,xr); /* calculate the center */
    nrad=sqrt((zr[0]-c[0])*(zr[0]-c[0])+(xr[0]-c[1])*(xr[0]-c[1])); /*calculate the radius of curvature for the neutron path */
   /* calculate points along path of neutron through cylinder quit on absorption
    * or transmit neutron if 200 points are calculated 
    * calculate phi for first and last points */
   phivec[0]=acos0_2pi((zr[1]-c[0])/nrad,xr[1]-c[1]);phivec[1]=acos0_2pi((zr[2]-c[0])/nrad,xr[2]-c[1]);
   neutxypos(&tneuzr,&tneuxr,phivec[0],nrad,c);
 /* reset phi[0] and phi[1] to match the length of the slit package rather than cylinder radius*/
   if(tneuzr<-splen){
       phivec[0]=acos0_2pi((-c[0]-splen)/nrad,-c[1]);
    }
   neutxypos(&tneuzr,&tneuxr,phivec[1],nrad,c);
   if(tneuzr>splen){
       phivec[1]=acos0_2pi((-c[0]+splen/2.0)/nrad,-c[1]);
    }
   dphi=phivec[1]-phivec[0];  /* initial dphi */
   idx1=2;
   phivec[idx1]=phivec[0]+dphi/2.0;  /* calculate center point */
   if (!t0checkabsorb(phivec[idx1],nrad,w1,w2,c))
      ABSORB;
   while (idx1<129){
     dphi=phivec[1]-phivec[idx1];
     idx1++;
     phivec[idx1]=phivec[0]+dphi/2.0;
     if (!t0checkabsorb(phivec[idx1],nrad,w1,w2,c))
      ABSORB;
     if (dphi>0){
       while ((phivec[idx1]<phivec[1])&&(idx1<129)){
        /* printf("phivec[%i]: %g dphi: %g phivec[1]: %g\n", idx1,phivec[idx1],dphi,phivec[1]);*/
         idx1++;
         phivec[idx1]=phivec[idx1-1]+dphi;
         if (!t0checkabsorb(phivec[idx1],nrad,w1,w2,c))
           ABSORB;
       }
       if (phivec[idx1]>=phivec[1]) idx1--; //remove the point that is beyond phivec[1]
     }
     else if (dphi<0){
         while ((phivec[idx1]>phivec[1])&&(idx1<129)){
        /* printf("phivec[%i]: %g\n", idx1,phivec[idx1]);*/
         idx1++;
         phivec[idx1]=phivec[idx1-1]+dphi;
         if (!t0checkabsorb(phivec[idx1],nrad,w1,w2,c))
           ABSORB;   
       }
       if (phivec[idx1]<=phivec[1]) idx1--; //remove the point that is beyond phivec[1]
     }
     else
        ABSORB; /* dphi =0? */
   }      
  }
  else				/* The neutron failed to even hit the chopper */
    ABSORB;

}
#line 21880 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w2
#undef w1
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component t_check1 [17] */
  mccoordschange(mcposrt_check1, mcrotrt_check1,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrt_check1, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component t_check1 (without coords transformations) */
  mcJumpTrace_t_check1:
  SIG_MESSAGE("t_check1 (Trace)");
  mcDEBUG_COMP("t_check1")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(17,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[17]++;
  mcPCounter[17] += p;
  mcP2Counter[17] += p*p;
#define mccompcurname  t_check1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 17
#define nchan mcct_check1_nchan
#define TOF_N mcct_check1_TOF_N
#define TOF_p mcct_check1_TOF_p
#define TOF_p2 mcct_check1_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mcct_check1_xmin;
MCNUM xmax = mcct_check1_xmax;
MCNUM ymin = mcct_check1_ymin;
MCNUM ymax = mcct_check1_ymax;
MCNUM tmin = mcct_check1_tmin;
MCNUM tmax = mcct_check1_tmax;
char* filename = mcct_check1_filename;
#line 59 "TOF_monitor2.comp"
{
    int i;
     double dt;
     dt=(tmax-tmin)/nchan;
    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax && t>=tmin && t<=tmax)
    {
    /* printf("dt %g\n",dt);*/
      i = floor((t-tmin)/dt);              /* Bin number */
      if(i >= nchan) i = nchan - 1;
      if(i < 0)
      {
        printf("FATAL ERROR: negative time-of-flight.\n");
        exit(1);
      }
      TOF_N[i]++;
      TOF_p[i] += p;
      TOF_p2[i] += p*p;
      //printf("i: %i TOF_p: %g TOF_p2:%g\n",i,TOF_p[i],TOF_p2[i]);
    }
}
#line 21972 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide13 [18] */
  mccoordschange(mcposrguide13, mcrotrguide13,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide13, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide13 (without coords transformations) */
  mcJumpTrace_guide13:
  SIG_MESSAGE("guide13 (Trace)");
  mcDEBUG_COMP("guide13")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(18,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[18]++;
  mcPCounter[18] += p;
  mcP2Counter[18] += p*p;
#define mccompcurname  guide13
#define mccompcurtype  Channeled_guide
#define mccompcurindex 18
#define w1c mccguide13_w1c
#define w2c mccguide13_w2c
#define ww mccguide13_ww
#define hh mccguide13_hh
#define whalf mccguide13_whalf
#define hhalf mccguide13_hhalf
#define lwhalf mccguide13_lwhalf
#define lhhalf mccguide13_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide13_w1;
MCNUM h1 = mccguide13_h1;
MCNUM w2 = mccguide13_w2;
MCNUM h2 = mccguide13_h2;
MCNUM l = mccguide13_l;
MCNUM R0 = mccguide13_R0;
MCNUM Qcx = mccguide13_Qcx;
MCNUM Qcy = mccguide13_Qcy;
MCNUM alphax = mccguide13_alphax;
MCNUM alphay = mccguide13_alphay;
MCNUM W = mccguide13_W;
MCNUM k = mccguide13_k;
MCNUM d = mccguide13_d;
MCNUM mx = mccguide13_mx;
MCNUM my = mccguide13_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 22174 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide14 [19] */
  mccoordschange(mcposrguide14, mcrotrguide14,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide14, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide14 (without coords transformations) */
  mcJumpTrace_guide14:
  SIG_MESSAGE("guide14 (Trace)");
  mcDEBUG_COMP("guide14")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(19,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[19]++;
  mcPCounter[19] += p;
  mcP2Counter[19] += p*p;
#define mccompcurname  guide14
#define mccompcurtype  Channeled_guide
#define mccompcurindex 19
#define w1c mccguide14_w1c
#define w2c mccguide14_w2c
#define ww mccguide14_ww
#define hh mccguide14_hh
#define whalf mccguide14_whalf
#define hhalf mccguide14_hhalf
#define lwhalf mccguide14_lwhalf
#define lhhalf mccguide14_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide14_w1;
MCNUM h1 = mccguide14_h1;
MCNUM w2 = mccguide14_w2;
MCNUM h2 = mccguide14_h2;
MCNUM l = mccguide14_l;
MCNUM R0 = mccguide14_R0;
MCNUM Qcx = mccguide14_Qcx;
MCNUM Qcy = mccguide14_Qcy;
MCNUM alphax = mccguide14_alphax;
MCNUM alphay = mccguide14_alphay;
MCNUM W = mccguide14_W;
MCNUM k = mccguide14_k;
MCNUM d = mccguide14_d;
MCNUM mx = mccguide14_mx;
MCNUM my = mccguide14_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 22380 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide15 [20] */
  mccoordschange(mcposrguide15, mcrotrguide15,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide15, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide15 (without coords transformations) */
  mcJumpTrace_guide15:
  SIG_MESSAGE("guide15 (Trace)");
  mcDEBUG_COMP("guide15")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(20,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[20]++;
  mcPCounter[20] += p;
  mcP2Counter[20] += p*p;
#define mccompcurname  guide15
#define mccompcurtype  Channeled_guide
#define mccompcurindex 20
#define w1c mccguide15_w1c
#define w2c mccguide15_w2c
#define ww mccguide15_ww
#define hh mccguide15_hh
#define whalf mccguide15_whalf
#define hhalf mccguide15_hhalf
#define lwhalf mccguide15_lwhalf
#define lhhalf mccguide15_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide15_w1;
MCNUM h1 = mccguide15_h1;
MCNUM w2 = mccguide15_w2;
MCNUM h2 = mccguide15_h2;
MCNUM l = mccguide15_l;
MCNUM R0 = mccguide15_R0;
MCNUM Qcx = mccguide15_Qcx;
MCNUM Qcy = mccguide15_Qcy;
MCNUM alphax = mccguide15_alphax;
MCNUM alphay = mccguide15_alphay;
MCNUM W = mccguide15_W;
MCNUM k = mccguide15_k;
MCNUM d = mccguide15_d;
MCNUM mx = mccguide15_mx;
MCNUM my = mccguide15_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 22586 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide16 [21] */
  mccoordschange(mcposrguide16, mcrotrguide16,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide16, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide16 (without coords transformations) */
  mcJumpTrace_guide16:
  SIG_MESSAGE("guide16 (Trace)");
  mcDEBUG_COMP("guide16")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(21,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[21]++;
  mcPCounter[21] += p;
  mcP2Counter[21] += p*p;
#define mccompcurname  guide16
#define mccompcurtype  Channeled_guide
#define mccompcurindex 21
#define w1c mccguide16_w1c
#define w2c mccguide16_w2c
#define ww mccguide16_ww
#define hh mccguide16_hh
#define whalf mccguide16_whalf
#define hhalf mccguide16_hhalf
#define lwhalf mccguide16_lwhalf
#define lhhalf mccguide16_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide16_w1;
MCNUM h1 = mccguide16_h1;
MCNUM w2 = mccguide16_w2;
MCNUM h2 = mccguide16_h2;
MCNUM l = mccguide16_l;
MCNUM R0 = mccguide16_R0;
MCNUM Qcx = mccguide16_Qcx;
MCNUM Qcy = mccguide16_Qcy;
MCNUM alphax = mccguide16_alphax;
MCNUM alphay = mccguide16_alphay;
MCNUM W = mccguide16_W;
MCNUM k = mccguide16_k;
MCNUM d = mccguide16_d;
MCNUM mx = mccguide16_mx;
MCNUM my = mccguide16_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 22792 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide17 [22] */
  mccoordschange(mcposrguide17, mcrotrguide17,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide17, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide17 (without coords transformations) */
  mcJumpTrace_guide17:
  SIG_MESSAGE("guide17 (Trace)");
  mcDEBUG_COMP("guide17")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(22,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[22]++;
  mcPCounter[22] += p;
  mcP2Counter[22] += p*p;
#define mccompcurname  guide17
#define mccompcurtype  Channeled_guide
#define mccompcurindex 22
#define w1c mccguide17_w1c
#define w2c mccguide17_w2c
#define ww mccguide17_ww
#define hh mccguide17_hh
#define whalf mccguide17_whalf
#define hhalf mccguide17_hhalf
#define lwhalf mccguide17_lwhalf
#define lhhalf mccguide17_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide17_w1;
MCNUM h1 = mccguide17_h1;
MCNUM w2 = mccguide17_w2;
MCNUM h2 = mccguide17_h2;
MCNUM l = mccguide17_l;
MCNUM R0 = mccguide17_R0;
MCNUM Qcx = mccguide17_Qcx;
MCNUM Qcy = mccguide17_Qcy;
MCNUM alphax = mccguide17_alphax;
MCNUM alphay = mccguide17_alphay;
MCNUM W = mccguide17_W;
MCNUM k = mccguide17_k;
MCNUM d = mccguide17_d;
MCNUM mx = mccguide17_mx;
MCNUM my = mccguide17_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 22998 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide18 [23] */
  mccoordschange(mcposrguide18, mcrotrguide18,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide18, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide18 (without coords transformations) */
  mcJumpTrace_guide18:
  SIG_MESSAGE("guide18 (Trace)");
  mcDEBUG_COMP("guide18")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(23,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[23]++;
  mcPCounter[23] += p;
  mcP2Counter[23] += p*p;
#define mccompcurname  guide18
#define mccompcurtype  Channeled_guide
#define mccompcurindex 23
#define w1c mccguide18_w1c
#define w2c mccguide18_w2c
#define ww mccguide18_ww
#define hh mccguide18_hh
#define whalf mccguide18_whalf
#define hhalf mccguide18_hhalf
#define lwhalf mccguide18_lwhalf
#define lhhalf mccguide18_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide18_w1;
MCNUM h1 = mccguide18_h1;
MCNUM w2 = mccguide18_w2;
MCNUM h2 = mccguide18_h2;
MCNUM l = mccguide18_l;
MCNUM R0 = mccguide18_R0;
MCNUM Qcx = mccguide18_Qcx;
MCNUM Qcy = mccguide18_Qcy;
MCNUM alphax = mccguide18_alphax;
MCNUM alphay = mccguide18_alphay;
MCNUM W = mccguide18_W;
MCNUM k = mccguide18_k;
MCNUM d = mccguide18_d;
MCNUM mx = mccguide18_mx;
MCNUM my = mccguide18_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 23204 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide19 [24] */
  mccoordschange(mcposrguide19, mcrotrguide19,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide19, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide19 (without coords transformations) */
  mcJumpTrace_guide19:
  SIG_MESSAGE("guide19 (Trace)");
  mcDEBUG_COMP("guide19")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(24,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[24]++;
  mcPCounter[24] += p;
  mcP2Counter[24] += p*p;
#define mccompcurname  guide19
#define mccompcurtype  Channeled_guide
#define mccompcurindex 24
#define w1c mccguide19_w1c
#define w2c mccguide19_w2c
#define ww mccguide19_ww
#define hh mccguide19_hh
#define whalf mccguide19_whalf
#define hhalf mccguide19_hhalf
#define lwhalf mccguide19_lwhalf
#define lhhalf mccguide19_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide19_w1;
MCNUM h1 = mccguide19_h1;
MCNUM w2 = mccguide19_w2;
MCNUM h2 = mccguide19_h2;
MCNUM l = mccguide19_l;
MCNUM R0 = mccguide19_R0;
MCNUM Qcx = mccguide19_Qcx;
MCNUM Qcy = mccguide19_Qcy;
MCNUM alphax = mccguide19_alphax;
MCNUM alphay = mccguide19_alphay;
MCNUM W = mccguide19_W;
MCNUM k = mccguide19_k;
MCNUM d = mccguide19_d;
MCNUM mx = mccguide19_mx;
MCNUM my = mccguide19_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 23410 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide20 [25] */
  mccoordschange(mcposrguide20, mcrotrguide20,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide20, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide20 (without coords transformations) */
  mcJumpTrace_guide20:
  SIG_MESSAGE("guide20 (Trace)");
  mcDEBUG_COMP("guide20")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(25,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[25]++;
  mcPCounter[25] += p;
  mcP2Counter[25] += p*p;
#define mccompcurname  guide20
#define mccompcurtype  Channeled_guide
#define mccompcurindex 25
#define w1c mccguide20_w1c
#define w2c mccguide20_w2c
#define ww mccguide20_ww
#define hh mccguide20_hh
#define whalf mccguide20_whalf
#define hhalf mccguide20_hhalf
#define lwhalf mccguide20_lwhalf
#define lhhalf mccguide20_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide20_w1;
MCNUM h1 = mccguide20_h1;
MCNUM w2 = mccguide20_w2;
MCNUM h2 = mccguide20_h2;
MCNUM l = mccguide20_l;
MCNUM R0 = mccguide20_R0;
MCNUM Qcx = mccguide20_Qcx;
MCNUM Qcy = mccguide20_Qcy;
MCNUM alphax = mccguide20_alphax;
MCNUM alphay = mccguide20_alphay;
MCNUM W = mccguide20_W;
MCNUM k = mccguide20_k;
MCNUM d = mccguide20_d;
MCNUM mx = mccguide20_mx;
MCNUM my = mccguide20_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 23616 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide21 [26] */
  mccoordschange(mcposrguide21, mcrotrguide21,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide21, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide21 (without coords transformations) */
  mcJumpTrace_guide21:
  SIG_MESSAGE("guide21 (Trace)");
  mcDEBUG_COMP("guide21")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(26,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[26]++;
  mcPCounter[26] += p;
  mcP2Counter[26] += p*p;
#define mccompcurname  guide21
#define mccompcurtype  Channeled_guide
#define mccompcurindex 26
#define w1c mccguide21_w1c
#define w2c mccguide21_w2c
#define ww mccguide21_ww
#define hh mccguide21_hh
#define whalf mccguide21_whalf
#define hhalf mccguide21_hhalf
#define lwhalf mccguide21_lwhalf
#define lhhalf mccguide21_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide21_w1;
MCNUM h1 = mccguide21_h1;
MCNUM w2 = mccguide21_w2;
MCNUM h2 = mccguide21_h2;
MCNUM l = mccguide21_l;
MCNUM R0 = mccguide21_R0;
MCNUM Qcx = mccguide21_Qcx;
MCNUM Qcy = mccguide21_Qcy;
MCNUM alphax = mccguide21_alphax;
MCNUM alphay = mccguide21_alphay;
MCNUM W = mccguide21_W;
MCNUM k = mccguide21_k;
MCNUM d = mccguide21_d;
MCNUM mx = mccguide21_mx;
MCNUM my = mccguide21_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 23822 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide22 [27] */
  mccoordschange(mcposrguide22, mcrotrguide22,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide22, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide22 (without coords transformations) */
  mcJumpTrace_guide22:
  SIG_MESSAGE("guide22 (Trace)");
  mcDEBUG_COMP("guide22")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(27,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[27]++;
  mcPCounter[27] += p;
  mcP2Counter[27] += p*p;
#define mccompcurname  guide22
#define mccompcurtype  Channeled_guide
#define mccompcurindex 27
#define w1c mccguide22_w1c
#define w2c mccguide22_w2c
#define ww mccguide22_ww
#define hh mccguide22_hh
#define whalf mccguide22_whalf
#define hhalf mccguide22_hhalf
#define lwhalf mccguide22_lwhalf
#define lhhalf mccguide22_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide22_w1;
MCNUM h1 = mccguide22_h1;
MCNUM w2 = mccguide22_w2;
MCNUM h2 = mccguide22_h2;
MCNUM l = mccguide22_l;
MCNUM R0 = mccguide22_R0;
MCNUM Qcx = mccguide22_Qcx;
MCNUM Qcy = mccguide22_Qcy;
MCNUM alphax = mccguide22_alphax;
MCNUM alphay = mccguide22_alphay;
MCNUM W = mccguide22_W;
MCNUM k = mccguide22_k;
MCNUM d = mccguide22_d;
MCNUM mx = mccguide22_mx;
MCNUM my = mccguide22_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 24028 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide23 [28] */
  mccoordschange(mcposrguide23, mcrotrguide23,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide23, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide23 (without coords transformations) */
  mcJumpTrace_guide23:
  SIG_MESSAGE("guide23 (Trace)");
  mcDEBUG_COMP("guide23")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(28,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[28]++;
  mcPCounter[28] += p;
  mcP2Counter[28] += p*p;
#define mccompcurname  guide23
#define mccompcurtype  Channeled_guide
#define mccompcurindex 28
#define w1c mccguide23_w1c
#define w2c mccguide23_w2c
#define ww mccguide23_ww
#define hh mccguide23_hh
#define whalf mccguide23_whalf
#define hhalf mccguide23_hhalf
#define lwhalf mccguide23_lwhalf
#define lhhalf mccguide23_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide23_w1;
MCNUM h1 = mccguide23_h1;
MCNUM w2 = mccguide23_w2;
MCNUM h2 = mccguide23_h2;
MCNUM l = mccguide23_l;
MCNUM R0 = mccguide23_R0;
MCNUM Qcx = mccguide23_Qcx;
MCNUM Qcy = mccguide23_Qcy;
MCNUM alphax = mccguide23_alphax;
MCNUM alphay = mccguide23_alphay;
MCNUM W = mccguide23_W;
MCNUM k = mccguide23_k;
MCNUM d = mccguide23_d;
MCNUM mx = mccguide23_mx;
MCNUM my = mccguide23_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 24234 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide24 [29] */
  mccoordschange(mcposrguide24, mcrotrguide24,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide24, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide24 (without coords transformations) */
  mcJumpTrace_guide24:
  SIG_MESSAGE("guide24 (Trace)");
  mcDEBUG_COMP("guide24")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(29,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[29]++;
  mcPCounter[29] += p;
  mcP2Counter[29] += p*p;
#define mccompcurname  guide24
#define mccompcurtype  Channeled_guide
#define mccompcurindex 29
#define w1c mccguide24_w1c
#define w2c mccguide24_w2c
#define ww mccguide24_ww
#define hh mccguide24_hh
#define whalf mccguide24_whalf
#define hhalf mccguide24_hhalf
#define lwhalf mccguide24_lwhalf
#define lhhalf mccguide24_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide24_w1;
MCNUM h1 = mccguide24_h1;
MCNUM w2 = mccguide24_w2;
MCNUM h2 = mccguide24_h2;
MCNUM l = mccguide24_l;
MCNUM R0 = mccguide24_R0;
MCNUM Qcx = mccguide24_Qcx;
MCNUM Qcy = mccguide24_Qcy;
MCNUM alphax = mccguide24_alphax;
MCNUM alphay = mccguide24_alphay;
MCNUM W = mccguide24_W;
MCNUM k = mccguide24_k;
MCNUM d = mccguide24_d;
MCNUM mx = mccguide24_mx;
MCNUM my = mccguide24_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 24440 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide25 [30] */
  mccoordschange(mcposrguide25, mcrotrguide25,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide25, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide25 (without coords transformations) */
  mcJumpTrace_guide25:
  SIG_MESSAGE("guide25 (Trace)");
  mcDEBUG_COMP("guide25")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(30,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[30]++;
  mcPCounter[30] += p;
  mcP2Counter[30] += p*p;
#define mccompcurname  guide25
#define mccompcurtype  Channeled_guide
#define mccompcurindex 30
#define w1c mccguide25_w1c
#define w2c mccguide25_w2c
#define ww mccguide25_ww
#define hh mccguide25_hh
#define whalf mccguide25_whalf
#define hhalf mccguide25_hhalf
#define lwhalf mccguide25_lwhalf
#define lhhalf mccguide25_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide25_w1;
MCNUM h1 = mccguide25_h1;
MCNUM w2 = mccguide25_w2;
MCNUM h2 = mccguide25_h2;
MCNUM l = mccguide25_l;
MCNUM R0 = mccguide25_R0;
MCNUM Qcx = mccguide25_Qcx;
MCNUM Qcy = mccguide25_Qcy;
MCNUM alphax = mccguide25_alphax;
MCNUM alphay = mccguide25_alphay;
MCNUM W = mccguide25_W;
MCNUM k = mccguide25_k;
MCNUM d = mccguide25_d;
MCNUM mx = mccguide25_mx;
MCNUM my = mccguide25_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 24646 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide26 [31] */
  mccoordschange(mcposrguide26, mcrotrguide26,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide26, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide26 (without coords transformations) */
  mcJumpTrace_guide26:
  SIG_MESSAGE("guide26 (Trace)");
  mcDEBUG_COMP("guide26")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(31,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[31]++;
  mcPCounter[31] += p;
  mcP2Counter[31] += p*p;
#define mccompcurname  guide26
#define mccompcurtype  Channeled_guide
#define mccompcurindex 31
#define w1c mccguide26_w1c
#define w2c mccguide26_w2c
#define ww mccguide26_ww
#define hh mccguide26_hh
#define whalf mccguide26_whalf
#define hhalf mccguide26_hhalf
#define lwhalf mccguide26_lwhalf
#define lhhalf mccguide26_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide26_w1;
MCNUM h1 = mccguide26_h1;
MCNUM w2 = mccguide26_w2;
MCNUM h2 = mccguide26_h2;
MCNUM l = mccguide26_l;
MCNUM R0 = mccguide26_R0;
MCNUM Qcx = mccguide26_Qcx;
MCNUM Qcy = mccguide26_Qcy;
MCNUM alphax = mccguide26_alphax;
MCNUM alphay = mccguide26_alphay;
MCNUM W = mccguide26_W;
MCNUM k = mccguide26_k;
MCNUM d = mccguide26_d;
MCNUM mx = mccguide26_mx;
MCNUM my = mccguide26_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 24852 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide27 [32] */
  mccoordschange(mcposrguide27, mcrotrguide27,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide27, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide27 (without coords transformations) */
  mcJumpTrace_guide27:
  SIG_MESSAGE("guide27 (Trace)");
  mcDEBUG_COMP("guide27")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(32,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[32]++;
  mcPCounter[32] += p;
  mcP2Counter[32] += p*p;
#define mccompcurname  guide27
#define mccompcurtype  Channeled_guide
#define mccompcurindex 32
#define w1c mccguide27_w1c
#define w2c mccguide27_w2c
#define ww mccguide27_ww
#define hh mccguide27_hh
#define whalf mccguide27_whalf
#define hhalf mccguide27_hhalf
#define lwhalf mccguide27_lwhalf
#define lhhalf mccguide27_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide27_w1;
MCNUM h1 = mccguide27_h1;
MCNUM w2 = mccguide27_w2;
MCNUM h2 = mccguide27_h2;
MCNUM l = mccguide27_l;
MCNUM R0 = mccguide27_R0;
MCNUM Qcx = mccguide27_Qcx;
MCNUM Qcy = mccguide27_Qcy;
MCNUM alphax = mccguide27_alphax;
MCNUM alphay = mccguide27_alphay;
MCNUM W = mccguide27_W;
MCNUM k = mccguide27_k;
MCNUM d = mccguide27_d;
MCNUM mx = mccguide27_mx;
MCNUM my = mccguide27_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 25058 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component fermi_chopp [33] */
  mccoordschange(mcposrfermi_chopp, mcrotrfermi_chopp,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrfermi_chopp, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component fermi_chopp (without coords transformations) */
  mcJumpTrace_fermi_chopp:
  SIG_MESSAGE("fermi_chopp (Trace)");
  mcDEBUG_COMP("fermi_chopp")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(33,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[33]++;
  mcPCounter[33] += p;
  mcP2Counter[33] += p*p;
#define mccompcurname  fermi_chopp
#define mccompcurtype  Fermi_chop2a
#define mccompcurindex 33
#define len mccfermi_chopp_len
#define w mccfermi_chopp_w
#define nu mccfermi_chopp_nu
#define delta mccfermi_chopp_delta
#define tc mccfermi_chopp_tc
#define ymin mccfermi_chopp_ymin
#define ymax mccfermi_chopp_ymax
#define nchan mccfermi_chopp_nchan
#define bw mccfermi_chopp_bw
#define blader mccfermi_chopp_blader
#define omega mccfermi_chopp_omega
#define r_blade mccfermi_chopp_r_blade
#define x_width mccfermi_chopp_x_width
#define nn mccfermi_chopp_nn
#define tdr mccfermi_chopp_tdr
#line 110 "Fermi_chop2a.comp"
{
 
  double t0,t1,dphi,dt2,tneuzr,tneuxr,nrad;
  double phivec[200],tpt[3],xpt[3],ypt[3],zpt[3],zr[3],xr[3],yr[3],theta[3],c[2];
  int chan_num,chan_num0,idx1,idx3;
  if (cylinder_intersect (&t0, &t1, x, y, z, vx, vy, vz, rad, ymax-ymin)){
    if (t0 < 0)			/*Neutron started inside cylinder */
        ABSORB;
    dt2=t1-t0;	
    PROP_DT(t0);                /*propagate neutron to edge of chopper*/
    /*calculate neutron position and velocity in chopper frame 
      calculate 3 points in the instrument frame and put them into the
      chopper frame inorder to determine the radius and center of a circle 
       that describes the path of the neutron in the chopper frame. */
    tpt[1]=t;
    tpt[2]=t+dt2;
    tpt[0]=t+dt2/2.0;
     //set local 0 in time as tc and calculate angle of rotation for each point
    for(idx3=0;idx3<3;idx3++){
      theta[idx3]=(tpt[idx3]-tc)*omega;
    }
    zpt[1]=-sqrt(rad*rad-x*x);  xpt[1]=x; ypt[1]=y;   /* point where neutron intersects chopper */
    zpt[2]=zpt[1]+vz*(dt2); xpt[2]=xpt[1]+vx*(dt2); ypt[2]=ypt[1]+vy*(dt2);  /* point where neutron leaves the chopper */
    xpt[0]=xpt[1]+vx*(dt2/2.0); ypt[0]=ypt[1]+vy*(dt2/2.0); zpt[0]=zpt[1]+vz*(dt2/2.0); /*point half way between in time */
   /* do the rotation */ 
   for(idx3=0;idx3<3;idx3++){
       rotate(xr[idx3],yr[idx3],zr[idx3],xpt[idx3],ypt[idx3],zpt[idx3],theta[idx3],0,1,0);     
    }       
    calccenter(c,zr,xr); /* calculate the center */
    nrad=sqrt((zr[0]-c[0])*(zr[0]-c[0])+(xr[0]-c[1])*(xr[0]-c[1])); /*calculate the radius of curvature for the neutron path */
   /* calculate points along path of neutron through cylinder quit on absorption
    * or transmit neutron if 200 points are calculated 
    * calculate phi for first and last points */
   phivec[0]=acos0_2pi((zr[1]-c[0])/nrad,xr[1]-c[1]);phivec[1]=acos0_2pi((zr[2]-c[0])/nrad,xr[2]-c[1]);
   neutxypos(&tneuzr,&tneuxr,phivec[0],nrad,c);
 /* reset phi[0] and phi[1] to match the length of the slit package rather than cylinder radius*/
   if(tneuzr<-splen){
       phivec[0]=acos0_2pi((-c[0]-splen)/nrad,-c[1]);
    }
   neutxypos(&tneuzr,&tneuxr,phivec[1],nrad,c);
   if(tneuzr>splen){
       phivec[1]=acos0_2pi((-c[0]+splen/2.0)/nrad,-c[1]);
    }
   dphi=phivec[1]-phivec[0];  /* initial dphi */
   idx1=2;
   phivec[idx1]=phivec[0]+dphi/2.0;  /* calculate center point */
   if (!checkabsorb(phivec[idx1],&chan_num,nrad,tw,sw,bw,c))
      ABSORB;
   chan_num0=chan_num;
   while (idx1<129){
     dphi=phivec[1]-phivec[idx1];
     idx1++;
     phivec[idx1]=phivec[0]+dphi/2.0;
     if (!checkabsorb(phivec[idx1],&chan_num,nrad,tw,sw,bw,c))
      ABSORB;
     if ((chan_num!=chan_num0) || (chan_num>nchan))
       ABSORB;
     /*  If the current dphi is positive calcualte points until a point is beyond phivec[1]
                    Check to see if the point is absorbed after each new point is generated stop if more than 129 iterations are performed
            */
     if (dphi>0){
       while ((phivec[idx1]<phivec[1])&&(idx1<129)){
        /* printf("phivec[%i]: %g dphi: %g phivec[1]: %g\n", idx1,phivec[idx1],dphi,phivec[1]);*/
         idx1++;
         phivec[idx1]=phivec[idx1-1]+dphi;
         if (!checkabsorb(phivec[idx1],&chan_num,nrad,tw,sw,bw,c))
           ABSORB;
     //   printf("chan_num0: %i chan_num: %i\n",chan_num0,chan_num);
         if ((chan_num!=chan_num0) || (chan_num>nchan))
           ABSORB;
           
       }
       if (phivec[idx1]>=phivec[1]) idx1--; //remove the point that is beyond phivec[1]
     }
     /*  If the current dphi is negative calculatete points until a point is beyond phivec[1]
                    Check to see if the point is absorbed after each new point is generated stop if more than 129 iterations are performed
            */
     else if (dphi<0){
       while ((phivec[idx1]>phivec[1])&&(idx1<129)){
        /* printf("phivec[%i]: %g\n", idx1,phivec[idx1]);*/
         idx1++;
         phivec[idx1]=phivec[idx1-1]+dphi;
         if (!checkabsorb(phivec[idx1],&chan_num,nrad,tw,sw,bw,c))
           ABSORB;
      //   printf("chan_num0: %i chan_num: %i\n",chan_num0,chan_num);
         if ((chan_num!=chan_num0) || (chan_num>nchan))
           ABSORB;                  
       }
       if (phivec[idx1]<=phivec[1]) idx1--; //remove the point that is beyond phivec[1]
     }
     else
        ABSORB; /* dphi =0? */
   }      
  }
  else				/* The neutron failed to even hit the chopper */
    ABSORB;

}
#line 25226 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef blader
#undef bw
#undef nchan
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component adjustable_slits [34] */
  mccoordschange(mcposradjustable_slits, mcrotradjustable_slits,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotradjustable_slits, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component adjustable_slits (without coords transformations) */
  mcJumpTrace_adjustable_slits:
  SIG_MESSAGE("adjustable_slits (Trace)");
  mcDEBUG_COMP("adjustable_slits")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(34,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[34]++;
  mcPCounter[34] += p;
  mcP2Counter[34] += p*p;
#define mccompcurname  adjustable_slits
#define mccompcurtype  Slit
#define mccompcurindex 34
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccadjustable_slits_xmin;
MCNUM xmax = mccadjustable_slits_xmax;
MCNUM ymin = mccadjustable_slits_ymin;
MCNUM ymax = mccadjustable_slits_ymax;
MCNUM radius = mccadjustable_slits_radius;
MCNUM cut = mccadjustable_slits_cut;
MCNUM width = mccadjustable_slits_width;
MCNUM height = mccadjustable_slits_height;
#line 60 "/usr/local/lib/mcstas/optics/Slit.comp"
{
    PROP_Z0;
    if (((radius == 0) && (x<xmin || x>xmax || y<ymin || y>ymax))
    || ((radius != 0) && (x*x + y*y > radius*radius)))
      ABSORB;
    else
      if (p < cut)
        ABSORB;
      else
        SCATTER;
}
#line 25307 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component Monitor1 [35] */
  mccoordschange(mcposrMonitor1, mcrotrMonitor1,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrMonitor1, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component Monitor1 (without coords transformations) */
  mcJumpTrace_Monitor1:
  SIG_MESSAGE("Monitor1 (Trace)");
  mcDEBUG_COMP("Monitor1")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(35,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[35]++;
  mcPCounter[35] += p;
  mcP2Counter[35] += p*p;
#define mccompcurname  Monitor1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 35
#define nchan mccMonitor1_nchan
#define TOF_N mccMonitor1_TOF_N
#define TOF_p mccMonitor1_TOF_p
#define TOF_p2 mccMonitor1_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccMonitor1_xmin;
MCNUM xmax = mccMonitor1_xmax;
MCNUM ymin = mccMonitor1_ymin;
MCNUM ymax = mccMonitor1_ymax;
MCNUM tmin = mccMonitor1_tmin;
MCNUM tmax = mccMonitor1_tmax;
char* filename = mccMonitor1_filename;
#line 59 "TOF_monitor2.comp"
{
    int i;
     double dt;
     dt=(tmax-tmin)/nchan;
    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax && t>=tmin && t<=tmax)
    {
    /* printf("dt %g\n",dt);*/
      i = floor((t-tmin)/dt);              /* Bin number */
      if(i >= nchan) i = nchan - 1;
      if(i < 0)
      {
        printf("FATAL ERROR: negative time-of-flight.\n");
        exit(1);
      }
      TOF_N[i]++;
      TOF_p[i] += p;
      TOF_p2[i] += p*p;
      //printf("i: %i TOF_p: %g TOF_p2:%g\n",i,TOF_p[i],TOF_p2[i]);
    }
}
#line 25387 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide29 [36] */
  mccoordschange(mcposrguide29, mcrotrguide29,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide29, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide29 (without coords transformations) */
  mcJumpTrace_guide29:
  SIG_MESSAGE("guide29 (Trace)");
  mcDEBUG_COMP("guide29")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(36,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[36]++;
  mcPCounter[36] += p;
  mcP2Counter[36] += p*p;
#define mccompcurname  guide29
#define mccompcurtype  Channeled_guide
#define mccompcurindex 36
#define w1c mccguide29_w1c
#define w2c mccguide29_w2c
#define ww mccguide29_ww
#define hh mccguide29_hh
#define whalf mccguide29_whalf
#define hhalf mccguide29_hhalf
#define lwhalf mccguide29_lwhalf
#define lhhalf mccguide29_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide29_w1;
MCNUM h1 = mccguide29_h1;
MCNUM w2 = mccguide29_w2;
MCNUM h2 = mccguide29_h2;
MCNUM l = mccguide29_l;
MCNUM R0 = mccguide29_R0;
MCNUM Qcx = mccguide29_Qcx;
MCNUM Qcy = mccguide29_Qcy;
MCNUM alphax = mccguide29_alphax;
MCNUM alphay = mccguide29_alphay;
MCNUM W = mccguide29_W;
MCNUM k = mccguide29_k;
MCNUM d = mccguide29_d;
MCNUM mx = mccguide29_mx;
MCNUM my = mccguide29_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 25589 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide31 [37] */
  mccoordschange(mcposrguide31, mcrotrguide31,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide31, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide31 (without coords transformations) */
  mcJumpTrace_guide31:
  SIG_MESSAGE("guide31 (Trace)");
  mcDEBUG_COMP("guide31")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(37,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[37]++;
  mcPCounter[37] += p;
  mcP2Counter[37] += p*p;
#define mccompcurname  guide31
#define mccompcurtype  Channeled_guide
#define mccompcurindex 37
#define w1c mccguide31_w1c
#define w2c mccguide31_w2c
#define ww mccguide31_ww
#define hh mccguide31_hh
#define whalf mccguide31_whalf
#define hhalf mccguide31_hhalf
#define lwhalf mccguide31_lwhalf
#define lhhalf mccguide31_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide31_w1;
MCNUM h1 = mccguide31_h1;
MCNUM w2 = mccguide31_w2;
MCNUM h2 = mccguide31_h2;
MCNUM l = mccguide31_l;
MCNUM R0 = mccguide31_R0;
MCNUM Qcx = mccguide31_Qcx;
MCNUM Qcy = mccguide31_Qcy;
MCNUM alphax = mccguide31_alphax;
MCNUM alphay = mccguide31_alphay;
MCNUM W = mccguide31_W;
MCNUM k = mccguide31_k;
MCNUM d = mccguide31_d;
MCNUM mx = mccguide31_mx;
MCNUM my = mccguide31_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 25795 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide32 [38] */
  mccoordschange(mcposrguide32, mcrotrguide32,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide32, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide32 (without coords transformations) */
  mcJumpTrace_guide32:
  SIG_MESSAGE("guide32 (Trace)");
  mcDEBUG_COMP("guide32")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(38,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[38]++;
  mcPCounter[38] += p;
  mcP2Counter[38] += p*p;
#define mccompcurname  guide32
#define mccompcurtype  Channeled_guide
#define mccompcurindex 38
#define w1c mccguide32_w1c
#define w2c mccguide32_w2c
#define ww mccguide32_ww
#define hh mccguide32_hh
#define whalf mccguide32_whalf
#define hhalf mccguide32_hhalf
#define lwhalf mccguide32_lwhalf
#define lhhalf mccguide32_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide32_w1;
MCNUM h1 = mccguide32_h1;
MCNUM w2 = mccguide32_w2;
MCNUM h2 = mccguide32_h2;
MCNUM l = mccguide32_l;
MCNUM R0 = mccguide32_R0;
MCNUM Qcx = mccguide32_Qcx;
MCNUM Qcy = mccguide32_Qcy;
MCNUM alphax = mccguide32_alphax;
MCNUM alphay = mccguide32_alphay;
MCNUM W = mccguide32_W;
MCNUM k = mccguide32_k;
MCNUM d = mccguide32_d;
MCNUM mx = mccguide32_mx;
MCNUM my = mccguide32_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 26001 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component guide34 [39] */
  mccoordschange(mcposrguide34, mcrotrguide34,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrguide34, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component guide34 (without coords transformations) */
  mcJumpTrace_guide34:
  SIG_MESSAGE("guide34 (Trace)");
  mcDEBUG_COMP("guide34")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(39,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[39]++;
  mcPCounter[39] += p;
  mcP2Counter[39] += p*p;
#define mccompcurname  guide34
#define mccompcurtype  Channeled_guide
#define mccompcurindex 39
#define w1c mccguide34_w1c
#define w2c mccguide34_w2c
#define ww mccguide34_ww
#define hh mccguide34_hh
#define whalf mccguide34_whalf
#define hhalf mccguide34_hhalf
#define lwhalf mccguide34_lwhalf
#define lhhalf mccguide34_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide34_w1;
MCNUM h1 = mccguide34_h1;
MCNUM w2 = mccguide34_w2;
MCNUM h2 = mccguide34_h2;
MCNUM l = mccguide34_l;
MCNUM R0 = mccguide34_R0;
MCNUM Qcx = mccguide34_Qcx;
MCNUM Qcy = mccguide34_Qcy;
MCNUM alphax = mccguide34_alphax;
MCNUM alphay = mccguide34_alphay;
MCNUM W = mccguide34_W;
MCNUM k = mccguide34_k;
MCNUM d = mccguide34_d;
MCNUM mx = mccguide34_mx;
MCNUM my = mccguide34_my;
#line 99 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double t1,t2;                                 /* Intersection times. */
  double av,ah,bv,bh,cv1,cv2,ch1,ch2,dd;        /* Intermediate values */
  double vdotn_v1,vdotn_v2,vdotn_h1,vdotn_h2;   /* Dot products. */
  int i;                                        /* Which mirror hit? */
  double q;                                     /* Q [1/AA] of reflection */
  double vlen2,nlen2;                           /* Vector lengths squared */
  double edge;
  double hadj;                                  /* Channel displacement */

  /* Propagate neutron to guide entrance. */
  PROP_Z0;
  if(x <= w1/-2.0 || x >= w1/2.0 || y <= -hhalf || y >= hhalf)
    ABSORB;
  /* Shift origin to center of channel hit (absorb if hit dividing walls) */
  x += w1/2.0;
  edge = floor(x/w1c)*w1c;
  if(x - edge > w1c - d)
  {
    x -= w1/2.0; /* Re-adjust origin */
    ABSORB;
  }
  x -= (edge + (w1c - d)/2.0);
  hadj = edge + (w1c - d)/2.0 - w1/2.0;
  for(;;)
  {
    /* Compute the dot products of v and n for the four mirrors. */
    av = l*vx; bv = ww*vz;
    ah = l*vy; bh = hh*vz;
    vdotn_v1 = bv + av;         /* Left vertical */
    vdotn_v2 = bv - av;         /* Right vertical */
    vdotn_h1 = bh + ah;         /* Lower horizontal */
    vdotn_h2 = bh - ah;         /* Upper horizontal */
    /* Compute the dot products of (O - r) and n as c1+c2 and c1-c2 */
    cv1 = -whalf*l - z*ww; cv2 = x*l;
    ch1 = -hhalf*l - z*hh; ch2 = y*l;
    /* Compute intersection times. */
    t1 = (l - z)/vz;
    i = 0;
    if(vdotn_v1 < 0 && (t2 = (cv1 - cv2)/vdotn_v1) < t1)
    {
      t1 = t2;
      i = 1;
    }
    if(vdotn_v2 < 0 && (t2 = (cv1 + cv2)/vdotn_v2) < t1)
    {
      t1 = t2;
      i = 2;
    }
    if(vdotn_h1 < 0 && (t2 = (ch1 - ch2)/vdotn_h1) < t1)
    {
      t1 = t2;
      i = 3;
    }
    if(vdotn_h2 < 0 && (t2 = (ch1 + ch2)/vdotn_h2) < t1)
    {
      t1 = t2;
      i = 4;
    }
    if(i == 0)
      break;                    /* Neutron left guide. */
    PROP_DT(t1);
    switch(i)
    {
      case 1:                   /* Left vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v1/sqrt(nlen2);
        dd = 2*vdotn_v1/nlen2;
        vx = vx - dd*l;
        vz = vz - dd*ww;
        break;
      case 2:                   /* Right vertical mirror */
        nlen2 = l*l + ww*ww;
        q = V2Q*(-2)*vdotn_v2/sqrt(nlen2);
        dd = 2*vdotn_v2/nlen2;
        vx = vx + dd*l;
        vz = vz - dd*ww;
        break;
      case 3:                   /* Lower horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h1/sqrt(nlen2);
        dd = 2*vdotn_h1/nlen2;
        vy = vy - dd*l;
        vz = vz - dd*hh;
        break;
      case 4:                   /* Upper horizontal mirror */
        nlen2 = l*l + hh*hh;
        q = V2Q*(-2)*vdotn_h2/sqrt(nlen2);
        dd = 2*vdotn_h2/nlen2;
        vy = vy + dd*l;
        vz = vz - dd*hh;
        break;
    }
    /* Now compute reflectivity. */
    if((i <= 2 && mx == 0) || (i > 2 && my == 0))
    {
      x += hadj; /* Re-adjust origin */
      ABSORB;
    }
    if((i <= 2 && q > Qcx) || (i > 2 && q > Qcy))
    {
      if (i <= 2)
      {
        double arg = (q - mx*Qcx)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphax*(q-Qcx));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      } else {
        double arg = (q - my*Qcy)/W;
        if(arg < 10)
          p *= .5*(1-tanh(arg))*(1-alphay*(q-Qcy));
        else
        {
          x += hadj; /* Re-adjust origin */
          ABSORB;                               /* Cutoff ~ 1E-10 */
        }
      }
    }
    p *= R0;
    x += hadj; SCATTER; x -= hadj;
  }
  x += hadj; /* Re-adjust origin */
}
#line 26207 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component E_det [40] */
  mccoordschange(mcposrE_det, mcrotrE_det,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrE_det, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component E_det (without coords transformations) */
  mcJumpTrace_E_det:
  SIG_MESSAGE("E_det (Trace)");
  mcDEBUG_COMP("E_det")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
  STORE_NEUTRON(40,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[40]++;
  mcPCounter[40] += p;
  mcP2Counter[40] += p*p;
#define mccompcurname  E_det
#define mccompcurtype  E_monitor
#define mccompcurindex 40
#define nchan mccE_det_nchan
#define filename mccE_det_filename
#define restore_neutron mccE_det_restore_neutron
#define E_N mccE_det_E_N
#define E_p mccE_det_E_p
#define E_p2 mccE_det_E_p2
#define S_p mccE_det_S_p
#define S_pE mccE_det_S_pE
#define S_pE2 mccE_det_S_pE2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccE_det_xmin;
MCNUM xmax = mccE_det_xmax;
MCNUM ymin = mccE_det_ymin;
MCNUM ymax = mccE_det_ymax;
MCNUM xwidth = mccE_det_xwidth;
MCNUM yheight = mccE_det_yheight;
MCNUM Emin = mccE_det_Emin;
MCNUM Emax = mccE_det_Emax;
#line 87 "/usr/local/lib/mcstas/monitors/E_monitor.comp"
{
    int i;
    double E;

    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax)
    {
      E = VS2E*(vx*vx + vy*vy + vz*vz);

      S_p += p;
      S_pE += p*E;
      S_pE2 += p*E*E;

      i = floor((E-Emin)*nchan/(Emax-Emin));
      if(i >= 0 && i < nchan)
      {
        E_N[i]++;
        E_p[i] += p;
        E_p2[i] += p*p;
        SCATTER;
      }
    }
    if (restore_neutron) {
      RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
    }
}
#line 26309 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef restore_neutron
#undef filename
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef sz
#undef sy
#undef sx
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component Sample_Arm [41] */
  mccoordschange(mcposrSample_Arm, mcrotrSample_Arm,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrSample_Arm, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component Sample_Arm (without coords transformations) */
  mcJumpTrace_Sample_Arm:
  SIG_MESSAGE("Sample_Arm (Trace)");
  mcDEBUG_COMP("Sample_Arm")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(41,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[41]++;
  mcPCounter[41] += p;
  mcP2Counter[41] += p*p;
#define mccompcurname  Sample_Arm
#define mccompcurtype  Arm
#define mccompcurindex 41
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component sample [42] */
  mccoordschange(mcposrsample, mcrotrsample,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrsample, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component sample (without coords transformations) */
  mcJumpTrace_sample:
  SIG_MESSAGE("sample (Trace)");
  mcDEBUG_COMP("sample")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
  if (!mcSplit_sample) { /* STORE only the first time */
    STORE_NEUTRON(42,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  } else {
    RESTORE_NEUTRON(42,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp); }
  mcSplit_sample++; /* SPLIT number */
  mcScattered=0;
  mcNCounter[42]++;
  mcPCounter[42] += p;
  mcP2Counter[42] += p*p;
#define mccompcurname  sample
#define mccompcurtype  V_sample
#define mccompcurindex 42
#define StructVarsV mccsample_StructVarsV
#define VarsV mccsample_VarsV
{   /* Declarations of SETTING parameters. */
MCNUM radius_i = mccsample_radius_i;
MCNUM radius_o = mccsample_radius_o;
MCNUM h = mccsample_h;
MCNUM focus_r = mccsample_focus_r;
MCNUM pack = mccsample_pack;
MCNUM frac = mccsample_frac;
MCNUM f_QE = mccsample_f_QE;
MCNUM gamma = mccsample_gamma;
MCNUM target_x = mccsample_target_x;
MCNUM target_y = mccsample_target_y;
MCNUM target_z = mccsample_target_z;
MCNUM focus_xw = mccsample_focus_xw;
MCNUM focus_yh = mccsample_focus_yh;
MCNUM focus_aw = mccsample_focus_aw;
MCNUM focus_ah = mccsample_focus_ah;
MCNUM xwidth = mccsample_xwidth;
MCNUM yheight = mccsample_yheight;
MCNUM zthick = mccsample_zthick;
MCNUM rad_sphere = mccsample_rad_sphere;
MCNUM sig_a = mccsample_sig_a;
MCNUM sig_i = mccsample_sig_i;
MCNUM V0 = mccsample_V0;
int target_index = mccsample_target_index;
MCNUM multiples = mccsample_multiples;
#line 178 "/usr/local/lib/mcstas/samples/V_sample.comp"
{
  double t0, t3;                /* Entry/exit time for outer cylinder */
  double t1, t2;                /* Entry/exit time for inner cylinder */
  double v;                     /* Neutron velocity */
  double dt0, dt1, dt2, dt;     /* Flight times through sample */
  double l_full;                /* Flight path length for non-scattered neutron */
  double l_i, l_o=0;            /* Flight path lenght in/out for scattered neutron */
  double my_a=0;                  /* Velocity-dependent attenuation factor */
  double solid_angle=0;         /* Solid angle of target as seen from scattering point */
  double aim_x=0, aim_y=0, aim_z=1;   /* Position of target relative to scattering point */
  double v_i, v_f, E_i, E_f; /* initial and final energies and velocities */
  double dE;                 /* Energy transfer */
  int    intersect=0;

  if (VarsV.shapetyp == 2)
    intersect = sphere_intersect(&t0, &t3, x, y, z, vx, vy, vz, rad_sphere);
  else
    if (VarsV.shapetyp == 1)
      intersect = box_intersect(&t0, &t3, x, y, z, vx, vy, vz, xwidth, yheight, zthick);
  else
    intersect = cylinder_intersect(&t0, &t3, x, y, z, vx, vy, vz, radius_o, h);
  if(intersect)
  {
    if(t0 < 0) ABSORB; /* we already passed the sample; this is illegal */
    /* Neutron enters at t=t0. */
    if(VarsV.shapetyp == 1 || VarsV.shapetyp == 2)
      t1 = t2 = t3;
    else
      if(!radius_i || !cylinder_intersect(&t1, &t2, x, y, z, vx, vy, vz, radius_i, h))
        t1 = t2 = t3;

    dt0 = t1-t0;                /* Time in sample, ingoing */
    dt1 = t2-t1;                /* Time in hole */
    dt2 = t3-t2;                /* Time in sample, outgoing */
    v = sqrt(vx*vx + vy*vy + vz*vz);
    l_full = v * (dt0 + dt2);   /* Length of full path through sample */
    if (v) my_a = VarsV.my_a_v*(2200/v);

    if (frac >= 1 || rand01()<frac)          /* Scattering */
    {
      dt = rand01()*(dt0+dt2);    /* Time of scattering (relative to t0) */
      l_i = v*dt;                 /* Penetration in sample: scattering+abs */
      if (dt > dt0)
        dt += dt1;                /* jump to 2nd side of cylinder */

      PROP_DT(dt+t0);             /* Point of scattering */

      if ((VarsV.tx || VarsV.ty || VarsV.tz)) {
        aim_x = VarsV.tx-x;       /* Vector pointing at target (anal./det.) */
        aim_y = VarsV.ty-y;
        aim_z = VarsV.tz-z;
      }
      if(VarsV.aw && VarsV.ah) {
        randvec_target_rect_angular(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, VarsV.aw, VarsV.ah, ROT_A_CURRENT_COMP);
      } else if(VarsV.xw && VarsV.yh) {
        randvec_target_rect(&vx, &vy, &vz, &solid_angle,
          aim_x, aim_y, aim_z, VarsV.xw, VarsV.yh, ROT_A_CURRENT_COMP);
      } else {
        randvec_target_circle(&vx, &vy, &vz, &solid_angle, aim_x, aim_y, aim_z, focus_r);
      }
      NORM(vx, vy, vz);

      v_i = v;          /* Store initial velocity in case of quasielastic */
      if (rand01()<f_QE)	/* Quasielastic contribution */
	{
          E_i = VS2E*v_i*v_i;
          dE = gamma*tan(PI/2*randpm1());
          E_f = E_i + dE;
          if (E_f <= 0)
            ABSORB;
	  v_f = SE2V*sqrt(E_f);
          v = v_f;
	  /*          printf("vi: %g Ei: %g dE: %g Ef %g vf: %g v: %g \n",
		      v_i,E_i,dE,E_f,v_f,v); */
	}

      vx *= v;
      vy *= v;
      vz *= v;

      if(VarsV.shapetyp == 0) {
        if(!cylinder_intersect(&t0, &t3, x, y, z, vx, vy, vz, radius_o, h)) {
          /* ??? did not hit cylinder */
          printf("FATAL ERROR: Did not hit cylinder from inside.\n");
          exit(1);
        }
        dt = t3; /* outgoing point */
        if(cylinder_intersect(&t1, &t2, x, y, z, vx, vy, vz, radius_i, h) &&
           t2 > 0)
          dt -= (t2-t1);            /* Subtract hollow part */
      }
      else {
        if(VarsV.shapetyp == 1) {
	      if(!box_intersect(&t0, &t3, x, y, z, vx, vy, vz, xwidth, yheight, zthick)) {
            /* ??? did not hit box */
            printf("FATAL ERROR: Did not hit box from inside.\n");
            exit(1);
          }
          dt = t3;
        }
        else {
	      if(!sphere_intersect(&t0, &t3, x, y, z, vx, vy, vz, rad_sphere)) {
            /* ??? did not hit sphere */
            printf("FATAL ERROR: Did not hit sphere from inside.\n");
            exit(1);
          }
          dt = t3;  
        }
      }
      l_o = v*dt; /* trajectory after scattering point: absorption only */

      p *= v/v_i*l_full*VarsV.my_s*exp(-my_a*(l_i+v_i/v*l_o)-VarsV.my_s*l_i);
      if (!multiples) {
	/* If no "multiples", correct by applying scattering cross-sec and
	   implicitly "absorb" further scattering (as in PowderN) 
	   We are currently (august 2007) having a debate on which solution 
	   is the most reasonable */
	p *= exp(-VarsV.my_s*l_o);
      }
      /* We do not consider scattering from 2nd part (outgoing) */
      p /= 4*PI/solid_angle;
      p /= frac;

      /* Polarisation part (1/3 NSF, 2/3 SF) */
      sx *= -1.0/3.0;
      sy *= -1.0/3.0;
      sz *= -1.0/3.0;

      SCATTER;
    }
  else /* Transmitting; always elastic */
    {
      p *= exp(-(my_a+VarsV.my_s)*l_full);
      p /= (1-frac);
    }
  }
}
#line 26584 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef VarsV
#undef StructVarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
  if (floor(10) > 1) p /= floor(10); /* adapt weight for SPLITed neutron */
#undef sz
#undef sy
#undef sx
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component t_mon_detC [43] */
  mccoordschange(mcposrt_mon_detC, mcrotrt_mon_detC,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrt_mon_detC, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component t_mon_detC (without coords transformations) */
  mcJumpTrace_t_mon_detC:
  SIG_MESSAGE("t_mon_detC (Trace)");
  mcDEBUG_COMP("t_mon_detC")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
  STORE_NEUTRON(43,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[43]++;
  mcPCounter[43] += p;
  mcP2Counter[43] += p*p;
#define mccompcurname  t_mon_detC
#define mccompcurtype  Monitor_nD
#define mccompcurindex 43
#define options mcct_mon_detC_options
#define filename mcct_mon_detC_filename
#define user1 mcct_mon_detC_user1
#define user2 mcct_mon_detC_user2
#define user3 mcct_mon_detC_user3
#define username1 mcct_mon_detC_username1
#define username2 mcct_mon_detC_username2
#define username3 mcct_mon_detC_username3
#define DEFS mcct_mon_detC_DEFS
#define Vars mcct_mon_detC_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detC_xwidth;
MCNUM yheight = mcct_mon_detC_yheight;
MCNUM zthick = mcct_mon_detC_zthick;
MCNUM xmin = mcct_mon_detC_xmin;
MCNUM xmax = mcct_mon_detC_xmax;
MCNUM ymin = mcct_mon_detC_ymin;
MCNUM ymax = mcct_mon_detC_ymax;
MCNUM zmin = mcct_mon_detC_zmin;
MCNUM zmax = mcct_mon_detC_zmax;
MCNUM bins = mcct_mon_detC_bins;
MCNUM min = mcct_mon_detC_min;
MCNUM max = mcct_mon_detC_max;
MCNUM restore_neutron = mcct_mon_detC_restore_neutron;
#line 260 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  double  XY=0;
  double  t0 = 0;
  double  t1 = 0;
  double  pp;
  int     intersect   = 0;
  char    Flag_Restore = 0;

  if (user1 != FLT_MAX) Vars.UserVariable1 = user1;
  if (user2 != FLT_MAX) Vars.UserVariable2 = user2;
  if (user3 != FLT_MAX) Vars.UserVariable3 = user3;

  /* this is done automatically
    STORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  */

  if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SQUARE) /* square xy */
  {
    PROP_Z0;
    intersect = (x>=Vars.mxmin && x<=Vars.mxmax && y>=Vars.mymin && y<=Vars.mymax);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_DISK)   /* disk xy */
  {
    PROP_Z0;
    intersect = ((x*x + y*y) <= Vars.Sphere_Radius*Vars.Sphere_Radius);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) /* sphere */
  {
    intersect = sphere_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius);
  /*      intersect = (intersect && t0 > 0); */
  }
  else if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA)) /* cylinder */
  {
    intersect = cylinder_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius, Vars.Cylinder_Height);
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA) && (intersect != 1)) intersect = 0; /* remove top/bottom for banana */
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) /* box */
  {
    intersect = box_intersect(&t0, &t1, x, y, z, vx, vy, vz, fabs(Vars.mxmax-Vars.mxmin), fabs(Vars.mymax-Vars.mymin), fabs(Vars.mzmax-Vars.mzmin));
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_PREVIOUS) /* previous comp */
  { intersect = 1; }

  if (intersect)
  {
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA))
    {
      if (t0 < 0 && t1 > 0)
        t0 = t;  /* neutron was already inside ! */
      if (t1 < 0 && t0 > 0) /* neutron exit before entering !! */
        t1 = t;
      /* t0 is now time of incoming intersection with the sphere. */
      if ((Vars.Flag_Shape < 0) && (t1 > 0))
        PROP_DT(t1); /* t1 outgoing beam */
      else
        PROP_DT(t0); /* t0 incoming beam */
    }

    /* Now get the data to monitor: current or keep from PreMonitor */
    if (Vars.Flag_UsePreMonitor != 1)
    {
      Vars.cp = p;
      Vars.cx = x;
      Vars.cvx = vx;
      Vars.csx = sx;
      Vars.cy = y;
      Vars.cvy = vy;
      Vars.csy = sy;
      Vars.cz = z;
      Vars.cvz = vz;
      Vars.csz = sz;
      Vars.ct = t;
    }

    if ((Vars.He3_pressure > 0) && (t1 != t0) && ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX)))
    {
      XY = exp(-7.417*Vars.He3_pressure*fabs(t1-t0)*2*PI*K2V);
      /* will monitor the absorbed part */
      Vars.cp *= 1-XY;
      /* and modify the neutron weight after monitor, only remains 1-p_detect */
      p *= XY;
    }

    if (Vars.Flag_capture)
    {
      XY = sqrt(Vars.cvx*Vars.cvx+Vars.cvy*Vars.cvy+Vars.cvz*Vars.cvz);
      XY *= V2K;
      if (XY != 0) XY = 2*PI/XY; /* lambda. lambda(2200 m/2) = 1.7985 Angs  */
      Vars.cp *= XY/1.7985;
    }

    pp = Monitor_nD_Trace(&DEFS, &Vars);
    if (pp==0.0)
    { ABSORB;
    }
    else
    { Vars.Nsum++;
      Vars.psum += pp;
      Vars.p2sum += pp*pp;
      SCATTER;
    }

    /* now handles intermediate results saving */
    if ((Vars.Intermediate > 0) && (mcget_run_num() > Vars.IntermediateCnts))
    {
      Vars.IntermediateCnts += Vars.Intermediate*mcget_ncount();
      /* save results for all monitors in the simulation */
      mcsave(NULL);
    }
    if (Vars.Flag_parallel) /* back to neutron state before detection */
      Flag_Restore = 1;
  } /* end if intersection */
  else {
    if (Vars.Flag_Absorb && !Vars.Flag_parallel) ABSORB;
    else Flag_Restore = 1;  /* no intersection, back to previous state */
  }

  if (Flag_Restore)
  {
    RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  }
}
#line 26786 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef sz
#undef sy
#undef sx
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component t_mon_detB [44] */
  mccoordschange(mcposrt_mon_detB, mcrotrt_mon_detB,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrt_mon_detB, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component t_mon_detB (without coords transformations) */
  mcJumpTrace_t_mon_detB:
  SIG_MESSAGE("t_mon_detB (Trace)");
  mcDEBUG_COMP("t_mon_detB")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
  STORE_NEUTRON(44,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[44]++;
  mcPCounter[44] += p;
  mcP2Counter[44] += p*p;
#define mccompcurname  t_mon_detB
#define mccompcurtype  Monitor_nD
#define mccompcurindex 44
#define options mcct_mon_detB_options
#define filename mcct_mon_detB_filename
#define user1 mcct_mon_detB_user1
#define user2 mcct_mon_detB_user2
#define user3 mcct_mon_detB_user3
#define username1 mcct_mon_detB_username1
#define username2 mcct_mon_detB_username2
#define username3 mcct_mon_detB_username3
#define DEFS mcct_mon_detB_DEFS
#define Vars mcct_mon_detB_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detB_xwidth;
MCNUM yheight = mcct_mon_detB_yheight;
MCNUM zthick = mcct_mon_detB_zthick;
MCNUM xmin = mcct_mon_detB_xmin;
MCNUM xmax = mcct_mon_detB_xmax;
MCNUM ymin = mcct_mon_detB_ymin;
MCNUM ymax = mcct_mon_detB_ymax;
MCNUM zmin = mcct_mon_detB_zmin;
MCNUM zmax = mcct_mon_detB_zmax;
MCNUM bins = mcct_mon_detB_bins;
MCNUM min = mcct_mon_detB_min;
MCNUM max = mcct_mon_detB_max;
MCNUM restore_neutron = mcct_mon_detB_restore_neutron;
#line 260 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  double  XY=0;
  double  t0 = 0;
  double  t1 = 0;
  double  pp;
  int     intersect   = 0;
  char    Flag_Restore = 0;

  if (user1 != FLT_MAX) Vars.UserVariable1 = user1;
  if (user2 != FLT_MAX) Vars.UserVariable2 = user2;
  if (user3 != FLT_MAX) Vars.UserVariable3 = user3;

  /* this is done automatically
    STORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  */

  if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SQUARE) /* square xy */
  {
    PROP_Z0;
    intersect = (x>=Vars.mxmin && x<=Vars.mxmax && y>=Vars.mymin && y<=Vars.mymax);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_DISK)   /* disk xy */
  {
    PROP_Z0;
    intersect = ((x*x + y*y) <= Vars.Sphere_Radius*Vars.Sphere_Radius);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) /* sphere */
  {
    intersect = sphere_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius);
  /*      intersect = (intersect && t0 > 0); */
  }
  else if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA)) /* cylinder */
  {
    intersect = cylinder_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius, Vars.Cylinder_Height);
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA) && (intersect != 1)) intersect = 0; /* remove top/bottom for banana */
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) /* box */
  {
    intersect = box_intersect(&t0, &t1, x, y, z, vx, vy, vz, fabs(Vars.mxmax-Vars.mxmin), fabs(Vars.mymax-Vars.mymin), fabs(Vars.mzmax-Vars.mzmin));
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_PREVIOUS) /* previous comp */
  { intersect = 1; }

  if (intersect)
  {
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA))
    {
      if (t0 < 0 && t1 > 0)
        t0 = t;  /* neutron was already inside ! */
      if (t1 < 0 && t0 > 0) /* neutron exit before entering !! */
        t1 = t;
      /* t0 is now time of incoming intersection with the sphere. */
      if ((Vars.Flag_Shape < 0) && (t1 > 0))
        PROP_DT(t1); /* t1 outgoing beam */
      else
        PROP_DT(t0); /* t0 incoming beam */
    }

    /* Now get the data to monitor: current or keep from PreMonitor */
    if (Vars.Flag_UsePreMonitor != 1)
    {
      Vars.cp = p;
      Vars.cx = x;
      Vars.cvx = vx;
      Vars.csx = sx;
      Vars.cy = y;
      Vars.cvy = vy;
      Vars.csy = sy;
      Vars.cz = z;
      Vars.cvz = vz;
      Vars.csz = sz;
      Vars.ct = t;
    }

    if ((Vars.He3_pressure > 0) && (t1 != t0) && ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX)))
    {
      XY = exp(-7.417*Vars.He3_pressure*fabs(t1-t0)*2*PI*K2V);
      /* will monitor the absorbed part */
      Vars.cp *= 1-XY;
      /* and modify the neutron weight after monitor, only remains 1-p_detect */
      p *= XY;
    }

    if (Vars.Flag_capture)
    {
      XY = sqrt(Vars.cvx*Vars.cvx+Vars.cvy*Vars.cvy+Vars.cvz*Vars.cvz);
      XY *= V2K;
      if (XY != 0) XY = 2*PI/XY; /* lambda. lambda(2200 m/2) = 1.7985 Angs  */
      Vars.cp *= XY/1.7985;
    }

    pp = Monitor_nD_Trace(&DEFS, &Vars);
    if (pp==0.0)
    { ABSORB;
    }
    else
    { Vars.Nsum++;
      Vars.psum += pp;
      Vars.p2sum += pp*pp;
      SCATTER;
    }

    /* now handles intermediate results saving */
    if ((Vars.Intermediate > 0) && (mcget_run_num() > Vars.IntermediateCnts))
    {
      Vars.IntermediateCnts += Vars.Intermediate*mcget_ncount();
      /* save results for all monitors in the simulation */
      mcsave(NULL);
    }
    if (Vars.Flag_parallel) /* back to neutron state before detection */
      Flag_Restore = 1;
  } /* end if intersection */
  else {
    if (Vars.Flag_Absorb && !Vars.Flag_parallel) ABSORB;
    else Flag_Restore = 1;  /* no intersection, back to previous state */
  }

  if (Flag_Restore)
  {
    RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  }
}
#line 26995 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef sz
#undef sy
#undef sx
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component t_mon_detD [45] */
  mccoordschange(mcposrt_mon_detD, mcrotrt_mon_detD,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrt_mon_detD, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component t_mon_detD (without coords transformations) */
  mcJumpTrace_t_mon_detD:
  SIG_MESSAGE("t_mon_detD (Trace)");
  mcDEBUG_COMP("t_mon_detD")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
#define sx mcnlsx
#define sy mcnlsy
#define sz mcnlsz
  STORE_NEUTRON(45,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[45]++;
  mcPCounter[45] += p;
  mcP2Counter[45] += p*p;
#define mccompcurname  t_mon_detD
#define mccompcurtype  Monitor_nD
#define mccompcurindex 45
#define options mcct_mon_detD_options
#define filename mcct_mon_detD_filename
#define user1 mcct_mon_detD_user1
#define user2 mcct_mon_detD_user2
#define user3 mcct_mon_detD_user3
#define username1 mcct_mon_detD_username1
#define username2 mcct_mon_detD_username2
#define username3 mcct_mon_detD_username3
#define DEFS mcct_mon_detD_DEFS
#define Vars mcct_mon_detD_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detD_xwidth;
MCNUM yheight = mcct_mon_detD_yheight;
MCNUM zthick = mcct_mon_detD_zthick;
MCNUM xmin = mcct_mon_detD_xmin;
MCNUM xmax = mcct_mon_detD_xmax;
MCNUM ymin = mcct_mon_detD_ymin;
MCNUM ymax = mcct_mon_detD_ymax;
MCNUM zmin = mcct_mon_detD_zmin;
MCNUM zmax = mcct_mon_detD_zmax;
MCNUM bins = mcct_mon_detD_bins;
MCNUM min = mcct_mon_detD_min;
MCNUM max = mcct_mon_detD_max;
MCNUM restore_neutron = mcct_mon_detD_restore_neutron;
#line 260 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  double  XY=0;
  double  t0 = 0;
  double  t1 = 0;
  double  pp;
  int     intersect   = 0;
  char    Flag_Restore = 0;

  if (user1 != FLT_MAX) Vars.UserVariable1 = user1;
  if (user2 != FLT_MAX) Vars.UserVariable2 = user2;
  if (user3 != FLT_MAX) Vars.UserVariable3 = user3;

  /* this is done automatically
    STORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  */

  if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SQUARE) /* square xy */
  {
    PROP_Z0;
    intersect = (x>=Vars.mxmin && x<=Vars.mxmax && y>=Vars.mymin && y<=Vars.mymax);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_DISK)   /* disk xy */
  {
    PROP_Z0;
    intersect = ((x*x + y*y) <= Vars.Sphere_Radius*Vars.Sphere_Radius);
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) /* sphere */
  {
    intersect = sphere_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius);
  /*      intersect = (intersect && t0 > 0); */
  }
  else if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA)) /* cylinder */
  {
    intersect = cylinder_intersect(&t0, &t1, x, y, z, vx, vy, vz, Vars.Sphere_Radius, Vars.Cylinder_Height);
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA) && (intersect != 1)) intersect = 0; /* remove top/bottom for banana */
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) /* box */
  {
    intersect = box_intersect(&t0, &t1, x, y, z, vx, vy, vz, fabs(Vars.mxmax-Vars.mxmin), fabs(Vars.mymax-Vars.mymin), fabs(Vars.mzmax-Vars.mzmin));
  }
  else if (abs(Vars.Flag_Shape) == DEFS.SHAPE_PREVIOUS) /* previous comp */
  { intersect = 1; }

  if (intersect)
  {
    if ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BANANA))
    {
      if (t0 < 0 && t1 > 0)
        t0 = t;  /* neutron was already inside ! */
      if (t1 < 0 && t0 > 0) /* neutron exit before entering !! */
        t1 = t;
      /* t0 is now time of incoming intersection with the sphere. */
      if ((Vars.Flag_Shape < 0) && (t1 > 0))
        PROP_DT(t1); /* t1 outgoing beam */
      else
        PROP_DT(t0); /* t0 incoming beam */
    }

    /* Now get the data to monitor: current or keep from PreMonitor */
    if (Vars.Flag_UsePreMonitor != 1)
    {
      Vars.cp = p;
      Vars.cx = x;
      Vars.cvx = vx;
      Vars.csx = sx;
      Vars.cy = y;
      Vars.cvy = vy;
      Vars.csy = sy;
      Vars.cz = z;
      Vars.cvz = vz;
      Vars.csz = sz;
      Vars.ct = t;
    }

    if ((Vars.He3_pressure > 0) && (t1 != t0) && ((abs(Vars.Flag_Shape) == DEFS.SHAPE_SPHERE) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_CYLIND) || (abs(Vars.Flag_Shape) == DEFS.SHAPE_BOX)))
    {
      XY = exp(-7.417*Vars.He3_pressure*fabs(t1-t0)*2*PI*K2V);
      /* will monitor the absorbed part */
      Vars.cp *= 1-XY;
      /* and modify the neutron weight after monitor, only remains 1-p_detect */
      p *= XY;
    }

    if (Vars.Flag_capture)
    {
      XY = sqrt(Vars.cvx*Vars.cvx+Vars.cvy*Vars.cvy+Vars.cvz*Vars.cvz);
      XY *= V2K;
      if (XY != 0) XY = 2*PI/XY; /* lambda. lambda(2200 m/2) = 1.7985 Angs  */
      Vars.cp *= XY/1.7985;
    }

    pp = Monitor_nD_Trace(&DEFS, &Vars);
    if (pp==0.0)
    { ABSORB;
    }
    else
    { Vars.Nsum++;
      Vars.psum += pp;
      Vars.p2sum += pp*pp;
      SCATTER;
    }

    /* now handles intermediate results saving */
    if ((Vars.Intermediate > 0) && (mcget_run_num() > Vars.IntermediateCnts))
    {
      Vars.IntermediateCnts += Vars.Intermediate*mcget_ncount();
      /* save results for all monitors in the simulation */
      mcsave(NULL);
    }
    if (Vars.Flag_parallel) /* back to neutron state before detection */
      Flag_Restore = 1;
  } /* end if intersection */
  else {
    if (Vars.Flag_Absorb && !Vars.Flag_parallel) ABSORB;
    else Flag_Restore = 1;  /* no intersection, back to previous state */
  }

  if (Flag_Restore)
  {
    RESTORE_NEUTRON(INDEX_CURRENT_COMP, x, y, z, vx, vy, vz, t, sx, sy, sz, p);
  }
}
#line 27204 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef sz
#undef sy
#undef sx
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  /* TRACE Component t_mon2 [46] */
  mccoordschange(mcposrt_mon2, mcrotrt_mon2,
    &mcnlx, &mcnly, &mcnlz,
    &mcnlvx, &mcnlvy, &mcnlvz,
    &mcnlt, &mcnlsx, &mcnlsy);
  mccoordschange_polarisation(mcrotrt_mon2, &mcnlsx, &mcnlsy, &mcnlsz);
  /* define label inside component t_mon2 (without coords transformations) */
  mcJumpTrace_t_mon2:
  SIG_MESSAGE("t_mon2 (Trace)");
  mcDEBUG_COMP("t_mon2")
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
#define x mcnlx
#define y mcnly
#define z mcnlz
#define vx mcnlvx
#define vy mcnlvy
#define vz mcnlvz
#define t mcnlt
#define s1 mcnlsx
#define s2 mcnlsy
#define p mcnlp
  STORE_NEUTRON(46,mcnlx, mcnly, mcnlz, mcnlvx,mcnlvy,mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlsz, mcnlp);
  mcScattered=0;
  mcNCounter[46]++;
  mcPCounter[46] += p;
  mcP2Counter[46] += p*p;
#define mccompcurname  t_mon2
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 46
#define nchan mcct_mon2_nchan
#define TOF_N mcct_mon2_TOF_N
#define TOF_p mcct_mon2_TOF_p
#define TOF_p2 mcct_mon2_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mcct_mon2_xmin;
MCNUM xmax = mcct_mon2_xmax;
MCNUM ymin = mcct_mon2_ymin;
MCNUM ymax = mcct_mon2_ymax;
MCNUM tmin = mcct_mon2_tmin;
MCNUM tmax = mcct_mon2_tmax;
char* filename = mcct_mon2_filename;
#line 59 "TOF_monitor2.comp"
{
    int i;
     double dt;
     dt=(tmax-tmin)/nchan;
    PROP_Z0;
    if (x>xmin && x<xmax && y>ymin && y<ymax && t>=tmin && t<=tmax)
    {
    /* printf("dt %g\n",dt);*/
      i = floor((t-tmin)/dt);              /* Bin number */
      if(i >= nchan) i = nchan - 1;
      if(i < 0)
      {
        printf("FATAL ERROR: negative time-of-flight.\n");
        exit(1);
      }
      TOF_N[i]++;
      TOF_p[i] += p;
      TOF_p2[i] += p*p;
      //printf("i: %i TOF_p: %g TOF_p2:%g\n",i,TOF_p[i],TOF_p2[i]);
    }
}
#line 27297 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex
#undef p
#undef s2
#undef s1
#undef t
#undef vz
#undef vy
#undef vx
#undef z
#undef y
#undef x
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)

  mcabsorbAll:
  /* SPLIT loops in reverse order */
  if (mcSplit_sample && mcSplit_sample < (10)) {
    goto mcJumpTrace_sample;
  }
    else mcSplit_sample=0;

  mcDEBUG_LEAVE()
  mcDEBUG_STATE(mcnlx, mcnly, mcnlz, mcnlvx, mcnlvy, mcnlvz,mcnlt,mcnlsx,mcnlsy, mcnlp)
  /* Copy neutron state to global variables. */
  mcnx = mcnlx;
  mcny = mcnly;
  mcnz = mcnlz;
  mcnvx = mcnlvx;
  mcnvy = mcnlvy;
  mcnvz = mcnlvz;
  mcnt = mcnlt;
  mcnsx = mcnlsx;
  mcnsy = mcnlsy;
  mcnsz = mcnlsz;
  mcnp = mcnlp;
} /* end trace */

void mcsave(FILE *handle) {
  if (!handle) mcsiminfo_init(NULL);
  /* User component SAVE code. */

  /* User SAVE code for component 'arm1'. */
  SIG_MESSAGE("arm1 (Save)");
#define mccompcurname  arm1
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define profile mccarm1_profile
#define IntermediateCnts mccarm1_IntermediateCnts
#define StartTime mccarm1_StartTime
#define EndTime mccarm1_EndTime
{   /* Declarations of SETTING parameters. */
MCNUM percent = mccarm1_percent;
MCNUM flag_save = mccarm1_flag_save;
MCNUM minutes = mccarm1_minutes;
#line 108 "/usr/local/lib/mcstas/misc/Progress_bar.comp"
{
  MPI_MASTER(fprintf(stdout, "\nSave [%s]\n", mcinstrument_name););
  if (profile) {
    char filename[256];
    if (!strlen(profile)) strcpy(filename, mcinstrument_name);
    else strcpy(filename, profile);
    DETECTOR_OUT_1D(
        "Intensity profiler",
        "Component index [1]",
        "Intensity",
        "prof", 1, mcNUMCOMP, mcNUMCOMP-1,
        &mcNCounter[1],&mcPCounter[1],&mcP2Counter[1],
        filename);

  }
}
#line 27370 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef profile
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 't_check1'. */
  SIG_MESSAGE("t_check1 (Save)");
#define mccompcurname  t_check1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 17
#define nchan mcct_check1_nchan
#define TOF_N mcct_check1_TOF_N
#define TOF_p mcct_check1_TOF_p
#define TOF_p2 mcct_check1_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mcct_check1_xmin;
MCNUM xmax = mcct_check1_xmax;
MCNUM ymin = mcct_check1_ymin;
MCNUM ymax = mcct_check1_ymax;
MCNUM tmin = mcct_check1_tmin;
MCNUM tmax = mcct_check1_tmax;
char* filename = mcct_check1_filename;
#line 81 "TOF_monitor2.comp"
{
    double dt;
     dt=(tmax-tmin)/nchan;
    DETECTOR_OUT_1D(
        "Time-of-flight monitor",
        "Time-of-flight [\\gms]",
        "Intensity",
        "t", tmin*1.0e6, (tmin+nchan*(double)dt)*1.0e6, nchan,
        &TOF_N[0],&TOF_p[0],&TOF_p2[0],
        filename);
}
#line 27409 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'Monitor1'. */
  SIG_MESSAGE("Monitor1 (Save)");
#define mccompcurname  Monitor1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 35
#define nchan mccMonitor1_nchan
#define TOF_N mccMonitor1_TOF_N
#define TOF_p mccMonitor1_TOF_p
#define TOF_p2 mccMonitor1_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccMonitor1_xmin;
MCNUM xmax = mccMonitor1_xmax;
MCNUM ymin = mccMonitor1_ymin;
MCNUM ymax = mccMonitor1_ymax;
MCNUM tmin = mccMonitor1_tmin;
MCNUM tmax = mccMonitor1_tmax;
char* filename = mccMonitor1_filename;
#line 81 "TOF_monitor2.comp"
{
    double dt;
     dt=(tmax-tmin)/nchan;
    DETECTOR_OUT_1D(
        "Time-of-flight monitor",
        "Time-of-flight [\\gms]",
        "Intensity",
        "t", tmin*1.0e6, (tmin+nchan*(double)dt)*1.0e6, nchan,
        &TOF_N[0],&TOF_p[0],&TOF_p2[0],
        filename);
}
#line 27448 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 'E_det'. */
  SIG_MESSAGE("E_det (Save)");
#define mccompcurname  E_det
#define mccompcurtype  E_monitor
#define mccompcurindex 40
#define nchan mccE_det_nchan
#define filename mccE_det_filename
#define restore_neutron mccE_det_restore_neutron
#define E_N mccE_det_E_N
#define E_p mccE_det_E_p
#define E_p2 mccE_det_E_p2
#define S_p mccE_det_S_p
#define S_pE mccE_det_S_pE
#define S_pE2 mccE_det_S_pE2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccE_det_xmin;
MCNUM xmax = mccE_det_xmax;
MCNUM ymin = mccE_det_ymin;
MCNUM ymax = mccE_det_ymax;
MCNUM xwidth = mccE_det_xwidth;
MCNUM yheight = mccE_det_yheight;
MCNUM Emin = mccE_det_Emin;
MCNUM Emax = mccE_det_Emax;
#line 114 "/usr/local/lib/mcstas/monitors/E_monitor.comp"
{
    DETECTOR_OUT_1D(
        "Energy monitor",
        "Energy [meV]",
        "Intensity",
        "E", Emin, Emax, nchan,
        &E_N[0],&E_p[0],&E_p2[0],
        filename);
    if (S_p) printf("<E> : %g meV , E-width : %g meV \n",
     S_pE/S_p,sqrt(S_pE2/S_p - S_pE*S_pE/(S_p*S_p)) );
}
#line 27493 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef restore_neutron
#undef filename
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 't_mon_detC'. */
  SIG_MESSAGE("t_mon_detC (Save)");
#define mccompcurname  t_mon_detC
#define mccompcurtype  Monitor_nD
#define mccompcurindex 43
#define options mcct_mon_detC_options
#define filename mcct_mon_detC_filename
#define user1 mcct_mon_detC_user1
#define user2 mcct_mon_detC_user2
#define user3 mcct_mon_detC_user3
#define username1 mcct_mon_detC_username1
#define username2 mcct_mon_detC_username2
#define username3 mcct_mon_detC_username3
#define DEFS mcct_mon_detC_DEFS
#define Vars mcct_mon_detC_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detC_xwidth;
MCNUM yheight = mcct_mon_detC_yheight;
MCNUM zthick = mcct_mon_detC_zthick;
MCNUM xmin = mcct_mon_detC_xmin;
MCNUM xmax = mcct_mon_detC_xmax;
MCNUM ymin = mcct_mon_detC_ymin;
MCNUM ymax = mcct_mon_detC_ymax;
MCNUM zmin = mcct_mon_detC_zmin;
MCNUM zmax = mcct_mon_detC_zmax;
MCNUM bins = mcct_mon_detC_bins;
MCNUM min = mcct_mon_detC_min;
MCNUM max = mcct_mon_detC_max;
MCNUM restore_neutron = mcct_mon_detC_restore_neutron;
#line 384 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  /* save results, but do not free pointers */
  Monitor_nD_Save(&DEFS, &Vars);
}
#line 27542 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 't_mon_detB'. */
  SIG_MESSAGE("t_mon_detB (Save)");
#define mccompcurname  t_mon_detB
#define mccompcurtype  Monitor_nD
#define mccompcurindex 44
#define options mcct_mon_detB_options
#define filename mcct_mon_detB_filename
#define user1 mcct_mon_detB_user1
#define user2 mcct_mon_detB_user2
#define user3 mcct_mon_detB_user3
#define username1 mcct_mon_detB_username1
#define username2 mcct_mon_detB_username2
#define username3 mcct_mon_detB_username3
#define DEFS mcct_mon_detB_DEFS
#define Vars mcct_mon_detB_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detB_xwidth;
MCNUM yheight = mcct_mon_detB_yheight;
MCNUM zthick = mcct_mon_detB_zthick;
MCNUM xmin = mcct_mon_detB_xmin;
MCNUM xmax = mcct_mon_detB_xmax;
MCNUM ymin = mcct_mon_detB_ymin;
MCNUM ymax = mcct_mon_detB_ymax;
MCNUM zmin = mcct_mon_detB_zmin;
MCNUM zmax = mcct_mon_detB_zmax;
MCNUM bins = mcct_mon_detB_bins;
MCNUM min = mcct_mon_detB_min;
MCNUM max = mcct_mon_detB_max;
MCNUM restore_neutron = mcct_mon_detB_restore_neutron;
#line 384 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  /* save results, but do not free pointers */
  Monitor_nD_Save(&DEFS, &Vars);
}
#line 27592 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 't_mon_detD'. */
  SIG_MESSAGE("t_mon_detD (Save)");
#define mccompcurname  t_mon_detD
#define mccompcurtype  Monitor_nD
#define mccompcurindex 45
#define options mcct_mon_detD_options
#define filename mcct_mon_detD_filename
#define user1 mcct_mon_detD_user1
#define user2 mcct_mon_detD_user2
#define user3 mcct_mon_detD_user3
#define username1 mcct_mon_detD_username1
#define username2 mcct_mon_detD_username2
#define username3 mcct_mon_detD_username3
#define DEFS mcct_mon_detD_DEFS
#define Vars mcct_mon_detD_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detD_xwidth;
MCNUM yheight = mcct_mon_detD_yheight;
MCNUM zthick = mcct_mon_detD_zthick;
MCNUM xmin = mcct_mon_detD_xmin;
MCNUM xmax = mcct_mon_detD_xmax;
MCNUM ymin = mcct_mon_detD_ymin;
MCNUM ymax = mcct_mon_detD_ymax;
MCNUM zmin = mcct_mon_detD_zmin;
MCNUM zmax = mcct_mon_detD_zmax;
MCNUM bins = mcct_mon_detD_bins;
MCNUM min = mcct_mon_detD_min;
MCNUM max = mcct_mon_detD_max;
MCNUM restore_neutron = mcct_mon_detD_restore_neutron;
#line 384 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  /* save results, but do not free pointers */
  Monitor_nD_Save(&DEFS, &Vars);
}
#line 27642 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* User SAVE code for component 't_mon2'. */
  SIG_MESSAGE("t_mon2 (Save)");
#define mccompcurname  t_mon2
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 46
#define nchan mcct_mon2_nchan
#define TOF_N mcct_mon2_TOF_N
#define TOF_p mcct_mon2_TOF_p
#define TOF_p2 mcct_mon2_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mcct_mon2_xmin;
MCNUM xmax = mcct_mon2_xmax;
MCNUM ymin = mcct_mon2_ymin;
MCNUM ymax = mcct_mon2_ymax;
MCNUM tmin = mcct_mon2_tmin;
MCNUM tmax = mcct_mon2_tmax;
char* filename = mcct_mon2_filename;
#line 81 "TOF_monitor2.comp"
{
    double dt;
     dt=(tmax-tmin)/nchan;
    DETECTOR_OUT_1D(
        "Time-of-flight monitor",
        "Time-of-flight [\\gms]",
        "Intensity",
        "t", tmin*1.0e6, (tmin+nchan*(double)dt)*1.0e6, nchan,
        &TOF_N[0],&TOF_p[0],&TOF_p2[0],
        filename);
}
#line 27687 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  if (!handle) mcsiminfo_close(); 
} /* end save */
void mcfinally(void) {
  /* User component FINALLY code. */
  mcsiminfo_init(NULL);
  mcsave(mcsiminfo_file); /* save data when simulation ends */

  /* User FINALLY code for component 'arm1'. */
  SIG_MESSAGE("arm1 (Finally)");
#define mccompcurname  arm1
#define mccompcurtype  Progress_bar
#define mccompcurindex 1
#define profile mccarm1_profile
#define IntermediateCnts mccarm1_IntermediateCnts
#define StartTime mccarm1_StartTime
#define EndTime mccarm1_EndTime
{   /* Declarations of SETTING parameters. */
MCNUM percent = mccarm1_percent;
MCNUM flag_save = mccarm1_flag_save;
MCNUM minutes = mccarm1_minutes;
#line 126 "/usr/local/lib/mcstas/misc/Progress_bar.comp"
{
  time_t NowTime;
  time(&NowTime);
  fprintf(stdout, "\nFinally. Time: ");
  if (difftime(NowTime,StartTime) < 60.0)
    fprintf(stdout, "%g [s] ", difftime(NowTime,StartTime));
  else if (difftime(NowTime,StartTime) > 3600.0)
    fprintf(stdout, "%g [h] ", difftime(NowTime,StartTime)/3660.0);
  else
    fprintf(stdout, "%g [min] ", difftime(NowTime,StartTime)/60.0);
  fprintf(stdout, "\n");
}
#line 27730 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef EndTime
#undef StartTime
#undef IntermediateCnts
#undef profile
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[1]) fprintf(stderr, "Warning: No neutron could reach Component[1] arm1\n");
    if (mcAbsorbProp[1]) fprintf(stderr, "Warning: %g events were removed in Component[1] arm1\n""         (negative time, rounding errors).\n", mcAbsorbProp[1]);
  /* User FINALLY code for component 'mod'. */
  SIG_MESSAGE("mod (Finally)");
#define mccompcurname  mod
#define mccompcurtype  SNS_source
#define mccompcurindex 2
#define S_filename mccmod_S_filename
#define hdiv mccmod_hdiv
#define vdiv mccmod_vdiv
#define p_in mccmod_p_in
{   /* Declarations of SETTING parameters. */
MCNUM width = mccmod_width;
MCNUM height = mccmod_height;
MCNUM dist = mccmod_dist;
MCNUM xw = mccmod_xw;
MCNUM yh = mccmod_yh;
MCNUM Emin = mccmod_Emin;
MCNUM Emax = mccmod_Emax;
#line 523 "SNS_source.comp"
{
  int idxf;
  free(txval);free(tyval);free(tPvec);
  free(inxvec);free(inyvec);free(Pvec);free(tcol);free(Ecol);
  for(idxf=0;idxf<200;idxf++){
    free(Ptmat[idxf]);
  } 
  free(Ptmat); 
  
}
#line 27770 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef p_in
#undef vdiv
#undef hdiv
#undef S_filename
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[2]) fprintf(stderr, "Warning: No neutron could reach Component[2] mod\n");
    if (mcAbsorbProp[2]) fprintf(stderr, "Warning: %g events were removed in Component[2] mod\n""         (negative time, rounding errors).\n", mcAbsorbProp[2]);
    if (!mcNCounter[3]) fprintf(stderr, "Warning: No neutron could reach Component[3] core_ves\n");
    if (mcAbsorbProp[3]) fprintf(stderr, "Warning: %g events were removed in Component[3] core_ves\n""         (negative time, rounding errors).\n", mcAbsorbProp[3]);
    if (!mcNCounter[4]) fprintf(stderr, "Warning: No neutron could reach Component[4] shutter_guide\n");
    if (mcAbsorbProp[4]) fprintf(stderr, "Warning: %g events were removed in Component[4] shutter_guide\n""         (negative time, rounding errors).\n", mcAbsorbProp[4]);
    if (!mcNCounter[5]) fprintf(stderr, "Warning: No neutron could reach Component[5] guide1\n");
    if (mcAbsorbProp[5]) fprintf(stderr, "Warning: %g events were removed in Component[5] guide1\n""         (negative time, rounding errors).\n", mcAbsorbProp[5]);
    if (!mcNCounter[6]) fprintf(stderr, "Warning: No neutron could reach Component[6] guide2\n");
    if (mcAbsorbProp[6]) fprintf(stderr, "Warning: %g events were removed in Component[6] guide2\n""         (negative time, rounding errors).\n", mcAbsorbProp[6]);
    if (!mcNCounter[7]) fprintf(stderr, "Warning: No neutron could reach Component[7] guide3\n");
    if (mcAbsorbProp[7]) fprintf(stderr, "Warning: %g events were removed in Component[7] guide3\n""         (negative time, rounding errors).\n", mcAbsorbProp[7]);
    if (!mcNCounter[8]) fprintf(stderr, "Warning: No neutron could reach Component[8] guide4\n");
    if (mcAbsorbProp[8]) fprintf(stderr, "Warning: %g events were removed in Component[8] guide4\n""         (negative time, rounding errors).\n", mcAbsorbProp[8]);
    if (!mcNCounter[9]) fprintf(stderr, "Warning: No neutron could reach Component[9] guide5\n");
    if (mcAbsorbProp[9]) fprintf(stderr, "Warning: %g events were removed in Component[9] guide5\n""         (negative time, rounding errors).\n", mcAbsorbProp[9]);
    if (!mcNCounter[10]) fprintf(stderr, "Warning: No neutron could reach Component[10] guide6\n");
    if (mcAbsorbProp[10]) fprintf(stderr, "Warning: %g events were removed in Component[10] guide6\n""         (negative time, rounding errors).\n", mcAbsorbProp[10]);
    if (!mcNCounter[11]) fprintf(stderr, "Warning: No neutron could reach Component[11] guide7\n");
    if (mcAbsorbProp[11]) fprintf(stderr, "Warning: %g events were removed in Component[11] guide7\n""         (negative time, rounding errors).\n", mcAbsorbProp[11]);
    if (!mcNCounter[12]) fprintf(stderr, "Warning: No neutron could reach Component[12] guide8\n");
    if (mcAbsorbProp[12]) fprintf(stderr, "Warning: %g events were removed in Component[12] guide8\n""         (negative time, rounding errors).\n", mcAbsorbProp[12]);
    if (!mcNCounter[13]) fprintf(stderr, "Warning: No neutron could reach Component[13] guide9\n");
    if (mcAbsorbProp[13]) fprintf(stderr, "Warning: %g events were removed in Component[13] guide9\n""         (negative time, rounding errors).\n", mcAbsorbProp[13]);
    if (!mcNCounter[14]) fprintf(stderr, "Warning: No neutron could reach Component[14] guide10\n");
    if (mcAbsorbProp[14]) fprintf(stderr, "Warning: %g events were removed in Component[14] guide10\n""         (negative time, rounding errors).\n", mcAbsorbProp[14]);
    if (!mcNCounter[15]) fprintf(stderr, "Warning: No neutron could reach Component[15] guide11\n");
    if (mcAbsorbProp[15]) fprintf(stderr, "Warning: %g events were removed in Component[15] guide11\n""         (negative time, rounding errors).\n", mcAbsorbProp[15]);
    if (!mcNCounter[16]) fprintf(stderr, "Warning: No neutron could reach Component[16] t0_chopp\n");
    if (mcAbsorbProp[16]) fprintf(stderr, "Warning: %g events were removed in Component[16] t0_chopp\n""         (negative time, rounding errors).\n", mcAbsorbProp[16]);
    if (!mcNCounter[17]) fprintf(stderr, "Warning: No neutron could reach Component[17] t_check1\n");
    if (mcAbsorbProp[17]) fprintf(stderr, "Warning: %g events were removed in Component[17] t_check1\n""         (negative time, rounding errors).\n", mcAbsorbProp[17]);
    if (!mcNCounter[18]) fprintf(stderr, "Warning: No neutron could reach Component[18] guide13\n");
    if (mcAbsorbProp[18]) fprintf(stderr, "Warning: %g events were removed in Component[18] guide13\n""         (negative time, rounding errors).\n", mcAbsorbProp[18]);
    if (!mcNCounter[19]) fprintf(stderr, "Warning: No neutron could reach Component[19] guide14\n");
    if (mcAbsorbProp[19]) fprintf(stderr, "Warning: %g events were removed in Component[19] guide14\n""         (negative time, rounding errors).\n", mcAbsorbProp[19]);
    if (!mcNCounter[20]) fprintf(stderr, "Warning: No neutron could reach Component[20] guide15\n");
    if (mcAbsorbProp[20]) fprintf(stderr, "Warning: %g events were removed in Component[20] guide15\n""         (negative time, rounding errors).\n", mcAbsorbProp[20]);
    if (!mcNCounter[21]) fprintf(stderr, "Warning: No neutron could reach Component[21] guide16\n");
    if (mcAbsorbProp[21]) fprintf(stderr, "Warning: %g events were removed in Component[21] guide16\n""         (negative time, rounding errors).\n", mcAbsorbProp[21]);
    if (!mcNCounter[22]) fprintf(stderr, "Warning: No neutron could reach Component[22] guide17\n");
    if (mcAbsorbProp[22]) fprintf(stderr, "Warning: %g events were removed in Component[22] guide17\n""         (negative time, rounding errors).\n", mcAbsorbProp[22]);
    if (!mcNCounter[23]) fprintf(stderr, "Warning: No neutron could reach Component[23] guide18\n");
    if (mcAbsorbProp[23]) fprintf(stderr, "Warning: %g events were removed in Component[23] guide18\n""         (negative time, rounding errors).\n", mcAbsorbProp[23]);
    if (!mcNCounter[24]) fprintf(stderr, "Warning: No neutron could reach Component[24] guide19\n");
    if (mcAbsorbProp[24]) fprintf(stderr, "Warning: %g events were removed in Component[24] guide19\n""         (negative time, rounding errors).\n", mcAbsorbProp[24]);
    if (!mcNCounter[25]) fprintf(stderr, "Warning: No neutron could reach Component[25] guide20\n");
    if (mcAbsorbProp[25]) fprintf(stderr, "Warning: %g events were removed in Component[25] guide20\n""         (negative time, rounding errors).\n", mcAbsorbProp[25]);
    if (!mcNCounter[26]) fprintf(stderr, "Warning: No neutron could reach Component[26] guide21\n");
    if (mcAbsorbProp[26]) fprintf(stderr, "Warning: %g events were removed in Component[26] guide21\n""         (negative time, rounding errors).\n", mcAbsorbProp[26]);
    if (!mcNCounter[27]) fprintf(stderr, "Warning: No neutron could reach Component[27] guide22\n");
    if (mcAbsorbProp[27]) fprintf(stderr, "Warning: %g events were removed in Component[27] guide22\n""         (negative time, rounding errors).\n", mcAbsorbProp[27]);
    if (!mcNCounter[28]) fprintf(stderr, "Warning: No neutron could reach Component[28] guide23\n");
    if (mcAbsorbProp[28]) fprintf(stderr, "Warning: %g events were removed in Component[28] guide23\n""         (negative time, rounding errors).\n", mcAbsorbProp[28]);
    if (!mcNCounter[29]) fprintf(stderr, "Warning: No neutron could reach Component[29] guide24\n");
    if (mcAbsorbProp[29]) fprintf(stderr, "Warning: %g events were removed in Component[29] guide24\n""         (negative time, rounding errors).\n", mcAbsorbProp[29]);
    if (!mcNCounter[30]) fprintf(stderr, "Warning: No neutron could reach Component[30] guide25\n");
    if (mcAbsorbProp[30]) fprintf(stderr, "Warning: %g events were removed in Component[30] guide25\n""         (negative time, rounding errors).\n", mcAbsorbProp[30]);
    if (!mcNCounter[31]) fprintf(stderr, "Warning: No neutron could reach Component[31] guide26\n");
    if (mcAbsorbProp[31]) fprintf(stderr, "Warning: %g events were removed in Component[31] guide26\n""         (negative time, rounding errors).\n", mcAbsorbProp[31]);
    if (!mcNCounter[32]) fprintf(stderr, "Warning: No neutron could reach Component[32] guide27\n");
    if (mcAbsorbProp[32]) fprintf(stderr, "Warning: %g events were removed in Component[32] guide27\n""         (negative time, rounding errors).\n", mcAbsorbProp[32]);
    if (!mcNCounter[33]) fprintf(stderr, "Warning: No neutron could reach Component[33] fermi_chopp\n");
    if (mcAbsorbProp[33]) fprintf(stderr, "Warning: %g events were removed in Component[33] fermi_chopp\n""         (negative time, rounding errors).\n", mcAbsorbProp[33]);
    if (!mcNCounter[34]) fprintf(stderr, "Warning: No neutron could reach Component[34] adjustable_slits\n");
    if (mcAbsorbProp[34]) fprintf(stderr, "Warning: %g events were removed in Component[34] adjustable_slits\n""         (negative time, rounding errors).\n", mcAbsorbProp[34]);
    if (!mcNCounter[35]) fprintf(stderr, "Warning: No neutron could reach Component[35] Monitor1\n");
    if (mcAbsorbProp[35]) fprintf(stderr, "Warning: %g events were removed in Component[35] Monitor1\n""         (negative time, rounding errors).\n", mcAbsorbProp[35]);
    if (!mcNCounter[36]) fprintf(stderr, "Warning: No neutron could reach Component[36] guide29\n");
    if (mcAbsorbProp[36]) fprintf(stderr, "Warning: %g events were removed in Component[36] guide29\n""         (negative time, rounding errors).\n", mcAbsorbProp[36]);
    if (!mcNCounter[37]) fprintf(stderr, "Warning: No neutron could reach Component[37] guide31\n");
    if (mcAbsorbProp[37]) fprintf(stderr, "Warning: %g events were removed in Component[37] guide31\n""         (negative time, rounding errors).\n", mcAbsorbProp[37]);
    if (!mcNCounter[38]) fprintf(stderr, "Warning: No neutron could reach Component[38] guide32\n");
    if (mcAbsorbProp[38]) fprintf(stderr, "Warning: %g events were removed in Component[38] guide32\n""         (negative time, rounding errors).\n", mcAbsorbProp[38]);
    if (!mcNCounter[39]) fprintf(stderr, "Warning: No neutron could reach Component[39] guide34\n");
    if (mcAbsorbProp[39]) fprintf(stderr, "Warning: %g events were removed in Component[39] guide34\n""         (negative time, rounding errors).\n", mcAbsorbProp[39]);
    if (!mcNCounter[40]) fprintf(stderr, "Warning: No neutron could reach Component[40] E_det\n");
    if (mcAbsorbProp[40]) fprintf(stderr, "Warning: %g events were removed in Component[40] E_det\n""         (negative time, rounding errors).\n", mcAbsorbProp[40]);
    if (!mcNCounter[41]) fprintf(stderr, "Warning: No neutron could reach Component[41] Sample_Arm\n");
    if (mcAbsorbProp[41]) fprintf(stderr, "Warning: %g events were removed in Component[41] Sample_Arm\n""         (negative time, rounding errors).\n", mcAbsorbProp[41]);
    if (!mcNCounter[42]) fprintf(stderr, "Warning: No neutron could reach Component[42] sample\n");
    if (mcNCounter[42] < 1000*(10)) fprintf(stderr, 
"Warning: Number of events reaching SPLIT position Component[42] sample\n"
"         is probably too low. Increase Ncount.\n");

    if (mcAbsorbProp[42]) fprintf(stderr, "Warning: %g events were removed in Component[42] sample\n""         (negative time, rounding errors).\n", mcAbsorbProp[42]);
  /* User FINALLY code for component 't_mon_detC'. */
  SIG_MESSAGE("t_mon_detC (Finally)");
#define mccompcurname  t_mon_detC
#define mccompcurtype  Monitor_nD
#define mccompcurindex 43
#define options mcct_mon_detC_options
#define filename mcct_mon_detC_filename
#define user1 mcct_mon_detC_user1
#define user2 mcct_mon_detC_user2
#define user3 mcct_mon_detC_user3
#define username1 mcct_mon_detC_username1
#define username2 mcct_mon_detC_username2
#define username3 mcct_mon_detC_username3
#define DEFS mcct_mon_detC_DEFS
#define Vars mcct_mon_detC_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detC_xwidth;
MCNUM yheight = mcct_mon_detC_yheight;
MCNUM zthick = mcct_mon_detC_zthick;
MCNUM xmin = mcct_mon_detC_xmin;
MCNUM xmax = mcct_mon_detC_xmax;
MCNUM ymin = mcct_mon_detC_ymin;
MCNUM ymax = mcct_mon_detC_ymax;
MCNUM zmin = mcct_mon_detC_zmin;
MCNUM zmax = mcct_mon_detC_zmax;
MCNUM bins = mcct_mon_detC_bins;
MCNUM min = mcct_mon_detC_min;
MCNUM max = mcct_mon_detC_max;
MCNUM restore_neutron = mcct_mon_detC_restore_neutron;
#line 390 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  /* free pointers */
  Monitor_nD_Finally(&DEFS, &Vars);
}
#line 27897 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[43]) fprintf(stderr, "Warning: No neutron could reach Component[43] t_mon_detC\n");
    if (mcAbsorbProp[43]) fprintf(stderr, "Warning: %g events were removed in Component[43] t_mon_detC\n""         (negative time, rounding errors).\n", mcAbsorbProp[43]);
  /* User FINALLY code for component 't_mon_detB'. */
  SIG_MESSAGE("t_mon_detB (Finally)");
#define mccompcurname  t_mon_detB
#define mccompcurtype  Monitor_nD
#define mccompcurindex 44
#define options mcct_mon_detB_options
#define filename mcct_mon_detB_filename
#define user1 mcct_mon_detB_user1
#define user2 mcct_mon_detB_user2
#define user3 mcct_mon_detB_user3
#define username1 mcct_mon_detB_username1
#define username2 mcct_mon_detB_username2
#define username3 mcct_mon_detB_username3
#define DEFS mcct_mon_detB_DEFS
#define Vars mcct_mon_detB_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detB_xwidth;
MCNUM yheight = mcct_mon_detB_yheight;
MCNUM zthick = mcct_mon_detB_zthick;
MCNUM xmin = mcct_mon_detB_xmin;
MCNUM xmax = mcct_mon_detB_xmax;
MCNUM ymin = mcct_mon_detB_ymin;
MCNUM ymax = mcct_mon_detB_ymax;
MCNUM zmin = mcct_mon_detB_zmin;
MCNUM zmax = mcct_mon_detB_zmax;
MCNUM bins = mcct_mon_detB_bins;
MCNUM min = mcct_mon_detB_min;
MCNUM max = mcct_mon_detB_max;
MCNUM restore_neutron = mcct_mon_detB_restore_neutron;
#line 390 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  /* free pointers */
  Monitor_nD_Finally(&DEFS, &Vars);
}
#line 27949 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[44]) fprintf(stderr, "Warning: No neutron could reach Component[44] t_mon_detB\n");
    if (mcAbsorbProp[44]) fprintf(stderr, "Warning: %g events were removed in Component[44] t_mon_detB\n""         (negative time, rounding errors).\n", mcAbsorbProp[44]);
  /* User FINALLY code for component 't_mon_detD'. */
  SIG_MESSAGE("t_mon_detD (Finally)");
#define mccompcurname  t_mon_detD
#define mccompcurtype  Monitor_nD
#define mccompcurindex 45
#define options mcct_mon_detD_options
#define filename mcct_mon_detD_filename
#define user1 mcct_mon_detD_user1
#define user2 mcct_mon_detD_user2
#define user3 mcct_mon_detD_user3
#define username1 mcct_mon_detD_username1
#define username2 mcct_mon_detD_username2
#define username3 mcct_mon_detD_username3
#define DEFS mcct_mon_detD_DEFS
#define Vars mcct_mon_detD_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detD_xwidth;
MCNUM yheight = mcct_mon_detD_yheight;
MCNUM zthick = mcct_mon_detD_zthick;
MCNUM xmin = mcct_mon_detD_xmin;
MCNUM xmax = mcct_mon_detD_xmax;
MCNUM ymin = mcct_mon_detD_ymin;
MCNUM ymax = mcct_mon_detD_ymax;
MCNUM zmin = mcct_mon_detD_zmin;
MCNUM zmax = mcct_mon_detD_zmax;
MCNUM bins = mcct_mon_detD_bins;
MCNUM min = mcct_mon_detD_min;
MCNUM max = mcct_mon_detD_max;
MCNUM restore_neutron = mcct_mon_detD_restore_neutron;
#line 390 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  /* free pointers */
  Monitor_nD_Finally(&DEFS, &Vars);
}
#line 28001 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

    if (!mcNCounter[45]) fprintf(stderr, "Warning: No neutron could reach Component[45] t_mon_detD\n");
    if (mcAbsorbProp[45]) fprintf(stderr, "Warning: %g events were removed in Component[45] t_mon_detD\n""         (negative time, rounding errors).\n", mcAbsorbProp[45]);
    if (!mcNCounter[46]) fprintf(stderr, "Warning: No neutron could reach Component[46] t_mon2\n");
    if (mcAbsorbProp[46]) fprintf(stderr, "Warning: %g events were removed in Component[46] t_mon2\n""         (negative time, rounding errors).\n", mcAbsorbProp[46]);
  /* User FINALLY code from instrument definition. */
  SIG_MESSAGE("Fermi_T0 (Finally)");
#define mccompcurname Fermi_T0
#define Fermi_nu mcipFermi_nu
#define FC_num mcipFC_num
#define T0_nu mcipT0_nu
#define Edes mcipEdes
#define T0_off mcipT0_off
#define sxmin mcipsxmin
#define sxmax mcipsxmax
#define symin mcipsymin
#define symax mcipsymax
#define sam_file mcipsam_file
#line 338 "SEQ_11_09_2009.instr"
{
  // free(dett0optstr);free(detoptstr);free(detsampoptstr);free(detdetoptstr);free(mon1optstr);free(mon2optstr);	
}
#line 28038 "SEQ_11_09_2009.c"
#undef sam_file
#undef symax
#undef symin
#undef sxmax
#undef sxmin
#undef T0_off
#undef Edes
#undef T0_nu
#undef FC_num
#undef Fermi_nu
#undef mccompcurname

  mcsiminfo_close(); 
} /* end finally */
#define magnify mcdis_magnify
#define line mcdis_line
#define dashed_line mcdis_dashed_line
#define multiline mcdis_multiline
#define rectangle mcdis_rectangle
#define box mcdis_box
#define circle mcdis_circle
void mcdisplay(void) {
  printf("MCDISPLAY: start\n");
  /* Components MCDISPLAY code. */

  /* MCDISPLAY code for component 'mod'. */
  SIG_MESSAGE("mod (McDisplay)");
  printf("MCDISPLAY: component %s\n", "mod");
#define mccompcurname  mod
#define mccompcurtype  SNS_source
#define mccompcurindex 2
#define S_filename mccmod_S_filename
#define hdiv mccmod_hdiv
#define vdiv mccmod_vdiv
#define p_in mccmod_p_in
{   /* Declarations of SETTING parameters. */
MCNUM width = mccmod_width;
MCNUM height = mccmod_height;
MCNUM dist = mccmod_dist;
MCNUM xw = mccmod_xw;
MCNUM yh = mccmod_yh;
MCNUM Emin = mccmod_Emin;
MCNUM Emax = mccmod_Emax;
#line 535 "SNS_source.comp"
{
  double x1,y1,x2,y2;
  x1=-width/2.0;y1=-height/2.0;x2=width/2.0;y2=height/2.0;
  multiline(4,(double)x1,(double)y1,0.0,(double)x1,(double)y2,0.0,(double)x2,(double)y2,0.0,(double)x2,(double)y1,0.0,(double)x1,(double)y1,0.0);
}
#line 28088 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef p_in
#undef vdiv
#undef hdiv
#undef S_filename
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'core_ves'. */
  SIG_MESSAGE("core_ves (McDisplay)");
  printf("MCDISPLAY: component %s\n", "core_ves");
#define mccompcurname  core_ves
#define mccompcurtype  Channeled_guide
#define mccompcurindex 3
#define w1c mcccore_ves_w1c
#define w2c mcccore_ves_w2c
#define ww mcccore_ves_ww
#define hh mcccore_ves_hh
#define whalf mcccore_ves_whalf
#define hhalf mcccore_ves_hhalf
#define lwhalf mcccore_ves_lwhalf
#define lhhalf mcccore_ves_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mcccore_ves_w1;
MCNUM h1 = mcccore_ves_h1;
MCNUM w2 = mcccore_ves_w2;
MCNUM h2 = mcccore_ves_h2;
MCNUM l = mcccore_ves_l;
MCNUM R0 = mcccore_ves_R0;
MCNUM Qcx = mcccore_ves_Qcx;
MCNUM Qcy = mcccore_ves_Qcy;
MCNUM alphax = mcccore_ves_alphax;
MCNUM alphay = mcccore_ves_alphay;
MCNUM W = mcccore_ves_W;
MCNUM k = mcccore_ves_k;
MCNUM d = mcccore_ves_d;
MCNUM mx = mcccore_ves_mx;
MCNUM my = mcccore_ves_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28152 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'shutter_guide'. */
  SIG_MESSAGE("shutter_guide (McDisplay)");
  printf("MCDISPLAY: component %s\n", "shutter_guide");
#define mccompcurname  shutter_guide
#define mccompcurtype  Channeled_guide
#define mccompcurindex 4
#define w1c mccshutter_guide_w1c
#define w2c mccshutter_guide_w2c
#define ww mccshutter_guide_ww
#define hh mccshutter_guide_hh
#define whalf mccshutter_guide_whalf
#define hhalf mccshutter_guide_hhalf
#define lwhalf mccshutter_guide_lwhalf
#define lhhalf mccshutter_guide_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccshutter_guide_w1;
MCNUM h1 = mccshutter_guide_h1;
MCNUM w2 = mccshutter_guide_w2;
MCNUM h2 = mccshutter_guide_h2;
MCNUM l = mccshutter_guide_l;
MCNUM R0 = mccshutter_guide_R0;
MCNUM Qcx = mccshutter_guide_Qcx;
MCNUM Qcy = mccshutter_guide_Qcy;
MCNUM alphax = mccshutter_guide_alphax;
MCNUM alphay = mccshutter_guide_alphay;
MCNUM W = mccshutter_guide_W;
MCNUM k = mccshutter_guide_k;
MCNUM d = mccshutter_guide_d;
MCNUM mx = mccshutter_guide_mx;
MCNUM my = mccshutter_guide_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28220 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide1'. */
  SIG_MESSAGE("guide1 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide1");
#define mccompcurname  guide1
#define mccompcurtype  Channeled_guide
#define mccompcurindex 5
#define w1c mccguide1_w1c
#define w2c mccguide1_w2c
#define ww mccguide1_ww
#define hh mccguide1_hh
#define whalf mccguide1_whalf
#define hhalf mccguide1_hhalf
#define lwhalf mccguide1_lwhalf
#define lhhalf mccguide1_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide1_w1;
MCNUM h1 = mccguide1_h1;
MCNUM w2 = mccguide1_w2;
MCNUM h2 = mccguide1_h2;
MCNUM l = mccguide1_l;
MCNUM R0 = mccguide1_R0;
MCNUM Qcx = mccguide1_Qcx;
MCNUM Qcy = mccguide1_Qcy;
MCNUM alphax = mccguide1_alphax;
MCNUM alphay = mccguide1_alphay;
MCNUM W = mccguide1_W;
MCNUM k = mccguide1_k;
MCNUM d = mccguide1_d;
MCNUM mx = mccguide1_mx;
MCNUM my = mccguide1_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28288 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide2'. */
  SIG_MESSAGE("guide2 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide2");
#define mccompcurname  guide2
#define mccompcurtype  Channeled_guide
#define mccompcurindex 6
#define w1c mccguide2_w1c
#define w2c mccguide2_w2c
#define ww mccguide2_ww
#define hh mccguide2_hh
#define whalf mccguide2_whalf
#define hhalf mccguide2_hhalf
#define lwhalf mccguide2_lwhalf
#define lhhalf mccguide2_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide2_w1;
MCNUM h1 = mccguide2_h1;
MCNUM w2 = mccguide2_w2;
MCNUM h2 = mccguide2_h2;
MCNUM l = mccguide2_l;
MCNUM R0 = mccguide2_R0;
MCNUM Qcx = mccguide2_Qcx;
MCNUM Qcy = mccguide2_Qcy;
MCNUM alphax = mccguide2_alphax;
MCNUM alphay = mccguide2_alphay;
MCNUM W = mccguide2_W;
MCNUM k = mccguide2_k;
MCNUM d = mccguide2_d;
MCNUM mx = mccguide2_mx;
MCNUM my = mccguide2_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28356 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide3'. */
  SIG_MESSAGE("guide3 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide3");
#define mccompcurname  guide3
#define mccompcurtype  Channeled_guide
#define mccompcurindex 7
#define w1c mccguide3_w1c
#define w2c mccguide3_w2c
#define ww mccguide3_ww
#define hh mccguide3_hh
#define whalf mccguide3_whalf
#define hhalf mccguide3_hhalf
#define lwhalf mccguide3_lwhalf
#define lhhalf mccguide3_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide3_w1;
MCNUM h1 = mccguide3_h1;
MCNUM w2 = mccguide3_w2;
MCNUM h2 = mccguide3_h2;
MCNUM l = mccguide3_l;
MCNUM R0 = mccguide3_R0;
MCNUM Qcx = mccguide3_Qcx;
MCNUM Qcy = mccguide3_Qcy;
MCNUM alphax = mccguide3_alphax;
MCNUM alphay = mccguide3_alphay;
MCNUM W = mccguide3_W;
MCNUM k = mccguide3_k;
MCNUM d = mccguide3_d;
MCNUM mx = mccguide3_mx;
MCNUM my = mccguide3_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28424 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide4'. */
  SIG_MESSAGE("guide4 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide4");
#define mccompcurname  guide4
#define mccompcurtype  Channeled_guide
#define mccompcurindex 8
#define w1c mccguide4_w1c
#define w2c mccguide4_w2c
#define ww mccguide4_ww
#define hh mccguide4_hh
#define whalf mccguide4_whalf
#define hhalf mccguide4_hhalf
#define lwhalf mccguide4_lwhalf
#define lhhalf mccguide4_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide4_w1;
MCNUM h1 = mccguide4_h1;
MCNUM w2 = mccguide4_w2;
MCNUM h2 = mccguide4_h2;
MCNUM l = mccguide4_l;
MCNUM R0 = mccguide4_R0;
MCNUM Qcx = mccguide4_Qcx;
MCNUM Qcy = mccguide4_Qcy;
MCNUM alphax = mccguide4_alphax;
MCNUM alphay = mccguide4_alphay;
MCNUM W = mccguide4_W;
MCNUM k = mccguide4_k;
MCNUM d = mccguide4_d;
MCNUM mx = mccguide4_mx;
MCNUM my = mccguide4_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28492 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide5'. */
  SIG_MESSAGE("guide5 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide5");
#define mccompcurname  guide5
#define mccompcurtype  Channeled_guide
#define mccompcurindex 9
#define w1c mccguide5_w1c
#define w2c mccguide5_w2c
#define ww mccguide5_ww
#define hh mccguide5_hh
#define whalf mccguide5_whalf
#define hhalf mccguide5_hhalf
#define lwhalf mccguide5_lwhalf
#define lhhalf mccguide5_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide5_w1;
MCNUM h1 = mccguide5_h1;
MCNUM w2 = mccguide5_w2;
MCNUM h2 = mccguide5_h2;
MCNUM l = mccguide5_l;
MCNUM R0 = mccguide5_R0;
MCNUM Qcx = mccguide5_Qcx;
MCNUM Qcy = mccguide5_Qcy;
MCNUM alphax = mccguide5_alphax;
MCNUM alphay = mccguide5_alphay;
MCNUM W = mccguide5_W;
MCNUM k = mccguide5_k;
MCNUM d = mccguide5_d;
MCNUM mx = mccguide5_mx;
MCNUM my = mccguide5_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28560 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide6'. */
  SIG_MESSAGE("guide6 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide6");
#define mccompcurname  guide6
#define mccompcurtype  Channeled_guide
#define mccompcurindex 10
#define w1c mccguide6_w1c
#define w2c mccguide6_w2c
#define ww mccguide6_ww
#define hh mccguide6_hh
#define whalf mccguide6_whalf
#define hhalf mccguide6_hhalf
#define lwhalf mccguide6_lwhalf
#define lhhalf mccguide6_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide6_w1;
MCNUM h1 = mccguide6_h1;
MCNUM w2 = mccguide6_w2;
MCNUM h2 = mccguide6_h2;
MCNUM l = mccguide6_l;
MCNUM R0 = mccguide6_R0;
MCNUM Qcx = mccguide6_Qcx;
MCNUM Qcy = mccguide6_Qcy;
MCNUM alphax = mccguide6_alphax;
MCNUM alphay = mccguide6_alphay;
MCNUM W = mccguide6_W;
MCNUM k = mccguide6_k;
MCNUM d = mccguide6_d;
MCNUM mx = mccguide6_mx;
MCNUM my = mccguide6_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28628 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide7'. */
  SIG_MESSAGE("guide7 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide7");
#define mccompcurname  guide7
#define mccompcurtype  Channeled_guide
#define mccompcurindex 11
#define w1c mccguide7_w1c
#define w2c mccguide7_w2c
#define ww mccguide7_ww
#define hh mccguide7_hh
#define whalf mccguide7_whalf
#define hhalf mccguide7_hhalf
#define lwhalf mccguide7_lwhalf
#define lhhalf mccguide7_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide7_w1;
MCNUM h1 = mccguide7_h1;
MCNUM w2 = mccguide7_w2;
MCNUM h2 = mccguide7_h2;
MCNUM l = mccguide7_l;
MCNUM R0 = mccguide7_R0;
MCNUM Qcx = mccguide7_Qcx;
MCNUM Qcy = mccguide7_Qcy;
MCNUM alphax = mccguide7_alphax;
MCNUM alphay = mccguide7_alphay;
MCNUM W = mccguide7_W;
MCNUM k = mccguide7_k;
MCNUM d = mccguide7_d;
MCNUM mx = mccguide7_mx;
MCNUM my = mccguide7_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28696 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide8'. */
  SIG_MESSAGE("guide8 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide8");
#define mccompcurname  guide8
#define mccompcurtype  Channeled_guide
#define mccompcurindex 12
#define w1c mccguide8_w1c
#define w2c mccguide8_w2c
#define ww mccguide8_ww
#define hh mccguide8_hh
#define whalf mccguide8_whalf
#define hhalf mccguide8_hhalf
#define lwhalf mccguide8_lwhalf
#define lhhalf mccguide8_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide8_w1;
MCNUM h1 = mccguide8_h1;
MCNUM w2 = mccguide8_w2;
MCNUM h2 = mccguide8_h2;
MCNUM l = mccguide8_l;
MCNUM R0 = mccguide8_R0;
MCNUM Qcx = mccguide8_Qcx;
MCNUM Qcy = mccguide8_Qcy;
MCNUM alphax = mccguide8_alphax;
MCNUM alphay = mccguide8_alphay;
MCNUM W = mccguide8_W;
MCNUM k = mccguide8_k;
MCNUM d = mccguide8_d;
MCNUM mx = mccguide8_mx;
MCNUM my = mccguide8_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28764 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide9'. */
  SIG_MESSAGE("guide9 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide9");
#define mccompcurname  guide9
#define mccompcurtype  Channeled_guide
#define mccompcurindex 13
#define w1c mccguide9_w1c
#define w2c mccguide9_w2c
#define ww mccguide9_ww
#define hh mccguide9_hh
#define whalf mccguide9_whalf
#define hhalf mccguide9_hhalf
#define lwhalf mccguide9_lwhalf
#define lhhalf mccguide9_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide9_w1;
MCNUM h1 = mccguide9_h1;
MCNUM w2 = mccguide9_w2;
MCNUM h2 = mccguide9_h2;
MCNUM l = mccguide9_l;
MCNUM R0 = mccguide9_R0;
MCNUM Qcx = mccguide9_Qcx;
MCNUM Qcy = mccguide9_Qcy;
MCNUM alphax = mccguide9_alphax;
MCNUM alphay = mccguide9_alphay;
MCNUM W = mccguide9_W;
MCNUM k = mccguide9_k;
MCNUM d = mccguide9_d;
MCNUM mx = mccguide9_mx;
MCNUM my = mccguide9_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28832 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide10'. */
  SIG_MESSAGE("guide10 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide10");
#define mccompcurname  guide10
#define mccompcurtype  Channeled_guide
#define mccompcurindex 14
#define w1c mccguide10_w1c
#define w2c mccguide10_w2c
#define ww mccguide10_ww
#define hh mccguide10_hh
#define whalf mccguide10_whalf
#define hhalf mccguide10_hhalf
#define lwhalf mccguide10_lwhalf
#define lhhalf mccguide10_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide10_w1;
MCNUM h1 = mccguide10_h1;
MCNUM w2 = mccguide10_w2;
MCNUM h2 = mccguide10_h2;
MCNUM l = mccguide10_l;
MCNUM R0 = mccguide10_R0;
MCNUM Qcx = mccguide10_Qcx;
MCNUM Qcy = mccguide10_Qcy;
MCNUM alphax = mccguide10_alphax;
MCNUM alphay = mccguide10_alphay;
MCNUM W = mccguide10_W;
MCNUM k = mccguide10_k;
MCNUM d = mccguide10_d;
MCNUM mx = mccguide10_mx;
MCNUM my = mccguide10_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28900 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide11'. */
  SIG_MESSAGE("guide11 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide11");
#define mccompcurname  guide11
#define mccompcurtype  Channeled_guide
#define mccompcurindex 15
#define w1c mccguide11_w1c
#define w2c mccguide11_w2c
#define ww mccguide11_ww
#define hh mccguide11_hh
#define whalf mccguide11_whalf
#define hhalf mccguide11_hhalf
#define lwhalf mccguide11_lwhalf
#define lhhalf mccguide11_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide11_w1;
MCNUM h1 = mccguide11_h1;
MCNUM w2 = mccguide11_w2;
MCNUM h2 = mccguide11_h2;
MCNUM l = mccguide11_l;
MCNUM R0 = mccguide11_R0;
MCNUM Qcx = mccguide11_Qcx;
MCNUM Qcy = mccguide11_Qcy;
MCNUM alphax = mccguide11_alphax;
MCNUM alphay = mccguide11_alphay;
MCNUM W = mccguide11_W;
MCNUM k = mccguide11_k;
MCNUM d = mccguide11_d;
MCNUM mx = mccguide11_mx;
MCNUM my = mccguide11_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 28968 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 't0_chopp'. */
  SIG_MESSAGE("t0_chopp (McDisplay)");
  printf("MCDISPLAY: component %s\n", "t0_chopp");
#define mccompcurname  t0_chopp
#define mccompcurtype  Vertical_T0a
#define mccompcurindex 16
#define len mcct0_chopp_len
#define w1 mcct0_chopp_w1
#define w2 mcct0_chopp_w2
#define nu mcct0_chopp_nu
#define delta mcct0_chopp_delta
#define tc mcct0_chopp_tc
#define ymin mcct0_chopp_ymin
#define ymax mcct0_chopp_ymax
#define omega mcct0_chopp_omega
#define r_blade mcct0_chopp_r_blade
#define x_width mcct0_chopp_x_width
#define nn mcct0_chopp_nn
#define tdr mcct0_chopp_tdr
#line 171 "Vertical_T0a.comp"
{
double zstep,x1,x2,x3,x4,z1,z2;
int idx, idx2;
line(w2/2.0,ymin,splen,w2/2.0,ymax,splen);
line(w2/2.0,ymin,-splen,w2/2.0,ymax,-splen);
line(-w2/2.0,ymin,splen,-w2/2.0,ymax,splen);
line(-w2/2.0,ymin,-splen,-w2/2.0,ymax,-splen);
line(w2/2.0,ymax,splen,w1/2.0,ymax,0);
line(w1/2.0,ymax,0,w2/2.0,ymax,-splen);
line(-w2/2.0,ymax,splen,-w1/2.0,ymax,0);
line(-w1/2.0,ymax,0,-w2/2.0,ymax,-splen);
line(w2/2.0,ymin,splen,w1/2.0,ymin,0);
line(w1/2.0,ymin,0,w2/2.0,ymin,-splen);
line(-w2/2.0,ymin,splen,-w1/2.0,ymin,0);
line(-w1/2.0,ymin,0,-w2/2.0,ymin,-splen);
circle("zx",0,ymin,0,rad);
circle("zx",0,ymax,0,rad);
zstep=2.0*splen/10.0;
}
#line 29021 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w2
#undef w1
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 't_check1'. */
  SIG_MESSAGE("t_check1 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "t_check1");
#define mccompcurname  t_check1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 17
#define nchan mcct_check1_nchan
#define TOF_N mcct_check1_TOF_N
#define TOF_p mcct_check1_TOF_p
#define TOF_p2 mcct_check1_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mcct_check1_xmin;
MCNUM xmax = mcct_check1_xmax;
MCNUM ymin = mcct_check1_ymin;
MCNUM ymax = mcct_check1_ymax;
MCNUM tmin = mcct_check1_tmin;
MCNUM tmax = mcct_check1_tmax;
char* filename = mcct_check1_filename;
#line 94 "TOF_monitor2.comp"
{
  magnify("xy");
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 29066 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide13'. */
  SIG_MESSAGE("guide13 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide13");
#define mccompcurname  guide13
#define mccompcurtype  Channeled_guide
#define mccompcurindex 18
#define w1c mccguide13_w1c
#define w2c mccguide13_w2c
#define ww mccguide13_ww
#define hh mccguide13_hh
#define whalf mccguide13_whalf
#define hhalf mccguide13_hhalf
#define lwhalf mccguide13_lwhalf
#define lhhalf mccguide13_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide13_w1;
MCNUM h1 = mccguide13_h1;
MCNUM w2 = mccguide13_w2;
MCNUM h2 = mccguide13_h2;
MCNUM l = mccguide13_l;
MCNUM R0 = mccguide13_R0;
MCNUM Qcx = mccguide13_Qcx;
MCNUM Qcy = mccguide13_Qcy;
MCNUM alphax = mccguide13_alphax;
MCNUM alphay = mccguide13_alphay;
MCNUM W = mccguide13_W;
MCNUM k = mccguide13_k;
MCNUM d = mccguide13_d;
MCNUM mx = mccguide13_mx;
MCNUM my = mccguide13_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29130 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide14'. */
  SIG_MESSAGE("guide14 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide14");
#define mccompcurname  guide14
#define mccompcurtype  Channeled_guide
#define mccompcurindex 19
#define w1c mccguide14_w1c
#define w2c mccguide14_w2c
#define ww mccguide14_ww
#define hh mccguide14_hh
#define whalf mccguide14_whalf
#define hhalf mccguide14_hhalf
#define lwhalf mccguide14_lwhalf
#define lhhalf mccguide14_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide14_w1;
MCNUM h1 = mccguide14_h1;
MCNUM w2 = mccguide14_w2;
MCNUM h2 = mccguide14_h2;
MCNUM l = mccguide14_l;
MCNUM R0 = mccguide14_R0;
MCNUM Qcx = mccguide14_Qcx;
MCNUM Qcy = mccguide14_Qcy;
MCNUM alphax = mccguide14_alphax;
MCNUM alphay = mccguide14_alphay;
MCNUM W = mccguide14_W;
MCNUM k = mccguide14_k;
MCNUM d = mccguide14_d;
MCNUM mx = mccguide14_mx;
MCNUM my = mccguide14_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29198 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide15'. */
  SIG_MESSAGE("guide15 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide15");
#define mccompcurname  guide15
#define mccompcurtype  Channeled_guide
#define mccompcurindex 20
#define w1c mccguide15_w1c
#define w2c mccguide15_w2c
#define ww mccguide15_ww
#define hh mccguide15_hh
#define whalf mccguide15_whalf
#define hhalf mccguide15_hhalf
#define lwhalf mccguide15_lwhalf
#define lhhalf mccguide15_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide15_w1;
MCNUM h1 = mccguide15_h1;
MCNUM w2 = mccguide15_w2;
MCNUM h2 = mccguide15_h2;
MCNUM l = mccguide15_l;
MCNUM R0 = mccguide15_R0;
MCNUM Qcx = mccguide15_Qcx;
MCNUM Qcy = mccguide15_Qcy;
MCNUM alphax = mccguide15_alphax;
MCNUM alphay = mccguide15_alphay;
MCNUM W = mccguide15_W;
MCNUM k = mccguide15_k;
MCNUM d = mccguide15_d;
MCNUM mx = mccguide15_mx;
MCNUM my = mccguide15_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29266 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide16'. */
  SIG_MESSAGE("guide16 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide16");
#define mccompcurname  guide16
#define mccompcurtype  Channeled_guide
#define mccompcurindex 21
#define w1c mccguide16_w1c
#define w2c mccguide16_w2c
#define ww mccguide16_ww
#define hh mccguide16_hh
#define whalf mccguide16_whalf
#define hhalf mccguide16_hhalf
#define lwhalf mccguide16_lwhalf
#define lhhalf mccguide16_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide16_w1;
MCNUM h1 = mccguide16_h1;
MCNUM w2 = mccguide16_w2;
MCNUM h2 = mccguide16_h2;
MCNUM l = mccguide16_l;
MCNUM R0 = mccguide16_R0;
MCNUM Qcx = mccguide16_Qcx;
MCNUM Qcy = mccguide16_Qcy;
MCNUM alphax = mccguide16_alphax;
MCNUM alphay = mccguide16_alphay;
MCNUM W = mccguide16_W;
MCNUM k = mccguide16_k;
MCNUM d = mccguide16_d;
MCNUM mx = mccguide16_mx;
MCNUM my = mccguide16_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29334 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide17'. */
  SIG_MESSAGE("guide17 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide17");
#define mccompcurname  guide17
#define mccompcurtype  Channeled_guide
#define mccompcurindex 22
#define w1c mccguide17_w1c
#define w2c mccguide17_w2c
#define ww mccguide17_ww
#define hh mccguide17_hh
#define whalf mccguide17_whalf
#define hhalf mccguide17_hhalf
#define lwhalf mccguide17_lwhalf
#define lhhalf mccguide17_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide17_w1;
MCNUM h1 = mccguide17_h1;
MCNUM w2 = mccguide17_w2;
MCNUM h2 = mccguide17_h2;
MCNUM l = mccguide17_l;
MCNUM R0 = mccguide17_R0;
MCNUM Qcx = mccguide17_Qcx;
MCNUM Qcy = mccguide17_Qcy;
MCNUM alphax = mccguide17_alphax;
MCNUM alphay = mccguide17_alphay;
MCNUM W = mccguide17_W;
MCNUM k = mccguide17_k;
MCNUM d = mccguide17_d;
MCNUM mx = mccguide17_mx;
MCNUM my = mccguide17_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29402 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide18'. */
  SIG_MESSAGE("guide18 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide18");
#define mccompcurname  guide18
#define mccompcurtype  Channeled_guide
#define mccompcurindex 23
#define w1c mccguide18_w1c
#define w2c mccguide18_w2c
#define ww mccguide18_ww
#define hh mccguide18_hh
#define whalf mccguide18_whalf
#define hhalf mccguide18_hhalf
#define lwhalf mccguide18_lwhalf
#define lhhalf mccguide18_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide18_w1;
MCNUM h1 = mccguide18_h1;
MCNUM w2 = mccguide18_w2;
MCNUM h2 = mccguide18_h2;
MCNUM l = mccguide18_l;
MCNUM R0 = mccguide18_R0;
MCNUM Qcx = mccguide18_Qcx;
MCNUM Qcy = mccguide18_Qcy;
MCNUM alphax = mccguide18_alphax;
MCNUM alphay = mccguide18_alphay;
MCNUM W = mccguide18_W;
MCNUM k = mccguide18_k;
MCNUM d = mccguide18_d;
MCNUM mx = mccguide18_mx;
MCNUM my = mccguide18_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29470 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide19'. */
  SIG_MESSAGE("guide19 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide19");
#define mccompcurname  guide19
#define mccompcurtype  Channeled_guide
#define mccompcurindex 24
#define w1c mccguide19_w1c
#define w2c mccguide19_w2c
#define ww mccguide19_ww
#define hh mccguide19_hh
#define whalf mccguide19_whalf
#define hhalf mccguide19_hhalf
#define lwhalf mccguide19_lwhalf
#define lhhalf mccguide19_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide19_w1;
MCNUM h1 = mccguide19_h1;
MCNUM w2 = mccguide19_w2;
MCNUM h2 = mccguide19_h2;
MCNUM l = mccguide19_l;
MCNUM R0 = mccguide19_R0;
MCNUM Qcx = mccguide19_Qcx;
MCNUM Qcy = mccguide19_Qcy;
MCNUM alphax = mccguide19_alphax;
MCNUM alphay = mccguide19_alphay;
MCNUM W = mccguide19_W;
MCNUM k = mccguide19_k;
MCNUM d = mccguide19_d;
MCNUM mx = mccguide19_mx;
MCNUM my = mccguide19_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29538 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide20'. */
  SIG_MESSAGE("guide20 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide20");
#define mccompcurname  guide20
#define mccompcurtype  Channeled_guide
#define mccompcurindex 25
#define w1c mccguide20_w1c
#define w2c mccguide20_w2c
#define ww mccguide20_ww
#define hh mccguide20_hh
#define whalf mccguide20_whalf
#define hhalf mccguide20_hhalf
#define lwhalf mccguide20_lwhalf
#define lhhalf mccguide20_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide20_w1;
MCNUM h1 = mccguide20_h1;
MCNUM w2 = mccguide20_w2;
MCNUM h2 = mccguide20_h2;
MCNUM l = mccguide20_l;
MCNUM R0 = mccguide20_R0;
MCNUM Qcx = mccguide20_Qcx;
MCNUM Qcy = mccguide20_Qcy;
MCNUM alphax = mccguide20_alphax;
MCNUM alphay = mccguide20_alphay;
MCNUM W = mccguide20_W;
MCNUM k = mccguide20_k;
MCNUM d = mccguide20_d;
MCNUM mx = mccguide20_mx;
MCNUM my = mccguide20_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29606 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide21'. */
  SIG_MESSAGE("guide21 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide21");
#define mccompcurname  guide21
#define mccompcurtype  Channeled_guide
#define mccompcurindex 26
#define w1c mccguide21_w1c
#define w2c mccguide21_w2c
#define ww mccguide21_ww
#define hh mccguide21_hh
#define whalf mccguide21_whalf
#define hhalf mccguide21_hhalf
#define lwhalf mccguide21_lwhalf
#define lhhalf mccguide21_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide21_w1;
MCNUM h1 = mccguide21_h1;
MCNUM w2 = mccguide21_w2;
MCNUM h2 = mccguide21_h2;
MCNUM l = mccguide21_l;
MCNUM R0 = mccguide21_R0;
MCNUM Qcx = mccguide21_Qcx;
MCNUM Qcy = mccguide21_Qcy;
MCNUM alphax = mccguide21_alphax;
MCNUM alphay = mccguide21_alphay;
MCNUM W = mccguide21_W;
MCNUM k = mccguide21_k;
MCNUM d = mccguide21_d;
MCNUM mx = mccguide21_mx;
MCNUM my = mccguide21_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29674 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide22'. */
  SIG_MESSAGE("guide22 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide22");
#define mccompcurname  guide22
#define mccompcurtype  Channeled_guide
#define mccompcurindex 27
#define w1c mccguide22_w1c
#define w2c mccguide22_w2c
#define ww mccguide22_ww
#define hh mccguide22_hh
#define whalf mccguide22_whalf
#define hhalf mccguide22_hhalf
#define lwhalf mccguide22_lwhalf
#define lhhalf mccguide22_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide22_w1;
MCNUM h1 = mccguide22_h1;
MCNUM w2 = mccguide22_w2;
MCNUM h2 = mccguide22_h2;
MCNUM l = mccguide22_l;
MCNUM R0 = mccguide22_R0;
MCNUM Qcx = mccguide22_Qcx;
MCNUM Qcy = mccguide22_Qcy;
MCNUM alphax = mccguide22_alphax;
MCNUM alphay = mccguide22_alphay;
MCNUM W = mccguide22_W;
MCNUM k = mccguide22_k;
MCNUM d = mccguide22_d;
MCNUM mx = mccguide22_mx;
MCNUM my = mccguide22_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29742 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide23'. */
  SIG_MESSAGE("guide23 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide23");
#define mccompcurname  guide23
#define mccompcurtype  Channeled_guide
#define mccompcurindex 28
#define w1c mccguide23_w1c
#define w2c mccguide23_w2c
#define ww mccguide23_ww
#define hh mccguide23_hh
#define whalf mccguide23_whalf
#define hhalf mccguide23_hhalf
#define lwhalf mccguide23_lwhalf
#define lhhalf mccguide23_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide23_w1;
MCNUM h1 = mccguide23_h1;
MCNUM w2 = mccguide23_w2;
MCNUM h2 = mccguide23_h2;
MCNUM l = mccguide23_l;
MCNUM R0 = mccguide23_R0;
MCNUM Qcx = mccguide23_Qcx;
MCNUM Qcy = mccguide23_Qcy;
MCNUM alphax = mccguide23_alphax;
MCNUM alphay = mccguide23_alphay;
MCNUM W = mccguide23_W;
MCNUM k = mccguide23_k;
MCNUM d = mccguide23_d;
MCNUM mx = mccguide23_mx;
MCNUM my = mccguide23_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29810 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide24'. */
  SIG_MESSAGE("guide24 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide24");
#define mccompcurname  guide24
#define mccompcurtype  Channeled_guide
#define mccompcurindex 29
#define w1c mccguide24_w1c
#define w2c mccguide24_w2c
#define ww mccguide24_ww
#define hh mccguide24_hh
#define whalf mccguide24_whalf
#define hhalf mccguide24_hhalf
#define lwhalf mccguide24_lwhalf
#define lhhalf mccguide24_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide24_w1;
MCNUM h1 = mccguide24_h1;
MCNUM w2 = mccguide24_w2;
MCNUM h2 = mccguide24_h2;
MCNUM l = mccguide24_l;
MCNUM R0 = mccguide24_R0;
MCNUM Qcx = mccguide24_Qcx;
MCNUM Qcy = mccguide24_Qcy;
MCNUM alphax = mccguide24_alphax;
MCNUM alphay = mccguide24_alphay;
MCNUM W = mccguide24_W;
MCNUM k = mccguide24_k;
MCNUM d = mccguide24_d;
MCNUM mx = mccguide24_mx;
MCNUM my = mccguide24_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29878 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide25'. */
  SIG_MESSAGE("guide25 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide25");
#define mccompcurname  guide25
#define mccompcurtype  Channeled_guide
#define mccompcurindex 30
#define w1c mccguide25_w1c
#define w2c mccguide25_w2c
#define ww mccguide25_ww
#define hh mccguide25_hh
#define whalf mccguide25_whalf
#define hhalf mccguide25_hhalf
#define lwhalf mccguide25_lwhalf
#define lhhalf mccguide25_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide25_w1;
MCNUM h1 = mccguide25_h1;
MCNUM w2 = mccguide25_w2;
MCNUM h2 = mccguide25_h2;
MCNUM l = mccguide25_l;
MCNUM R0 = mccguide25_R0;
MCNUM Qcx = mccguide25_Qcx;
MCNUM Qcy = mccguide25_Qcy;
MCNUM alphax = mccguide25_alphax;
MCNUM alphay = mccguide25_alphay;
MCNUM W = mccguide25_W;
MCNUM k = mccguide25_k;
MCNUM d = mccguide25_d;
MCNUM mx = mccguide25_mx;
MCNUM my = mccguide25_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 29946 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide26'. */
  SIG_MESSAGE("guide26 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide26");
#define mccompcurname  guide26
#define mccompcurtype  Channeled_guide
#define mccompcurindex 31
#define w1c mccguide26_w1c
#define w2c mccguide26_w2c
#define ww mccguide26_ww
#define hh mccguide26_hh
#define whalf mccguide26_whalf
#define hhalf mccguide26_hhalf
#define lwhalf mccguide26_lwhalf
#define lhhalf mccguide26_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide26_w1;
MCNUM h1 = mccguide26_h1;
MCNUM w2 = mccguide26_w2;
MCNUM h2 = mccguide26_h2;
MCNUM l = mccguide26_l;
MCNUM R0 = mccguide26_R0;
MCNUM Qcx = mccguide26_Qcx;
MCNUM Qcy = mccguide26_Qcy;
MCNUM alphax = mccguide26_alphax;
MCNUM alphay = mccguide26_alphay;
MCNUM W = mccguide26_W;
MCNUM k = mccguide26_k;
MCNUM d = mccguide26_d;
MCNUM mx = mccguide26_mx;
MCNUM my = mccguide26_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 30014 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide27'. */
  SIG_MESSAGE("guide27 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide27");
#define mccompcurname  guide27
#define mccompcurtype  Channeled_guide
#define mccompcurindex 32
#define w1c mccguide27_w1c
#define w2c mccguide27_w2c
#define ww mccguide27_ww
#define hh mccguide27_hh
#define whalf mccguide27_whalf
#define hhalf mccguide27_hhalf
#define lwhalf mccguide27_lwhalf
#define lhhalf mccguide27_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide27_w1;
MCNUM h1 = mccguide27_h1;
MCNUM w2 = mccguide27_w2;
MCNUM h2 = mccguide27_h2;
MCNUM l = mccguide27_l;
MCNUM R0 = mccguide27_R0;
MCNUM Qcx = mccguide27_Qcx;
MCNUM Qcy = mccguide27_Qcy;
MCNUM alphax = mccguide27_alphax;
MCNUM alphay = mccguide27_alphay;
MCNUM W = mccguide27_W;
MCNUM k = mccguide27_k;
MCNUM d = mccguide27_d;
MCNUM mx = mccguide27_mx;
MCNUM my = mccguide27_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 30082 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'fermi_chopp'. */
  SIG_MESSAGE("fermi_chopp (McDisplay)");
  printf("MCDISPLAY: component %s\n", "fermi_chopp");
#define mccompcurname  fermi_chopp
#define mccompcurtype  Fermi_chop2a
#define mccompcurindex 33
#define len mccfermi_chopp_len
#define w mccfermi_chopp_w
#define nu mccfermi_chopp_nu
#define delta mccfermi_chopp_delta
#define tc mccfermi_chopp_tc
#define ymin mccfermi_chopp_ymin
#define ymax mccfermi_chopp_ymax
#define nchan mccfermi_chopp_nchan
#define bw mccfermi_chopp_bw
#define blader mccfermi_chopp_blader
#define omega mccfermi_chopp_omega
#define r_blade mccfermi_chopp_r_blade
#define x_width mccfermi_chopp_x_width
#define nn mccfermi_chopp_nn
#define tdr mccfermi_chopp_tdr
#line 209 "Fermi_chop2a.comp"
{
double zstep,x1,x2,x3,x4,z1,z2;
int idx, idx2;
line(tw/2.0,ymin,splen,tw/2.0,ymax,splen);
line(tw/2.0,ymin,-splen,tw/2.0,ymax,-splen);
line(-tw/2.0,ymin,splen,-tw/2.0,ymax,splen);
line(-tw/2.0,ymin,-splen,-tw/2.0,ymax,-splen);
line(tw/2.0,ymax,splen,tw/2.0,ymax,-splen);
line(-tw/2.0,ymax,splen,-tw/2.0,ymax,-splen);
line(tw/2.0,ymin,splen,tw/2.0,ymin,-splen);
line(-tw/2.0,ymin,splen,-tw/2.0,ymin,-splen);
circle("zx",0,ymin,0,rad);
circle("zx",0,ymax,0,rad);
zstep=2.0*splen/10.0;
for(idx=0;idx<nchan+1;idx++){
   for(idx2=0;idx2<10;idx2++){
      z1=idx2*zstep-splen;
      z2=(idx2+1)*zstep-splen;
      x1=blades(z1,blader,off)+idx*(sw+bw)-tw/2.0;
      x2=blades(z2,blader,off)+idx*(sw+bw)-tw/2.0;
      x3=x1+bw;
      x4=x2+bw;
      line(x1,ymin,z1,x2,ymin,z2);
      line(x1,ymax,z1,x2,ymax,z2);
      line(x3,ymin,z1,x4,ymin,z2);
      line(x3,ymax,z1,x4,ymax,z2);
      if(idx2==0){
        line(x1,ymin,z1,x1,ymax,z1);
        line(x3,ymin,z1,x3,ymax,z1);
        line(x1,ymin,z1,x3,ymin,z1);
        line(x1,ymax,z1,x3,ymax,z1);
      }
      if(idx2==9){
        line(x2,ymin,z2,x2,ymax,z2);
        line(x4,ymin,z2,x4,ymax,z2);
        line(x2,ymin,z2,x4,ymin,z2);
        line(x2,ymax,z2,x4,ymax,z2);
      }
   }
}
}
#line 30159 "SEQ_11_09_2009.c"
#undef tdr
#undef nn
#undef x_width
#undef r_blade
#undef omega
#undef blader
#undef bw
#undef nchan
#undef ymax
#undef ymin
#undef tc
#undef delta
#undef nu
#undef w
#undef len
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'adjustable_slits'. */
  SIG_MESSAGE("adjustable_slits (McDisplay)");
  printf("MCDISPLAY: component %s\n", "adjustable_slits");
#define mccompcurname  adjustable_slits
#define mccompcurtype  Slit
#define mccompcurindex 34
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccadjustable_slits_xmin;
MCNUM xmax = mccadjustable_slits_xmax;
MCNUM ymin = mccadjustable_slits_ymin;
MCNUM ymax = mccadjustable_slits_ymax;
MCNUM radius = mccadjustable_slits_radius;
MCNUM cut = mccadjustable_slits_cut;
MCNUM width = mccadjustable_slits_width;
MCNUM height = mccadjustable_slits_height;
#line 73 "/usr/local/lib/mcstas/optics/Slit.comp"
{
  magnify("xy");
  if (radius == 0) {
    double xw, yh;
    xw = (xmax - xmin)/2.0;
    yh = (ymax - ymin)/2.0;
    multiline(3, xmin-xw, (double)ymax, 0.0,
              (double)xmin, (double)ymax, 0.0,
              (double)xmin, ymax+yh, 0.0);
    multiline(3, xmax+xw, (double)ymax, 0.0,
              (double)xmax, (double)ymax, 0.0,
              (double)xmax, ymax+yh, 0.0);
    multiline(3, xmin-xw, (double)ymin, 0.0,
              (double)xmin, (double)ymin, 0.0,
              (double)xmin, ymin-yh, 0.0);
    multiline(3, xmax+xw, (double)ymin, 0.0,
              (double)xmax, (double)ymin, 0.0,
              (double)xmax, ymin-yh, 0.0);
  } else {
    circle("xy",0,0,0,radius);
  }
}
#line 30217 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'Monitor1'. */
  SIG_MESSAGE("Monitor1 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "Monitor1");
#define mccompcurname  Monitor1
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 35
#define nchan mccMonitor1_nchan
#define TOF_N mccMonitor1_TOF_N
#define TOF_p mccMonitor1_TOF_p
#define TOF_p2 mccMonitor1_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccMonitor1_xmin;
MCNUM xmax = mccMonitor1_xmax;
MCNUM ymin = mccMonitor1_ymin;
MCNUM ymax = mccMonitor1_ymax;
MCNUM tmin = mccMonitor1_tmin;
MCNUM tmax = mccMonitor1_tmax;
char* filename = mccMonitor1_filename;
#line 94 "TOF_monitor2.comp"
{
  magnify("xy");
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 30250 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide29'. */
  SIG_MESSAGE("guide29 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide29");
#define mccompcurname  guide29
#define mccompcurtype  Channeled_guide
#define mccompcurindex 36
#define w1c mccguide29_w1c
#define w2c mccguide29_w2c
#define ww mccguide29_ww
#define hh mccguide29_hh
#define whalf mccguide29_whalf
#define hhalf mccguide29_hhalf
#define lwhalf mccguide29_lwhalf
#define lhhalf mccguide29_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide29_w1;
MCNUM h1 = mccguide29_h1;
MCNUM w2 = mccguide29_w2;
MCNUM h2 = mccguide29_h2;
MCNUM l = mccguide29_l;
MCNUM R0 = mccguide29_R0;
MCNUM Qcx = mccguide29_Qcx;
MCNUM Qcy = mccguide29_Qcy;
MCNUM alphax = mccguide29_alphax;
MCNUM alphay = mccguide29_alphay;
MCNUM W = mccguide29_W;
MCNUM k = mccguide29_k;
MCNUM d = mccguide29_d;
MCNUM mx = mccguide29_mx;
MCNUM my = mccguide29_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 30314 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide31'. */
  SIG_MESSAGE("guide31 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide31");
#define mccompcurname  guide31
#define mccompcurtype  Channeled_guide
#define mccompcurindex 37
#define w1c mccguide31_w1c
#define w2c mccguide31_w2c
#define ww mccguide31_ww
#define hh mccguide31_hh
#define whalf mccguide31_whalf
#define hhalf mccguide31_hhalf
#define lwhalf mccguide31_lwhalf
#define lhhalf mccguide31_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide31_w1;
MCNUM h1 = mccguide31_h1;
MCNUM w2 = mccguide31_w2;
MCNUM h2 = mccguide31_h2;
MCNUM l = mccguide31_l;
MCNUM R0 = mccguide31_R0;
MCNUM Qcx = mccguide31_Qcx;
MCNUM Qcy = mccguide31_Qcy;
MCNUM alphax = mccguide31_alphax;
MCNUM alphay = mccguide31_alphay;
MCNUM W = mccguide31_W;
MCNUM k = mccguide31_k;
MCNUM d = mccguide31_d;
MCNUM mx = mccguide31_mx;
MCNUM my = mccguide31_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 30382 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide32'. */
  SIG_MESSAGE("guide32 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide32");
#define mccompcurname  guide32
#define mccompcurtype  Channeled_guide
#define mccompcurindex 38
#define w1c mccguide32_w1c
#define w2c mccguide32_w2c
#define ww mccguide32_ww
#define hh mccguide32_hh
#define whalf mccguide32_whalf
#define hhalf mccguide32_hhalf
#define lwhalf mccguide32_lwhalf
#define lhhalf mccguide32_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide32_w1;
MCNUM h1 = mccguide32_h1;
MCNUM w2 = mccguide32_w2;
MCNUM h2 = mccguide32_h2;
MCNUM l = mccguide32_l;
MCNUM R0 = mccguide32_R0;
MCNUM Qcx = mccguide32_Qcx;
MCNUM Qcy = mccguide32_Qcy;
MCNUM alphax = mccguide32_alphax;
MCNUM alphay = mccguide32_alphay;
MCNUM W = mccguide32_W;
MCNUM k = mccguide32_k;
MCNUM d = mccguide32_d;
MCNUM mx = mccguide32_mx;
MCNUM my = mccguide32_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 30450 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'guide34'. */
  SIG_MESSAGE("guide34 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "guide34");
#define mccompcurname  guide34
#define mccompcurtype  Channeled_guide
#define mccompcurindex 39
#define w1c mccguide34_w1c
#define w2c mccguide34_w2c
#define ww mccguide34_ww
#define hh mccguide34_hh
#define whalf mccguide34_whalf
#define hhalf mccguide34_hhalf
#define lwhalf mccguide34_lwhalf
#define lhhalf mccguide34_lhhalf
{   /* Declarations of SETTING parameters. */
MCNUM w1 = mccguide34_w1;
MCNUM h1 = mccguide34_h1;
MCNUM w2 = mccguide34_w2;
MCNUM h2 = mccguide34_h2;
MCNUM l = mccguide34_l;
MCNUM R0 = mccguide34_R0;
MCNUM Qcx = mccguide34_Qcx;
MCNUM Qcy = mccguide34_Qcy;
MCNUM alphax = mccguide34_alphax;
MCNUM alphay = mccguide34_alphay;
MCNUM W = mccguide34_W;
MCNUM k = mccguide34_k;
MCNUM d = mccguide34_d;
MCNUM mx = mccguide34_mx;
MCNUM my = mccguide34_my;
#line 228 "/usr/local/lib/mcstas/obsolete/Channeled_guide.comp"
{
  double x;
  int i;

  magnify("xy");
  for(i = 0; i < k; i++)
  {
    multiline(5,
              i*w1c - w1/2.0, -h1/2.0, 0.0,
              i*w2c - w2/2.0, -h2/2.0, (double)l,
              i*w2c - w2/2.0,  h2/2.0, (double)l,
              i*w1c - w1/2.0,  h1/2.0, 0.0,
              i*w1c - w1/2.0, -h1/2.0, 0.0);
    multiline(5,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0,
              (i+1)*w2c - d - w2/2.0, -h2/2.0, (double)l,
              (i+1)*w2c - d - w2/2.0,  h2/2.0, (double)l,
              (i+1)*w1c - d - w1/2.0,  h1/2.0, 0.0,
              (i+1)*w1c - d - w1/2.0, -h1/2.0, 0.0);
  }
  line(-w1/2.0, -h1/2.0, 0.0, w1/2.0, -h1/2.0, 0.0);
  line(-w2/2.0, -h2/2.0, (double)l, w2/2.0, -h2/2.0, (double)l);
}
#line 30518 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef lhhalf
#undef lwhalf
#undef hhalf
#undef whalf
#undef hh
#undef ww
#undef w2c
#undef w1c
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'E_det'. */
  SIG_MESSAGE("E_det (McDisplay)");
  printf("MCDISPLAY: component %s\n", "E_det");
#define mccompcurname  E_det
#define mccompcurtype  E_monitor
#define mccompcurindex 40
#define nchan mccE_det_nchan
#define filename mccE_det_filename
#define restore_neutron mccE_det_restore_neutron
#define E_N mccE_det_E_N
#define E_p mccE_det_E_p
#define E_p2 mccE_det_E_p2
#define S_p mccE_det_S_p
#define S_pE mccE_det_S_pE
#define S_pE2 mccE_det_S_pE2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mccE_det_xmin;
MCNUM xmax = mccE_det_xmax;
MCNUM ymin = mccE_det_ymin;
MCNUM ymax = mccE_det_ymax;
MCNUM xwidth = mccE_det_xwidth;
MCNUM yheight = mccE_det_yheight;
MCNUM Emin = mccE_det_Emin;
MCNUM Emax = mccE_det_Emax;
#line 127 "/usr/local/lib/mcstas/monitors/E_monitor.comp"
{
  magnify("xy");
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 30565 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef S_pE2
#undef S_pE
#undef S_p
#undef E_p2
#undef E_p
#undef E_N
#undef restore_neutron
#undef filename
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'Sample_Arm'. */
  SIG_MESSAGE("Sample_Arm (McDisplay)");
  printf("MCDISPLAY: component %s\n", "Sample_Arm");
#define mccompcurname  Sample_Arm
#define mccompcurtype  Arm
#define mccompcurindex 41
#line 43 "/usr/local/lib/mcstas/optics/Arm.comp"
{
  /* A bit ugly; hard-coded dimensions. */
  magnify("");
  line(0,0,0,0.2,0,0);
  line(0,0,0,0,0.2,0);
  line(0,0,0,0,0,0.2);
}
#line 30594 "SEQ_11_09_2009.c"
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 'sample'. */
  SIG_MESSAGE("sample (McDisplay)");
  printf("MCDISPLAY: component %s\n", "sample");
#define mccompcurname  sample
#define mccompcurtype  V_sample
#define mccompcurindex 42
#define StructVarsV mccsample_StructVarsV
#define VarsV mccsample_VarsV
{   /* Declarations of SETTING parameters. */
MCNUM radius_i = mccsample_radius_i;
MCNUM radius_o = mccsample_radius_o;
MCNUM h = mccsample_h;
MCNUM focus_r = mccsample_focus_r;
MCNUM pack = mccsample_pack;
MCNUM frac = mccsample_frac;
MCNUM f_QE = mccsample_f_QE;
MCNUM gamma = mccsample_gamma;
MCNUM target_x = mccsample_target_x;
MCNUM target_y = mccsample_target_y;
MCNUM target_z = mccsample_target_z;
MCNUM focus_xw = mccsample_focus_xw;
MCNUM focus_yh = mccsample_focus_yh;
MCNUM focus_aw = mccsample_focus_aw;
MCNUM focus_ah = mccsample_focus_ah;
MCNUM xwidth = mccsample_xwidth;
MCNUM yheight = mccsample_yheight;
MCNUM zthick = mccsample_zthick;
MCNUM rad_sphere = mccsample_rad_sphere;
MCNUM sig_a = mccsample_sig_a;
MCNUM sig_i = mccsample_sig_i;
MCNUM V0 = mccsample_V0;
int target_index = mccsample_target_index;
MCNUM multiples = mccsample_multiples;
#line 318 "/usr/local/lib/mcstas/samples/V_sample.comp"
{
  magnify("xyz");
  if (VarsV.shapetyp == 0) {
    circle("xz", 0,  h/2.0, 0, radius_i);
    circle("xz", 0,  h/2.0, 0, radius_o);
    circle("xz", 0, -h/2.0, 0, radius_i);
    circle("xz", 0, -h/2.0, 0, radius_o);
    line(-radius_i, -h/2.0, 0, -radius_i, +h/2.0, 0);
    line(+radius_i, -h/2.0, 0, +radius_i, +h/2.0, 0);
    line(0, -h/2.0, -radius_i, 0, +h/2.0, -radius_i);
    line(0, -h/2.0, +radius_i, 0, +h/2.0, +radius_i);
    line(-radius_o, -h/2.0, 0, -radius_o, +h/2.0, 0);
    line(+radius_o, -h/2.0, 0, +radius_o, +h/2.0, 0);
    line(0, -h/2.0, -radius_o, 0, +h/2.0, -radius_o);
    line(0, -h/2.0, +radius_o, 0, +h/2.0, +radius_o);
  }
  else { 
	if (VarsV.shapetyp == 1) {
      double xmin = -0.5*xwidth;
      double xmax =  0.5*xwidth;
      double ymin = -0.5*yheight;
      double ymax =  0.5*yheight;
      double zmin = -0.5*zthick;
      double zmax =  0.5*zthick;
      multiline(5, xmin, ymin, zmin,
                   xmax, ymin, zmin,
                   xmax, ymax, zmin,
                   xmin, ymax, zmin,
                   xmin, ymin, zmin);
      multiline(5, xmin, ymin, zmax,
                   xmax, ymin, zmax,
                   xmax, ymax, zmax,
                   xmin, ymax, zmax,
                   xmin, ymin, zmax);
      line(xmin, ymin, zmin, xmin, ymin, zmax);
      line(xmax, ymin, zmin, xmax, ymin, zmax);
      line(xmin, ymax, zmin, xmin, ymax, zmax);
      line(xmax, ymax, zmin, xmax, ymax, zmax);
    }
    else {
      circle("xy", 0,  0.0, 0, rad_sphere);
      circle("xz", 0,  0.0, 0, rad_sphere);
      circle("yz", 0,  0.0, 0, rad_sphere);        
    }
  }
}
#line 30679 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef VarsV
#undef StructVarsV
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 't_mon_detC'. */
  SIG_MESSAGE("t_mon_detC (McDisplay)");
  printf("MCDISPLAY: component %s\n", "t_mon_detC");
#define mccompcurname  t_mon_detC
#define mccompcurtype  Monitor_nD
#define mccompcurindex 43
#define options mcct_mon_detC_options
#define filename mcct_mon_detC_filename
#define user1 mcct_mon_detC_user1
#define user2 mcct_mon_detC_user2
#define user3 mcct_mon_detC_user3
#define username1 mcct_mon_detC_username1
#define username2 mcct_mon_detC_username2
#define username3 mcct_mon_detC_username3
#define DEFS mcct_mon_detC_DEFS
#define Vars mcct_mon_detC_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detC_xwidth;
MCNUM yheight = mcct_mon_detC_yheight;
MCNUM zthick = mcct_mon_detC_zthick;
MCNUM xmin = mcct_mon_detC_xmin;
MCNUM xmax = mcct_mon_detC_xmax;
MCNUM ymin = mcct_mon_detC_ymin;
MCNUM ymax = mcct_mon_detC_ymax;
MCNUM zmin = mcct_mon_detC_zmin;
MCNUM zmax = mcct_mon_detC_zmax;
MCNUM bins = mcct_mon_detC_bins;
MCNUM min = mcct_mon_detC_min;
MCNUM max = mcct_mon_detC_max;
MCNUM restore_neutron = mcct_mon_detC_restore_neutron;
#line 396 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  Monitor_nD_McDisplay(&DEFS, &Vars);
}
#line 30721 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 't_mon_detB'. */
  SIG_MESSAGE("t_mon_detB (McDisplay)");
  printf("MCDISPLAY: component %s\n", "t_mon_detB");
#define mccompcurname  t_mon_detB
#define mccompcurtype  Monitor_nD
#define mccompcurindex 44
#define options mcct_mon_detB_options
#define filename mcct_mon_detB_filename
#define user1 mcct_mon_detB_user1
#define user2 mcct_mon_detB_user2
#define user3 mcct_mon_detB_user3
#define username1 mcct_mon_detB_username1
#define username2 mcct_mon_detB_username2
#define username3 mcct_mon_detB_username3
#define DEFS mcct_mon_detB_DEFS
#define Vars mcct_mon_detB_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detB_xwidth;
MCNUM yheight = mcct_mon_detB_yheight;
MCNUM zthick = mcct_mon_detB_zthick;
MCNUM xmin = mcct_mon_detB_xmin;
MCNUM xmax = mcct_mon_detB_xmax;
MCNUM ymin = mcct_mon_detB_ymin;
MCNUM ymax = mcct_mon_detB_ymax;
MCNUM zmin = mcct_mon_detB_zmin;
MCNUM zmax = mcct_mon_detB_zmax;
MCNUM bins = mcct_mon_detB_bins;
MCNUM min = mcct_mon_detB_min;
MCNUM max = mcct_mon_detB_max;
MCNUM restore_neutron = mcct_mon_detB_restore_neutron;
#line 396 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  Monitor_nD_McDisplay(&DEFS, &Vars);
}
#line 30771 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 't_mon_detD'. */
  SIG_MESSAGE("t_mon_detD (McDisplay)");
  printf("MCDISPLAY: component %s\n", "t_mon_detD");
#define mccompcurname  t_mon_detD
#define mccompcurtype  Monitor_nD
#define mccompcurindex 45
#define options mcct_mon_detD_options
#define filename mcct_mon_detD_filename
#define user1 mcct_mon_detD_user1
#define user2 mcct_mon_detD_user2
#define user3 mcct_mon_detD_user3
#define username1 mcct_mon_detD_username1
#define username2 mcct_mon_detD_username2
#define username3 mcct_mon_detD_username3
#define DEFS mcct_mon_detD_DEFS
#define Vars mcct_mon_detD_Vars
{   /* Declarations of SETTING parameters. */
MCNUM xwidth = mcct_mon_detD_xwidth;
MCNUM yheight = mcct_mon_detD_yheight;
MCNUM zthick = mcct_mon_detD_zthick;
MCNUM xmin = mcct_mon_detD_xmin;
MCNUM xmax = mcct_mon_detD_xmax;
MCNUM ymin = mcct_mon_detD_ymin;
MCNUM ymax = mcct_mon_detD_ymax;
MCNUM zmin = mcct_mon_detD_zmin;
MCNUM zmax = mcct_mon_detD_zmax;
MCNUM bins = mcct_mon_detD_bins;
MCNUM min = mcct_mon_detD_min;
MCNUM max = mcct_mon_detD_max;
MCNUM restore_neutron = mcct_mon_detD_restore_neutron;
#line 396 "/usr/local/lib/mcstas/monitors/Monitor_nD.comp"
{
  Monitor_nD_McDisplay(&DEFS, &Vars);
}
#line 30821 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef Vars
#undef DEFS
#undef username3
#undef username2
#undef username1
#undef user3
#undef user2
#undef user1
#undef filename
#undef options
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  /* MCDISPLAY code for component 't_mon2'. */
  SIG_MESSAGE("t_mon2 (McDisplay)");
  printf("MCDISPLAY: component %s\n", "t_mon2");
#define mccompcurname  t_mon2
#define mccompcurtype  TOF_monitor2
#define mccompcurindex 46
#define nchan mcct_mon2_nchan
#define TOF_N mcct_mon2_TOF_N
#define TOF_p mcct_mon2_TOF_p
#define TOF_p2 mcct_mon2_TOF_p2
{   /* Declarations of SETTING parameters. */
MCNUM xmin = mcct_mon2_xmin;
MCNUM xmax = mcct_mon2_xmax;
MCNUM ymin = mcct_mon2_ymin;
MCNUM ymax = mcct_mon2_ymax;
MCNUM tmin = mcct_mon2_tmin;
MCNUM tmax = mcct_mon2_tmax;
char* filename = mcct_mon2_filename;
#line 94 "TOF_monitor2.comp"
{
  magnify("xy");
  multiline(5, (double)xmin, (double)ymin, 0.0,
               (double)xmax, (double)ymin, 0.0,
               (double)xmax, (double)ymax, 0.0,
               (double)xmin, (double)ymax, 0.0,
               (double)xmin, (double)ymin, 0.0);
}
#line 30864 "SEQ_11_09_2009.c"
}   /* End of SETTING parameter declarations. */
#undef TOF_p2
#undef TOF_p
#undef TOF_N
#undef nchan
#undef mccompcurname
#undef mccompcurtype
#undef mccompcurindex

  printf("MCDISPLAY: end\n");
} /* end display */
#undef magnify
#undef line
#undef dashed_line
#undef multiline
#undef rectangle
#undef box
#undef circle
