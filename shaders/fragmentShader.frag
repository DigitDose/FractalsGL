#version 460 core


layout(location = 0) out vec4 fragColor;

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
    double max_iterations = 10.0 * (zwiek*2);
    dvec2 c = dvec2(c1, c2);
    dvec2 i;
    dvec2 z_prev = dvec2(0.0, 0.0);  // Warto

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
        z_prev = i;  // Przechowaj poprzed
        i = dvec2(i.x * i.x - i.y * i.y, 2.0 * i.x * i.y) + c;
        iterations++;
    }

    if (iterations < max_iterations)
    {
        // Zastosowanie techniki  do wyznaczenia koloru
        double gradient = iterations / max_iterations;
        fragColor = vec4(
            gradient,  // Czerwony
            gradient * 0.5,  // Zielony
            gradient * 0.1,  // Niebieski
            1.0);
         float normalized_iterations = float(iterations) / float(max_iterations);
         float dragon_speed = length(float(i*p7) - float(z_prev*p8));
	/*
        //  "dragon_speed" do wyznaczenia koloru
        fragColor = vec4(
            0.5 + (0.5 * sin(30.0 + dragon_speed * 3.1416)) *float(p7),
            0.5 + (0.5 * cos(0.5 + dragon_speed * 2.0 * 3.1416))*float(p8),
            0.5 + (0.5 * tan(1.0 + dragon_speed * 4.0 * 3.1416))*float(p9),
            1.0);
	*/
   }
    else
    {
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
