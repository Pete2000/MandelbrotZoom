#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<gmp.h>

typedef struct{
    long double R,X;
} complex;

#define N 800
#define M 800
#define MAX_ITERATION 4000
#define MAX_ZOOM 500 //25 frame per secondo 20 secondi
long double segment(long double t,long double p, long double q);
int color(int k,double freq, int phase);
void mandelbrot(long double Cx, long double Cy, long double zoom,int t);

int main(){

     mpz_t x,y,result;

    //printf("%lf",pow(2,-1));

    //double Cx=-1.740062382579339905220844167065825638296641720436171866879862418461182919644153056054840718339483225743450008259172138785492983677893366503417299549623738838303346465461290768441055486136870719850559269507357211790243666940134793753068611574745943820712885258222629105433648695946003865;
    //double Cy=0.0281753397792110489924115211443195096875390767429906085704013095958801743240920186385400814658560553615695084486774077000669037710191665338060418999324320867147028768983704831316527873719459264592084600433150333362859318102017032958074799966721030307082150171994798478089798638258639934;
    //double Cx=-0.745428;
    //double Cy=0.113009;
    //double Cx=-1.25066;
    //double Cy=0.02012;
    //double Cx=-0.235125;
    //double Cy=0.827215;
/*
    double Cx=0.3750001200618655;
    double Cy=-0.2166393884377127;
*/
    long double Cx=0.360240443437614363236125244449545308482607807958585750488375814740195346059218100311752936722773426396233731729724987737320035372683285317664532401218521579554288661726564324134702299962817029213329980895208036363104546639698106204384566555001322985619004717862781192694046362748742863016467354574422779443226982622356594130430232458472420816652623492974891730419252651127672782407292315574480207005828774566475024380960675386215814315654794021855269375824443853463117354448779647099224311848192893972572398662626725254769950976527431277402440752868498588785436705371093442460696090720654908973712759963732914849861213100695402602927267843779747314419332179148608587129105289166676461292845685734536033692577618496925170576714796693411776794742904333484665301628662532967079174729170714156810530598764525260869731233845987202037712637770582084286587072766838497865108477149114659838883818795374195150936369987302574377608649625020864292915913378927790344097552591919409137354459097560040374880346637533711271919419723135538377394364882968994646845930838049998854075817859391340445151448381853615103761584177161812057928;
    long double Cy=-0.6413130610648031748603750151793020665794949522823052595561775430644485741727536902556370230689681162370740565537072149790106973211105273740851993394803287437606238596262287731075999483940467161288840614581091294325709988992269165007394305732683208318834672366947550710920088501655704252385244481168836426277052232593412981472237968353661477793530336607247738951625817755401065045362273039788332245567345061665756708689359294516668271440525273653083717877701237756144214394870245598590883973716531691124286669552803640414068523325276808909040317617092683826521501539932397262012011082098721944643118695001226048977430038509470101715555439047884752058334804891389685530946112621573416582482926221804767466258346014417934356149837352092608891639072745930639364693513216719114523328990690069588676087923656657656023794484324797546024248328156586471662631008741349069961493817600100133439721557969263221185095951241491408756751582471307537382827924073746760884081704887902040036056611401378785952452105099242499241003208013460878442953408648178692353788153787229940221611731034405203519945313911627314900851851072122990492499999999999999999991;

    for(int t=0;t<MAX_ZOOM;t++){
        mandelbrot(Cx,Cy,segment((double)t/MAX_ZOOM,-5,58),t);
        printf("zoom:%Lf\n",segment((double)t/MAX_ZOOM,-5,58));
    }
    system("ffmpeg -start_number 0 -i ./output/pgimg%d.ppm -vcodec mpeg4 -crf 0 -b 40M ./output/test.mp4 -y");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long double segment(long double t,long double p,long double q){
    return (double) (1.-t)*p+(t*q);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int color(int k,double freq, int phase){
    return 255*pow((cos(sqrt(k)*freq + phase)),2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mandelbrot(long double Cx, long double Cy, long double zoom,int t){
    complex Z;
    Z.R=0;
    Z.X=0;

    complex old_Z;
    old_Z.R=0;
    old_Z.X=0;
    
    complex C;
    C.R=0;
    C.X=0;
    long double sizeXY= pow(2,-zoom) * 2.;
    long double minReal= (Cx-sizeXY)/2.;
    long double maxReal= (Cx+sizeXY)/2.;
    long double minCompl= (Cy- sizeXY)/2.;
    long double maxCompl= (Cy+ sizeXY)/2.;
    char filename[50];
    snprintf(filename,50,"./output/pgimg%d.ppm",t);
    printf("%s\n",filename);
    FILE* pgmimg; 
    pgmimg = fopen(filename, "wb"); 
    // Writing Magic Number to the File 
    fprintf(pgmimg, "P3\n");  
    // Scrittura della larghezza e altezza dell'immagine
    fprintf(pgmimg, "%d %d\n", M, N);  
    // Scrittura del massimo valore di grigio 
    fprintf(pgmimg, "255\n");  
    
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++) { 
            // Scrittura della matrice coi valori di grigio
            
            int k=0; 
            Z.R=0;
            Z.X=0;
            do{
                old_Z.R=Z.R;
                old_Z.X=Z.X;
                Z.R=(long double)(old_Z.R*old_Z.R)-(old_Z.X*old_Z.X)+segment((long double)j/M,minReal,maxReal);//Intervallo di larghezza
                Z.X=(long double)(2.*old_Z.R*old_Z.X)+segment((long double)i/N,maxCompl,minCompl);//Intervallo di altezza
                k++;
            }while(k<MAX_ITERATION && Z.R<2);
            if(Z.R<2){
                fprintf(pgmimg, "%d %d %d ",0,0,0);
            }else{
                fprintf(pgmimg,"%d %d %d ",color(k,1,0),color(k,1,6),color(k,1,12));
                //phases: 0 120 240 or 0 6 12
            }
                
        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg); 

}
