layout(location = 0) rayPayloadInEXT Payload_t g_Payload;

void main()
{
  g_Payload.hitIndex = gl_InstanceID ; //gl_InstanceCustomIndexNV;
}

