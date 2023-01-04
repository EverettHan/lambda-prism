#ifndef LesBonnesRecettesDuPereLochard_h
#define LesBonnesRecettesDuPereLochard_h
// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
//
// Les bonnes recettes du pere Lochard
// macro for easy XRef search
//
//=============================================================================
// 12/01/09 NLD Creation
// 02/12/09 NLD Ajout quick summary
// 16/11/10 NLD Mention dans le quick summary des CATCGMProgressBar
// 03/06/11 NLD Mention dans le quick summary de  CATCompactCallStackManager
// 25/01/12 NLD Mention dans le quick summary de  CATCatchSecured
//              (livraison le 05/12/14)
// 06/12/14 NLD Mention dans le quick summary de  CATReturnManager
//              Mention dans le quick summary de l'usage des outils associes
//              a la CATSoftwareConfiguration pour determiner l'objet racine en leak
// 22/03/18 NLD Mention dans le quick summary de CATFrFOperator
//              Ajouts sur CATCompactCallStackManager ((catcgmerrorcreationnewstack()), (catcxunlicensedopenconfignewstack))
// 14/01/22 NLD Mention dans le quick summary de CATMathVersionningActive()
// 09/02/22 NLD Mention dans le quick summary de CATCGMemoryPoolTraceFilter
// 05/04/22 NLD Mention dans le quick summary de CATTopDataOnTheFlyWrapper
//=============================================================================
// --> A reporter dans WikiCGM: informations au 14/01/22: copy date 27 July 2012, updated 05 December 2014
//=============================================================================
#include <CATMathematics.h>
//
// should be used by subscribers like that: LesBonnesRecettesDuPereLochard(Id, "title");
#define LesBonnesRecettesDuPereLochard(Id,Title) extern ExportedByCATMathematics const int Id//

//=============================================================================
// Quick toolkit summary
//=============================================================================
LesBonnesRecettesDuPereLochard(PereLochardToolkit_021209, "Quick pere Lochard toolkit summary for debug and analysis");
/*
The PereLochard toolkit, for developing, maintaining, and optimizing software, is a set of shared open and breakthru
("to the other side") tools, techniques, methodologies and knowhows for all steps of development,
and mainly dedicated to geometric modeler software,
having lead to 100% XScale compatibility (small and large scale full support including reliability,
performance, behavior and numerical precision) of sweeping and lofting computations,
and to 60% performance improvement of these softwares, as well as quick and easy analysis and solve of
advanced mathematics algorithms problems,
in addition to efficiency improvements in daily maintenance.
The most general tools are shared and available through XRef (in "Show references" mode) with keyword/identifier
"LesBonnesRecettesDuPereLochard".


1) Tools and techniques for all sorts of leaks:
(model object, memory, cgm object).
Finding the reason for unfreed objects when hundred or even thousands of references to the object are created and removed
is a complex, costly, and often not converging task, if no tools helps finding the remaining, unremoved, reference.
(the root cause being the absence of signed references: all references are anonymous and undistinguishable).
- The most difficult case concerns the CATSoftwareConfiguration objects: in a complex topological operator, thousands of references
to this objet are done. A first and easy to use tool is an environnement variable (CGMDebugStaticTopData) which helps
finding in one shot the CATTopData object not freed (typical of VC8 compiler options with no stack object deallocation
when exceptions are raised). A second tool for far more complex cases, is an environnement variable (CGMDebugRefForSoftwareConfiguration),
coupled with the use of signed references with new software (CATSoftwareConfigurationAddRef(), CATSoftwareConfigurationRelease()), 
and a converging debug methodology, allowing to iterate on code equipment with this software, only on the execution sub tree showed by previous
iteration. This tool has leaded to full CATSoftwareConfiguration leaks solving on CGM test cases. It may also help finding the root leak object
in case of multiple objects leaks.
- For other objects, in CATBaseUnknown derivate classes, and for equations locks, we propose a methodology based on iterative approach,
and on code equipment with new tools (CATAddRef/CATRelease, CATLockGeometry.h); even with a great many references, these tools
give a quick converging debug process, leading to the missing reference. For middle complexity problems, a first value of
environment variables associated to these tools, simply activates the generation of CATCGMDebugReference objects, managing the 
couples (referenced object, referencing object) (and number of references), and a trace and breakpoint system, with target values,
leading to the error. For high complexity problems, a second value of the environment variables, also deactivates the real reference
management system (AddRef()/Release(), Lock()/Unlock()) for all references migrated on the debug tool. Doing that, we can check, at each
code modification, if the error is still in the non migrated code, or not. If it is, the CATCGMDebugReference tools will give the soluton. 
If not, code equipment may go on, but the number of breakpoints hits under the classic reference tool (generally speaking: catcxtag()
under AddRef()), is always diminuing.
In addition, we give a compact call stack traces system, in one line, based on automatic methods numbering, that may be helpful.
- For CGM model objects with pool allocation, we propose an environment variable CATCGMemoryPoolTraceFilter,
complementary to CATCGMemoryPoolTrace=1, for filtered traces and Tag information.
- For memory leaks, see below.
- For callstack management tool, see below.
Finally, we propose a very simple and easy to use tool, CATReturnManager, usable with almost no code change, hence no side effect,
for fixing leaks of objects remaining on stack after exception throw.


2) Tools for all sorts of memory problems
- CATCallCount for all sorts of complex memory problems (MLK, UMR), leading in one shot to the right occurence
of the instruction causing the problem, in a massively iterative context; the solution is based on an automatic modification
of the callstack using the occurence number, that hence will be directly readable in the output of MEMORYCHECK tool.
Then a single debug session iteration, with a breakpoint system equipped with target value, will give the solution.
A special use is dedicated to objects leaks, using the object tag instead of the call number, in the stack.
- Another tool is a debug class CATCGMDummyObject that can be directly used when MEMORYCHECK has given the error stack: it turns the
memory problem in a classic CGM object leak problem, with the classic and easy to use cgm memory pool debug tools.
- An iterative and convergent debugging methodology is given, using a debugger hitcount brakpoints stack to debug any complex
scenario leading to an incorrect numeric value.


3) Tools and techniques for data transmission bypassing CAA header or architecture rules
(container (CATMathFunctionXContainer), secured mail stack (CATFedex)) are used for secured CATSoftwareConfiguration transmission to
solve and minimize tools, before next Catia release and CAA header modification. The secured mail is also used for data transmission
to basic mathematical objects rarely needing extra data (CATMathTransformation using factory scale through CATMathDebugScale(),
CATMathSetOfPointsND using CGM software level through CATMathDirtyCGMLevel()). CATMathVersionningActive macro may be used for versionning
of a mathematical object with no direct access to versionning tools and variables.
CATTopDataOnTheFlyWrapper allows call of a standard topological operator interface requiring a CATTopData even with reception
of a NULL software configuration.

4) Tools for derivatives controls and solve/minimize tools:
- Advanced mathematic tools have always been, ever since V5 creation, black box tools, based on iterative of recursive solving techniques,
 with no debugging options at all, hiding to everyone their own weaknesses, as well as some frequent inconsistencies between
 their own hypotheses and the continuity levels of the functions they were called with (up to 2 or 3 continuity level gaps,
 between expected and received).
 Breakpoints have been setted for problem detections, and it is now possible at each iteration of these solving tools,
to easily check function behaviour on current subinterval, with possible refinement with simple changes under debugger
(sampling tools, with traces in standard output file are given for one variable and two variable functions, see CATMathFunctionDebugTool).
 In addition, in the case of complex functions using many subfunctions (for example several hundreds of components,
 and several deepness level, for functions based on complex surfaces), a spy mode, used simultaneously with buildtime options,
 allows a post re-sampling of all subfunctions, on their own subintervals, in order to quickly find the problem root cause,
 that is the first subfunction being unstable or not continuous enough.
- A derivative problem thus being found, another tool allows complex derivative debug (CATDebugDeriv) (see below), particularly useful
for FreeForm functions based on deep objects architecture.
- Problem isolation is possible with a few simple debugger operations (see below)


5) Tools for root cause analysis:
- CATDebugDeriv to find, in any complex mathematical function, derivative evaluator, the first intermediate expression badly derived
(tool compatible with multiple parameter change)
- CATMathFunctionDebugTool, in spy mode, to find, in any function heavily using sub functions (with deep recursivity level 
or/and several hundreds of subfunctions), ths first subfunction having a wrong or unstable derivate evaluator.
- CATGetDefaultToleranceBreakpoint to find the very first object accessing the default tolerance object (not linked to
current scaled factory) that will really be badly used later on (XScale context).
- CATGetDefaultParamReferenceBreakPoint to find the very first object accessing the default crv/sur param reference object
(not linked to a curve or a surface), that will really be used later on.


6) Tools for sharp CPU analysis in a massive and complex call tree
(CATCGMOperatorDebug, CATCGMOperatorSpecialImplementation, TestSurfacicSweepAllStars)
- Performance analysis may be rather difficult generally speaking, opposing measure on global test data base,
giving general statements, and on particular scenario, giving sharp results but on particular data.
A quick instrumentation of CATCGMOperator::Run() may be useful, as it can give operator-scenario links
in a global measure involving thousands of scenario and as many types of derived classes of CATCGMOperator as existing
(see CATCGMOperatorSpecialImplementation.cpp for buildtime activation by precompilation directive).
This buildtime generation of entry points and links is allowed by a set of generic macros (see CATMathMultipleDefineMacro.h)
with a short number of lines varying with log(n) where n is the maximum number of scenarii allowed
(about 50 lines for 3500 scenarii).
- An other very annoying problem in CPU analysis for CGM test cases is the unique entry point CATCGMOperator::Run in which
all sequences of code running derived CATCGMOperator classes are undistinguishable; for example, for two sequences of code
in which two classes Ai and Aj call two operators Bi and Bj, the standard CPU analysis tree gives
Ai->CATCGMOperator::Run(), Aj->CATCGMOperator::Run(),
and
CATCGMOperator::Run()->Bi::RunOperator() and CATCGMOperator::Run()->Bj::RunOperator(),
but there is absolutely no link in the tree between Ai and Bi, or between Aj and Bj.
The analysis becomes particularly difficult when there are many classes, many operators, and when i has large values.
A special buildtime and runtime switch has been provided (see CATCGMOperatorDebug.h) in order to break this
- Test cases grouping is necessary for advanced analysis. CGM test tools have been enhanced to manage several groups, and several groups
of test cases groups. About 3500 sweep test cases are measurable at same time through TestSurfacicSweepAllStars.

Additionnaly we mention the existence of debug and quality control tools on the progress bar objects, allowing to
measure and enhance quality (sharpness and consistency) of an algorithm progression described
with a CATCGMProgressBar object. These tools give graphic output for progression and point out the worst quality
points, with a breakpoint system to be used with a debugger. 


7) Tools for problem isolation
CATMathOperatorFunctionX and CATCGMOperatorDummy for dynamic generation, at chosen breakpoint and hitcount,
by callback from mathematical framework to geometrical framework, of a CGM operator allowing record -and then replay-
of a solve or minimize operation on any function. Additionnaly, dynamic load for complex functions stream/unstream code has been provided,
as well as code instrumentation for detection, on a complex function
using hundred of subfunctions at several deepness level, of the first not already streamable function.
Any mathematical problem is now potentially recordable.
Several filters are available associated with the 3 main mathematical tools (Solve(), SolveNewton(), Minimize()), in standard mode or 
in debug mode (automatic algorithm behaviour trace and sampling in CGMReplay output window), or with all three at the same time.

For pseudo operators with no inheritance from CATTopOperator or CATCGMoperator,
CATFrFOperator header gives a set of macros for quick and easy implementation of CGMReplay instrumentation

8) Tools for XScale debug and certification
XScale compatibility of CGM software, that is the full support of small and large scales, cannot be certified without
a set of dynamic check tools. We propose several check families and tools, for the following rules
- Forbidden access to length depending values, on the default CATTolerance object not setted with current Scale.
The associated tool includes a root cause system.
- Forbidden direct access to mathematical tolerances CATEpsg, CATEpsilon, ...: The tools are based on a buildtime set of macros
replacing these constants by function calls. They include error raising and/or statistics generation, easy runtime debug, and
handling old unstreamed functions particular cases.
- Forbidden access to advanced mathematical tools (function solving, function minimizing, system solving, ...) with a missing
or not certified CATMathScaleOption attribute describing the behaviour of each function parameter and each function value in relation to
the powers of the factory scale, or with a non certified parameter for the mathematical tool used (acceptance tolerance, ...).
The tools are based on a set of breakpoints allowing dynamic parallel check at 2 or more different scales, and on reviewing attributes.
This system is compatible with complex objects that can have several behaviours, as long as the scale options and the reviewing
attributes are managed considering these multiple behaviours (Free form comb, free form cleaning and smoothing tools for example)
- Forbidden access to laws (CATLaw object) without dynamic certification and review of law behaviour in relation to scale power
including parameter and value).
- Forbidden access to hardcoded numerical value (dynamic tool using CATHardTol())
- Generic tool for XScale support at CGMReplay loading of a topological operator
These tools have been used for obtaining a full XScale support of Sweep and loft softwares, including result precision and
CPU consumed. This support has meant hundreds of corrections, or more, in called softwares.


9) General tools
A simple call stack management software CATCompactCallStackManager, may be used in a great number of situations: it helps
finding the various call stacks leading to an instruction, and allows, with a final summary of all stacks with optional user weights,
as well as a debugger mode allowing management of a unique beakpoint hit for each call stack, a quick and easy search and
focus on most important call stacks.
This tool may be used, for example, in algorithm convergence study, leak search, optimization process, data check,
software migration, exception management, ...
This tool is already plugged for unique call stack debugger breakpoint associated to standard searches
(error rising (catcgmerrorcreationnewstack()), open software configuration use (catcxunlicensedopenconfignewstack), ...)


10) Tools combination
These tools may be used at the same time or one after the other on a single process;
For example a performance enhancement process may start with a global CPU tree analysis in CGMOperator-scenario link mode,
go on with a single test case replay in which advanced mathematics breakpoints will help isolate a replay file targetting the
solve or minimize problem, then with a sharp function derivative analysis on that replay file.


11) Optimization techniques
60% performance enhancement on sweep and loft softwares whole test data basis have been obtained using analysis tools described above,
and various techniques; among them:
New geometrical filters, memorization tools, derivatives debug and corrections, operators re-use, rough length computations
 when sufficient, equations locks, finite differences grid evaluators, unappropriate hash table uses suppression, allocations replacement
 by stack data, better insertions management in large set of points, equations share between coordinates for offset surfaces
 (including sharing post reengineering after separate equation deep duplications), and many others...


12) Secured exception management
As we must be aware that NO scalar or pointer local data can be safely accessed after exception catch, it not protected
with a "volatile" declaration, we propose a converging methodology towards safe software on any platform,
with a handful of full and stable securitization techniques avoiding further access
or non secured variable, and a set of macros CATTrySecured, CATCatchSecured, CATCatchOthersSecured, CATEndTrySecured,
to be used when full securization has been done, and that are combined with centralized breakpoints (catcgmcatchsecured(),
catcgmcatchunsecured()), and global counters, as well as quick summary in CGM test cases status files. These tools also allow
to forbid any use of unsecured exception management under a dedicated test operator.

*/
//=============================================================================

#endif
