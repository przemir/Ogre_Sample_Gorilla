#version ogre_glsl_ver_330

vulkan_layout( ogre_s0 ) uniform sampler2D atlas;

vulkan_layout( location = 0 ) in vec4 oUv;
vulkan_layout( location = 1 ) in vec4 oColor;

vulkan_layout( location = 0 )
out vec4 out_Color;

void main()
{
    out_Color = texture(atlas, oUv.xy) * oColor;
}

