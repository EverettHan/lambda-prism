#ifndef CATTopEdgePropagationDiagnosis_h_
#define CATTopEdgePropagationDiagnosis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Defines the various propagation diagnoses at a wire start or end extremity.
 * @param EMPTY_SELECTION
 * No more edge to be selected on this side ( case where input body is a wire ).
 * @param CLOSED_SELECTION
 * A closed selection has been found ( output wire is a closed wire ).
 * @param POINT_DISCONTINUITY
 * A point discontinuity ( gap within vertex ) has been found.
 * @param ANGULAR_DISCONTINUITY
 * An angular discontinuity has been found.
 * @param CURVATURE_DISCONTINUITY
 * A curvature discontinuity has been found.
 * @param MULTIPLE_SOLUTION
 * Propagation stops because several edges meet the criteria ( ambiguity ).
* @param NON_MANIFOLD_CASE
 * Propagation stops because there are several wires in a non manifold configuration.
*/
enum CATTopEdgePropagationDiagnosis { EMPTY_SELECTION          = 0 , 
                                      CLOSED_SELECTION         = 1 ,
                                      POINT_DISCONTINUITY      = 2 ,
                                      ANGULAR_DISCONTINUITY    = 3 ,
                                      CURVATURE_DISCONTINUITY  = 4 ,
                                      MULTIPLE_SOLUTION        = 5 ,
                                      NON_MANIFOLD_CASE        = 6 };

#endif /* CATTopEdgePropagationDiagnosis_h_ */
