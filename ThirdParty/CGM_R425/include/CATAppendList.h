#define APPENDLIST(TargetList, SourceList) { \
  int ielement = 0; \
  for(ielement = 1; ielement <= SourceList.Size(); ielement++) \
{ \
TargetList.Append(SourceList[ielement]); \
} \
}

#define APPENDCONVLIST(TargetList, SourceList, ConversionFunction) { \
  int ielement = 0; \
  for(ielement = 1; ielement <= SourceList.Size(); ielement++) \
{ \
TargetList.Append(ConversionFunction(SourceList[ielement])); \
} \
}

#define APPENDLISTNODUP(TargetList, SourceList) { \
  int ielement = 0; \
  for(ielement = 1; ielement <= SourceList.Size(); ielement++) \
{ \
if (!TargetList.Locate(SourceList[ielement])) TargetList.Append(SourceList[ielement]); \
} \
}

#define REMOVELIST(TargetList, SourceList) { \
  int ielement = 0; \
  for(ielement = 1; ielement <= SourceList.Size(); ielement++) \
{ \
TargetList.RemoveValue(SourceList[ielement]); \
} \
}
