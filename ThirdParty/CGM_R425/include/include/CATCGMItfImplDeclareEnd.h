
private:
  CATCGM_ITF_IMPL_CLASS(const CATCGM_ITF_IMPL_CLASS &iObject); // Interdit
  CATCGM_ITF_IMPL_CLASS &operator=(const CATCGM_ITF_IMPL_CLASS &iObject); // Interdit

  CATCGMItfInternalData _InternalData;
  unsigned int _RefCnt;

  static CATCGMItfMetaClass _ItfMetaClass;
};
