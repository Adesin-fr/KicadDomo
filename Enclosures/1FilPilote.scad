// 48 x 49.5 x 20
// Ergots de maintiens au centre sur le coté 49.5
// 2mm sous PCB
// PCB = 2mm
// 15 mm sur PCB

$DimX = 50;
$DimY = 49;
$DimZ = 17;
$WallThickness = 2;

$Box=0;
$Lid=1;


if ($Box==1){
    
    difference(){
    cube([$DimX + $WallThickness *2 ,
          $DimY + $WallThickness *2 ,
          $DimZ + $WallThickness *2 ]);
          
    translate([$WallThickness, $WallThickness, $WallThickness ]) cube([$DimX  ,
          $DimY ,
          $DimZ + 10]);

    // Rebord bas de boitier

    // Percage trous cables :
    translate([$WallThickness+ 4.5,5,$WallThickness+ 7.5]) 
           rotate([90,0,0])    cylinder (r=2, h=10, $fn=20);
    translate([$WallThickness+ 9.5,5,$WallThickness+ 7.5]) 
            rotate([90,0,0])    cylinder (r=2, h=10, $fn=20);
    translate([$WallThickness+ 14.5,5,$WallThickness+ 7.5]) 
            rotate([90,0,0])    cylinder (r=2, h=10, $fn=20);

    // Ventilations :  :
    translate([-5, 45, 10]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 40, 10]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 35, 10]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 30, 10]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);

    translate([-5, 42, 13]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 37, 13]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 32, 13]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 27, 13]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);

    translate([-5, 45, 16]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 40, 16]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 35, 16]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);
    translate([-5, 30, 16]) 
           rotate([0,90,0])    cylinder (r=1.5, h=10, $fn=20);

    };

    // Support PCB dans les angles, epaisseur 2mm
    translate([$WallThickness,$WallThickness, $WallThickness]) cube([2,2,2]);
    translate([$DimX, $WallThickness, $WallThickness]) cube([2,2,2]);
    translate([$WallThickness, $DimY, $WallThickness]) cube([2,2,2]);
    translate([$DimX, $DimY, $WallThickness]) cube([2,2,2]);
}

if($Lid==1){

    // Couvercle : 
    difference(){
        translate([-$WallThickness, -$WallThickness, $DimZ + $WallThickness*2 ]) 
            cube([$DimX + $WallThickness *4 ,
              $DimY + $WallThickness *4 ,
              $WallThickness *2 ]);

        translate ([-0.25, -0.25, $DimZ + $WallThickness]) 
            cube([$DimX +0.5 + $WallThickness *2 ,
                  $DimY +0.5 + $WallThickness *2 ,
                  $WallThickness *2 ]);

        // Percage trous cables :
        translate([$WallThickness+ 4.5 , 6.5 + $WallThickness , $DimZ]) 
               rotate([0,0,90])    cylinder (r=2, h=10, $fn=20);
        translate([$WallThickness+ 9.5 , 6.5 + $WallThickness , $DimZ]) 
               rotate([0,0,90])    cylinder (r=2, h=10, $fn=20);
        translate([$WallThickness+ 14.5 , 6.5 + $WallThickness , $DimZ]) 
               rotate([0,0,90])    cylinder (r=2, h=10, $fn=20);


    };

}
