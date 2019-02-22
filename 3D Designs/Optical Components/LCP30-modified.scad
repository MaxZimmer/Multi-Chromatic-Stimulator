  // // // // // // // // // // // // // // // // // // // // // // // //
 // // // // // // // // // //  LCP30// // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // // //

Smoothness = 360; // A value of 360 is recommended for a smooth print
tol = 0.1; // Tolerance value, set by default to 0.1 for Ultimaker2 printer
tol2 = 0.15; // Use for translational slots

sep = 75; // Separtion between objects (75 by default for proper display)
sep_plat = 00; // Separation between the objects of the Platform() module
Walls = 2; //Wall thickness (applied only to certain modules
rod_pos1 = 30/2; // Rod position for 30mm cage system
rod_pos2 = 60/2; // Rod position for 60mm cage system
x_screw_pos1 = 22.75/2; // Screw position for rods on 30mm cage system
x_screw_pos2 = 53/2; // Screw position for rods on 60mm cage system
r_rod = 6.1/2 + tol/2; // Rod radius 0.25 inch
S4 = 2.85/2; // ThorLabs small holding screws 0.05 inch
M4 = 3.85/2 + tol/2; //M4 screw
M4nut = 8/2; //M4 screw
width_M4 = 6.9; //M4 screw
h_M4nut = 3.1; //M4 screw
M4_screw_head =  2.9;//M4 screw head
M6 = 5.9/2 + tol/2; //M4 screw
r_lens_05_inch = 12.7/2 + 3.2*tol; //ThorLabs 0.5 inch diameter lens
r_lens_1_inch = 25.4/2 + 3.2*tol; //ThorLabs 1 inch diameter lens
r_lens_12_inch = 30/2 + 3.2*tol; //ThorLabs 1.2 inch diameter lens 
r_lens_2_inch = 50.8/2 + 3.2*tol; //ThorLabs 2 inch diameter lens
r_lens_3_inch = 76.2/2 + 3.2*tol; //ThorLabs 3 inch diameter lens
rotation = 10;
module small_rod_cage(){
    for(a = [-rotation:0.5:rotation]){
    rotate([0,0,a]){
    translate([rod_pos1,rod_pos1,0])cylinder(r=r_rod, h=200, $fn=Smoothness);//int rod hole
    translate([rod_pos1,-rod_pos1,0])cylinder(r=r_rod, h=200, $fn=Smoothness);//int rod hole
    translate([-rod_pos1,-rod_pos1,0])cylinder(r=r_rod, h=200, $fn=Smoothness);//int rod hole
    translate([-rod_pos1,rod_pos1,0])cylinder(r=r_rod, h=200, $fn=Smoothness);//int rod hole
} }}//30mm cage mounting system
X_LCP30 = 73.7; //outer cube length
x_LCP30 = 40.7+5; //inner cube length
y_LCP30 = 40.6+5;
z_LCP30 = 12.70; //module thickness
y_Groove_LCP30 = 12.9;
x_arm_LCP30 = 16.5; //arm width
y_arm_LCP30 = 14; //arm length
x_ext_LCP30 = 96.3; //module diagonal length
pos_z_Screw_LCP30 = 7.1;
pos_x_screw_LCP30 = 67.3/2;
pos_y_screw_LCP30 = 26.7/2;
pos_x2_screw_LCP30 = 30/2;
pos_z_screw_LCP30 = 6.4;


    difference(){
        translate([-X_LCP30/2,-y_LCP30/2,0])cube([X_LCP30,y_LCP30,z_LCP30]);
        
        difference(){
            translate([-X_LCP30/2,-y_Groove_LCP30/2,0])cube([X_LCP30,y_Groove_LCP30,z_LCP30]);
            translate([-x_LCP30/2,-y_LCP30/2,0])cube([x_LCP30,y_LCP30,z_LCP30]);
        }
        
        Screw_LCP30();
        cylinder(r=r_lens_1_inch+4,h=z_LCP30,$fn=Smoothness);
        
        
        //customisation
        translate([-X_LCP30/2,-y_LCP30/2,0])cube([X_LCP30/2-x_LCP30/2+2*tol,y_LCP30,z_LCP30]);
    }
    //customization
    difference(){
        translate([-X_LCP30/2,-y_Groove_LCP30/2+2*tol,0])cube([X_LCP30/2-x_LCP30/2+2*tol,y_Groove_LCP30-4*tol,z_LCP30]);
        
        Screw_LCP30();
        translate([-pos_x_screw_LCP30,0,0])cylinder(r=S4,h=z_LCP30,$fn=Smoothness);
    }


module Screw_LCP30(){
    small_rod_cage();
    
    translate([pos_x_screw_LCP30,pos_y_screw_LCP30,0])cylinder(r=S4,h=z_LCP30,$fn=Smoothness);
    translate([pos_x_screw_LCP30,-pos_y_screw_LCP30,0])cylinder(r=S4,h=z_LCP30,$fn=Smoothness);

    
    translate([rod_pos2,-y_LCP30/2,pos_z_Screw_LCP30])rotate([-90,0,0])cylinder(r=r_rod,h=y_LCP30,$fn=Smoothness);
    translate([-rod_pos2,-y_LCP30/2,pos_z_Screw_LCP30])rotate([-90,0,0])cylinder(r=r_rod,h=y_LCP30,$fn=Smoothness);
    
    translate([pos_x2_screw_LCP30,-y_LCP30/2,pos_z_screw_LCP30])rotate([-90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([pos_x2_screw_LCP30-4,-y_LCP30/2,pos_z_screw_LCP30])rotate([-90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([pos_x2_screw_LCP30+4,-y_LCP30/2,pos_z_screw_LCP30])rotate([-90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    
    translate([-pos_x2_screw_LCP30,-y_LCP30/2,pos_z_screw_LCP30])rotate([-90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([-pos_x2_screw_LCP30-4,-y_LCP30/2,pos_z_screw_LCP30])rotate([-90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([-pos_x2_screw_LCP30+4,-y_LCP30/2,pos_z_screw_LCP30])rotate([-90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    
    translate([pos_x2_screw_LCP30,y_LCP30/2,pos_z_screw_LCP30])rotate([90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([pos_x2_screw_LCP30-4,y_LCP30/2,pos_z_screw_LCP30])rotate([90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([pos_x2_screw_LCP30+4,y_LCP30/2,pos_z_screw_LCP30])rotate([90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    
    translate([-pos_x2_screw_LCP30,y_LCP30/2,pos_z_screw_LCP30])rotate([90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([-pos_x2_screw_LCP30-4,y_LCP30/2,pos_z_screw_LCP30])rotate([90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
    translate([-pos_x2_screw_LCP30+4,y_LCP30/2,pos_z_screw_LCP30])rotate([90,0,0])cylinder(r=S4,h=y_LCP30/2-y_Groove_LCP30+Walls,$fn=Smoothness);
}