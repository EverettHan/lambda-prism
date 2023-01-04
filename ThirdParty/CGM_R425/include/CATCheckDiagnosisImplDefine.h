// ---------- CATCheckDiagnosis

CATTopology *CATCGM_DIAG_IMPL_CLASS::GetCheckedTopo() const
{
  return _EmbeddedObject.GetCheckedTopo();
}

void CATCGM_DIAG_IMPL_CLASS::SetCheckedTopo(CATTopology *iCheckedTopo)
{
  _EmbeddedObject.SetCheckedTopo(iCheckedTopo);
}

CATCheckDiagnosis::MessageId CATCGM_DIAG_IMPL_CLASS::GetMessageId() const
{
  return _EmbeddedObject.GetMessageId();
}

void CATCGM_DIAG_IMPL_CLASS::SetMessageId(MessageId       iMessageId)
{
  _EmbeddedObject.SetMessageId(iMessageId);
}

const char *CATCGM_DIAG_IMPL_CLASS::GetMessage() const
{
  return _EmbeddedObject.GetMessage();
}

const char *CATCGM_DIAG_IMPL_CLASS::GetSpecificMessage() const
{
  return _EmbeddedObject.GetSpecificMessage();
}

void CATCGM_DIAG_IMPL_CLASS::SetSpecificMessage(const char *iMessage)
{
  _EmbeddedObject.SetSpecificMessage(iMessage);
}

CATBoolean CATCGM_DIAG_IMPL_CLASS::MustDump() const
{
  return _EmbeddedObject.MustDump();
}

void CATCGM_DIAG_IMPL_CLASS::SetMustDump(CATBoolean iMustDump)
{
  _EmbeddedObject.SetMustDump(iMustDump);
}

CATBoolean CATCGM_DIAG_IMPL_CLASS::MustThrow() const
{
  return _EmbeddedObject.MustThrow();
}

void CATCGM_DIAG_IMPL_CLASS::SetMustThrow(CATBoolean iMustThrow)
{
  _EmbeddedObject.SetMustThrow(iMustThrow);
}

void *CATCGM_DIAG_IMPL_CLASS::GetAssociatedData() const
{
  return _EmbeddedObject.GetAssociatedData();
}

void CATCGM_DIAG_IMPL_CLASS::SetAssociatedData(void *ipAssociatedData)
{
  _EmbeddedObject.SetAssociatedData(ipAssociatedData);
}

void CATCGM_DIAG_IMPL_CLASS::UpdateCheckDiagnosisType(
    CATCheckDiagnosis::CATCheckDiagnosisTypeId idiagTypeID)
{
  _EmbeddedObject.UpdateCheckDiagnosisType(idiagTypeID);
}

CATGeometry *CATCGM_DIAG_IMPL_CLASS::GetAssociatedObject() const
{
  return _EmbeddedObject.GetAssociatedObject();
}

void CATCGM_DIAG_IMPL_CLASS::Dump(CATCGMOutput &iOutput) const
{
  _EmbeddedObject.Dump(iOutput);
}

//void CATCGM_DIAG_IMPL_CLASS::Dump(ostream &iOutput) const
//{
//  _EmbeddedObject.Dump(iOutput);
//}

const char *CATCGM_DIAG_IMPL_CLASS::ClassName() const
{
  return _EmbeddedObject.ClassName();
}

unsigned int CATCGM_DIAG_IMPL_CLASS::GetType() const
{
  return _EmbeddedObject.GetType();
}

int CATCGM_DIAG_IMPL_CLASS::IsATypeOf(unsigned int iTypeReference) const
{
  return _EmbeddedObject.IsATypeOf(iTypeReference);
}

CATBoolean CATCGM_DIAG_IMPL_CLASS::IsInvalid() const
{
  return _EmbeddedObject.IsInvalid();
}

void CATCGM_DIAG_IMPL_CLASS::WriteOutput(CATCGMStream &ioStream)
{
  _EmbeddedObject.WriteOutput(ioStream);
}

CATBoolean  CATCGM_DIAG_IMPL_CLASS::ReadReferenceOutput(CATCGMStream & Str, CATListOfInt &oVersionNumbers)
{
  return _EmbeddedObject.ReadReferenceOutput(Str, oVersionNumbers);
}

CATBoolean  CATCGM_DIAG_IMPL_CLASS::ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
                                                   CATListOfInt &iVersionNumbers)
{
  return _EmbeddedObject.ValidateOutput(iRefDiagnosis, iConfig, iVersionNumbers);
}

int CATCGM_DIAG_IMPL_CLASS::operator == (const CATCheckDiagnosis& iDiagnosis) const
{
  return _EmbeddedObject.operator ==(iDiagnosis);
}

// By-pass for accessing data members
CATCGMObject *CATCGM_DIAG_IMPL_CLASS::GetAssociatedObjectPtr() const
{
  return _EmbeddedObject.GetAssociatedObjectPtr();
}
