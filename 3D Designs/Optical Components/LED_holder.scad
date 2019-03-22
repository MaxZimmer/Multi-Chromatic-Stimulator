tol = 0.1;
Smoothness = 360;
Wall = 2;

r_lens_1_inch = 25.8/2; //ThorLabs 1 inch diameter lens
r_inner_ring = 22.8/2;

h_LED_Holder = 3;
h_clip = 1;
r_LED = 6.35/2;
r_Clip = 7.5/2+tol;
h_ring = 2;


difference(){
    cylinder(r=r_lens_1_inch-tol, h=h_LED_Holder, $fn=Smoothness);
    
    cylinder(r=r_LED, h=h_LED_Holder, $fn=Smoothness);
    translate([0,0,h_clip])cylinder(r=r_Clip,h=h_LED_Holder,$fn=Smoothness);
    
    translate([0,0,h_ring])difference(){
        cylinder(r=r_lens_1_inch, h=h_LED_Holder, $fn=Smoothness);
        cylinder(r=r_inner_ring-tol, h=h_LED_Holder, $fn=Smoothness);
    }
}