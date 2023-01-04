layout(location = 0) rayPayloadInEXT Payload_t g_Payload;

void main()
{
  g_Payload.isHit = true;
  g_Payload.color.x = gl_HitTEXT;
}
