CATCGM_ITF_IMPL_CLASS::CATCGM_ITF_IMPL_CLASS(CATCGM_ITF_CONCRETE_CLASS *ipContext, CATTopOperator* ipOperator)
{
  _Extensible = ipContext;
  if (_Extensible != NULL)
    _Extensible->SetInterface(this);
  this->SetOperator(ipOperator);
}

CATCGM_ITF_IMPL_CLASS::~CATCGM_ITF_IMPL_CLASS()
{
}

