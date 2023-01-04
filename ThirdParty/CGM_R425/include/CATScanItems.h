#ifndef CATScanItems_H 
#define CATScanItems_H 

/*
Creation 09/09/2005   JHN
balayage de journal pour action specifique sur les item. Cette action est a coder effectivement
 */
#include "YP00IMPL.h"

class CATCGMJournalItem;
class CATCGMJournalList;

// peut etre utilise dans CATScanItems
// test si l'item est un ordre de creation d'un vertex 1 si vrai 0 si faux
ExportedByYP00IMPL int CATTestTildaResult(CATCGMJournalItem * iItem);

// peut etre utilise dans CATScanItems
// test si l'item est un ordre de creation d'un vertex 1 si vrai 0 si faux
ExportedByYP00IMPL int CATTestVertex(CATCGMJournalItem * iItem);

// peut etre utilise dans CATScanItems
// test si l'item est un ordre de deletion 1 si vrai 0 si faux
ExportedByYP00IMPL int CATTestDeletion(CATCGMJournalItem * iItem);

// peut etre utilise dans CATScanItems
// test si l'item est un ordre de Keep 1 si vrai 0 si faux
ExportedByYP00IMPL int CATTestKeep(CATCGMJournalItem * iItem);

// test si 'il y a des items dans le journal ou non
// test si l'item est un ordre de Keep 1 si vrai 0 si faux
ExportedByYP00IMPL int IsJournalEmpty(CATCGMJournalList * iList);

// balaie le CATCGMJournalList et applique la methode iTestsItem sur chaque item du journal
// iTestItem est prend en entree un item. le resultat rendu vaut
//         0 alors il n'y aura pas de traitement sur l'item dans CATDeleteItem 
//         1, alors l'item sera rendu inactif
// iTestItem peut aussi faire un traitement interne sur l'item a condition de ne pas le faire disparaitre
// iTass permet de preciser la realisation du tass en entree du traitement (1) en sortie du traitement (2), en entree et en sortie
// (3) ou pas de tass (0)
ExportedByYP00IMPL void CATScanItems(CATCGMJournalList * ioCurJournal, int iTass, int (* iTestItem) (CATCGMJournalItem *) );

#endif


