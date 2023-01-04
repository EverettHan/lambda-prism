#ifndef CATProDynTrimSewDef_h_
#define CATProDynTrimSewDef_h_

/**
 * @level Protected
 * @usage U1
 */

/**
 * @nodoc
 * The TrimSew PreviewMode.
 * @param CATDynTrimmedSkinShellPreview
 * To visualize the trimmed SkinShell.
 */
enum CATDynTrimSewPreviewMode
{
  CATDynTrimmedSkinShellPreview
};

/**
 * @nodoc
 * The TrimSew Initialization mode.
 * @param CATDynTrimSewIntersectionInitMode
 * Start with the intersection of the SkinShell with the covered faces.
 * @param CATDynTrimSewLaydownInitMode
 * Start with the border edges of the SkinShell that are lying on the TrimShell
 * (in this case it is advisable to provide said border edges (see below).
 * @param CATDynTrimSewLaydownAndInterInitMode
 * Default option.
 * @param CATDynTrimSewAlreadyLaidOnInitMode
 * Start with edges already laid on covered faces.
 * @param CATDynTrimSewNoneInitMode
 * Does not start with initialisation on covered faces but on faces adjacent to covered faces.
 */
enum CATDynTrimInitMode
{
  CATDynTrimSewIntersectionInitMode,
  CATDynTrimSewLaydownInitMode,
  CATDynTrimSewLaydownAndInterInitMode,
  CATDynTrimSewAlreadyLaidOnInitMode,
  CATDynTrimSewNoneInitMode
};

/**
 * @nocgmitf
 * @nodoc
 * The TrimSew Relimitation mode - applies only for free borders, so useless for not surfacic shells.
 * @param CATDynTrimSewDefaultRelimMode
 * Free borders are not relimited, journal reports for border edges may be missing
 * (it's the caller's responsability to handle this, and it's useful when
 *  free edges have been specified, for example).
 * @param CATDynTrimSewNoneRelimMode
 * Free borders are not relimited, but journal is checked to ensure all free borders
 * are followed, except those specified with the SetListOfFreeEdges API.
 */
enum CATDynTrimRelimMode
{
  CATDynTrimSewDefaultRelimMode,
  CATDynTrimSewNoneRelimMode
};

#endif /* CATProDynTrimSewDef_h_ */
