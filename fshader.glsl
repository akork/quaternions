#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set fragment color from texture
  vec4 a = texture2D(texture, v_texcoord);
  a.a = 0.6;
    gl_FragColor = a;
}
//! [0]

