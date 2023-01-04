public:
  /**
   * Constructs the envelop.
   * @param iHandledObject
   *   The letter
   * @param iItfDestrBehavior
   *   If it's <tt>TRUE</tt>, the letter will be deleted with the envelop.
   */
  CATCGM_ITF_IMPL_CLASS(CATCGM_ITF_CONCRETE_CLASS &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior);

protected:
  /**
   * @nodoc
   * Constructs the envelop linked with a previous one.
   * @param iPreviousItf
   *   The previous envelop.
   */
  CATCGM_ITF_IMPL_CLASS(CATCGMVirtualItf &iPreviousItf);

  /**
   * Destructor
   */
  virtual ~CATCGM_ITF_IMPL_CLASS();

public:
  // ---------- IUnknown

  virtual HRESULT __stdcall QueryInterface(const IID &iIID, void **oPPV);

  virtual ULONG __stdcall AddRef();

  virtual ULONG __stdcall Release();

  // ---------- Meta class associated with the interface class

  static const CATCGMItfMetaClass &CATCGM_ITF_METACLASS();

  // ---------- CATCGMVirtualItf

  virtual const CATCGMItfMetaClass &GetItfMetaClass() const;

protected:
  virtual CATCGMItfInternalData &GetInternalData();

private:
  /**
   * @nodoc
   * Creates a new envelop, the first one for the object to handle.
   * @return
   *   The new envelop.
   */
  static CATCGMVirtualItf *MakeRootItf(CATCGMVirtual &iHandledObject, CATCGMItfDestrBehavior iItfDestrBehavior);

  /**
   * @nodoc
   * Creates a new envelop linked with a previous one.
   * @return
   *   The new envelop.
   */
  static CATCGMVirtualItf *MakeLinkedItf(CATCGMVirtualItf &iPreviousItf);

public:
