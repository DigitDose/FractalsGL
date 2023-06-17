#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable

layout(location = 0) out vec4 color;

uniform vec2 offset;
uniform highp float zoomlvl;
uniform highp float zwiek;

void main()
{
    highp float max_iterations = 100.0 * zwiek;

    vec2 c = ((gl_FragCoord.xy * 2.0 - vec2(1920, 1080)) / vec2(min(1920, 1080)) * zoomlvl) - offset * 0.1;
    vec2 z = vec2(0.0);
    highp float iterations = 0.0;

    vec2 z_prev = z;
    while ((length(z)) < 2.0 && iterations < max_iterations)
    {
        z_prev = z;
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        iterations++;
    }

    if (iterations < max_iterations)
    {
        highp float normalized_iterations = iterations / max_iterations;
        highp float dragon_speed = length(z*z - z_prev);

        // U¿ycie "dragon_speed" do wyznaczenia koloru
        color = vec4(
            0.99 + 0.05 * cos(3.0 + dragon_speed * 3.1416),
            0.99 + 0.05 * cos(0.5 + dragon_speed * 2.0 * 3.1416),
            0.99 + 0.05 * cos(1.0 + dragon_speed * 4.0 * 3.1416),
            1.0);
    }
    else
    {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
