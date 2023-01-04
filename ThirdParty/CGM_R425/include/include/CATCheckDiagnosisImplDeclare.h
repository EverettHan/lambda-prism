  // ---------- CATCheckDiagnosis

  virtual CATTopology *GetCheckedTopo() const;

  virtual void SetCheckedTopo(CATTopology *iCheckedTopo);

  virtual MessageId GetMessageId() const;

  virtual void SetMessageId(MessageId iMsgId);

  virtual const char *GetMessage() const;

  virtual const char *GetSpecificMessage() const;

  virtual void SetSpecificMessage(const char *iMessage);

  virtual CATBoolean MustDump() const;

  virtual void SetMustDump(CATBoolean iMustDump);

  virtual CATBoolean MustThrow() const;

  virtual void SetMustThrow(CATBoolean iMustThrow);

  virtual void *GetAssociatedData() const;

  virtual void SetAssociatedData(void *ipAssociatedData);

  virtual void UpdateCheckDiagnosisType(
    CATCheckDiagnosis::CATCheckDiagnosisTypeId idiagTypeID);

  virtual CATGeometry *GetAssociatedObject() const;

  //virtual void Dump(ostream &iOutput) const;
  virtual void Dump(CATCGMOutput & iOutput) const;

  virtual void        WriteOutput(CATCGMStream &ioStream);
  virtual CATBoolean  ReadReferenceOutput(CATCGMStream & Str, CATListOfInt &oVersionNumbers);
  virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
    CATListOfInt &iVersionNumbers);

  virtual const char *ClassName() const;

  virtual unsigned int GetType() const;

  virtual int IsATypeOf(unsigned int iTypeReference) const;

  virtual CATBoolean IsInvalid() const;

  virtual int operator == (const CATCheckDiagnosis& iDiagnosis) const;

  // By-pass for accessing data members
  CATCGMObject      *GetAssociatedObjectPtr() const;

