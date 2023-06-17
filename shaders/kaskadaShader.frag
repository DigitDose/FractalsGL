#version 440 core
#extension GL_ARB_gpu_shader_fp64 : enable

layout(location = 0) out vec4 color;

uniform dvec2 offset;
uniform double zoomlvl;
uniform double zwiek;
uniform double c1;
uniform double c2;
uniform double p7;
uniform double p8;
uniform double p9;
uniform bool zmien;

void main()
{
    double max_iterations = 10.0 * (zwiek * 2);
    dvec2 c = dvec2(c1, c2);
    dvec2 i;
    dvec2 z_prev = dvec2(0.0, 0.0);  // Wartoœæ poprzednia

    if (zmien)
    {
        c = ((gl_FragCoord.xy * 2.0 - dvec2(1920, 1080)) / dvec2(min(1920, 1080)) * zoomlvl) - offset * 0.5;
        i = c;
    }
    else
    {
        i = ((gl_FragCoord.xy * 2.0 - dvec2(1920, 1080)) / dvec2(min(1920, 1080)) * zoomlvl) - offset * 0.5;
    }

    double iterations = 0.0;

    while (double(length(i)) < 2.0 && iterations < max_iterations)
    {
        z_prev = i;  // Przechowaj poprzedni¹ wartoœæ i
        i = dvec2(i.x * i.x - i.y * i.y, 2.0 * i.x * i.y) + c;
        iterations++;
    }

    if (iterations < max_iterations)
    {
        // Wykorzystanie techniki "Kaskada Marzeñ" do wyznaczenia koloru
        double gradient = iterations / max_iterations;
        float f_gradient = float(gradient);
        color = vec4(
            sin(f_gradient * 3.1416),            // Czerwony
            sin(f_gradient * 2.0 * 3.1416),      // Zielony
            sin(f_gradient * 4.0 * 3.1416),      // Niebieski
            1.0);
    }
    else
    {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
