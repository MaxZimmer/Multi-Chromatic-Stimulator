//*************************************//
//
//
//
//
//all units in mm.
//CC BY 4.0
//AM Chagas 20180516
//*************************************//

//variables
holed=6;
tol=0.15;
dist2hol = 42.42;//47.15-holed/2;
basethick=20;

dichx=25.4;
dichy=1;
dichz=36.2;
framey=3;

module mount_poles(){
//pole1
translate([dist2hol/2,0,0]){
cylinder(d=holed-tol,h=basethick,center=true,$fn=360);
}//translate
//pole2
translate([-dist2hol/2,0,0]){
cylinder(d=holed-tol,h=basethick,center=true,$fn=360);
}//translate
}//module

module main_holder(){
//dichr place

difference(){
cube([dist2hol+holed-tol,holed-tol+5,40],center=true);

translate([0,0,8]){
    cube([dichz+1,holed-tol+5,40],center=true);

 }//translate
translate([0,0,1.1]){
    rotate([0,90,0]){
        dich_frame1(dx=dichx+5+2*tol,dy=dichy+2+2*tol,dz=dichz+5+2*tol);
    }//rotate
}//translate
translate([0,0,8]){
    rotate([0,90,0]){
        dich_frame1(dx=dichx+5+2*tol,dy=dichy+2+2*tol,dz=dichz+5+2*tol);
    }//rotate
}//translate
}//difference
translate([0,0,-22]){
    cube([dist2hol+holed-tol,holed-tol+5,5],center=true);
}//translate
}//module

//translate([0,0,(basethick+15)/2]){
//main_holder();
//}

module dich_frame1(dx=dichx+5,dy=dichy+2,dz=dichz+5){
difference(){    
cube([dx,dy,dz],center=true);
translate([0,0.5,0]){
    cube([dx-5+tol,dy-0.9+tol,dz-5+tol],center=true);
    }//translate

cube([dx-7.5,dy+1,dz-7.5],center=true);


//translate([(dx-5)/2,1,0]){
//cube([10,dy-0,5],center=true);
//}//translate

translate([-(dx-5)/2,1,0]){
cube([10,dy-1,5],center=true);
}//translate

}//difference
}//module



//union(){

//main_holder();
/*translate([0,5,]){
rotate([0,90,0]){
dich_frame1();
}
}
*/
//translate([0,0,-dichz/2-5]){
//mount_poles();

//}
//}

dich_frame1();