#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///////////////
typedef struct{
int estado;
int aprobado;
int dni;
char nombre[10];
char apellido[20];
char fechaNac[12];
char sexo;
char localidad[20];
char calle[20];
int num;
int piso;
int dpto;
int cp;
char establecimiento[20];
int rama;
int finalizacion;
float notauni;
float notamat;
}ingresante;
////////////////
typedef struct{
int codmat;
int desaprobado;
int aprobadomat;
float parcial1;
float recuperatorio1;
float parcial2;
float recuperatorio2;
float parcial3;
float recuperatorio3;
float final1;
}notas;
////////////////
void ver_menu(){

printf("***********Bienvenidos al sistema Guarani************\n");
printf(" *************************************************** \n");
printf("  *************************************************  \n");
printf("1-Actualizacion de Archivos Maestros\n");
printf("2-Carga de Alumnos\n");
printf("3-Carga de examenes de Ingreso\n");
printf("4-Carga de notas de materias\n");
printf("5-Consultas de Ingreso\n");
printf("6-Consultas sobre las materias de primer año\n");
printf("7-Nota de corte\n");
printf("8-Salir\n");
}
////////////////
int corte;
//////////////////////
void actualizacion(){
int opcion2;

printf("1-Altas\n");
printf("2-Bajas\n");
printf("3-Modificaciones\n");
printf("4-Salir\n");
scanf("%d",&opcion2);
while(opcion2!=5){
    switch(opcion2){
    case 1:altas();
    break;
    case 2:bajas();
    break;
    case 3:modi();
    break;
    case 4:return 0;
    break;
    }
printf("1-Altas\n");
printf("2-Bajas\n");
printf("3-Modificaciones\n");
printf("4-Salir\n");
scanf("%d",&opcion2);
}
}
//////////////////////
void carga_alumnos(){
int sali;
ingresante i;
FILE*fd;
fd=fopen("ingreso.dat","a");
if(fd==NULL)return -1;
do{
    fflush(stdin);
    printf("Ingrese DNI:\n");
    scanf("%d",&i.dni);
    fflush(stdin);
    printf("Ingrese nombre: \n");
    scanf("%s",i.nombre);
    fflush(stdin);
    printf("Ingrese apellido: \n");
    scanf("%s",i.apellido);
    fflush(stdin);
    printf("Ingrese fecha de nacimiento: (MM/DD/AAAA)\n");
    scanf("%s",&i.fechaNac);
    fflush(stdin);
    printf("Ingrese sexo: m(masculino) f(femenino)\n");
    scanf("%c",&i.sexo);
    fflush(stdin);
    printf("Ingrese localidad: \n");
    scanf("%s",i.localidad);
    fflush(stdin);
    printf("Ingrese calle: \n");
    scanf("%s",i.calle);
    fflush(stdin);
    printf("Ingrese numero: \n");
    scanf("%d",&i.num);
    fflush(stdin);
    printf("Ingrese piso: \n");
    scanf("%d",&i.piso);
    fflush(stdin);
    printf("Ingrese departamento: \n");
    scanf("%d",&i.dpto);
    fflush(stdin);
    printf("Ingrese codigo postal: \n");
    scanf("%d",&i.cp);
    fflush(stdin);
    printf("Ingrese establecimiento: \n");
    scanf("%s",i.establecimiento);
    fflush(stdin);
    printf("Ingrese rama: 1(tecnico) 2(ciencias sociales) 3(comercial)\n");
    scanf("%d",&i.rama);
    fflush(stdin);
    printf("Ingrese anio de finalizacion de estudios: \n");
    scanf("%d",&i.finalizacion);
    fflush(stdin);
    i.notamat=-1;
    i.notauni=-1;
    i.estado=1;
    i.aprobado=0;
    printf("Seguir cargando alumnos? 1(si) otro no\n");
    scanf("%d",&sali);
    fprintf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %.2f %.2f %d %d\n",i.dni,i.nombre,i.apellido,i.fechaNac,i.sexo,i.localidad,i.calle,i.num,i.piso,i.dpto,i.cp,i.establecimiento,i.rama,i.finalizacion,i.notamat,i.notauni,i.estado,i.aprobado);
    }while(sali==1);
fclose(fd);
}
//////////////////////
void carga_examingre(){
int auxdni;
float prom;
ingresante c;
FILE*fd;
FILE*fdaux;
fd=fopen("ingreso.dat","r");
fdaux=fopen("ingresoaux.dat","a");
if(fd==NULL)return -1;
printf("Ingrese DNI:\n");
scanf("%d",&auxdni);
while(!feof(fd)){
     fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&c.dni,&c.nombre,&c.apellido,&c.fechaNac,&c.sexo,&c.localidad,&c.calle,&c.num,&c.piso,&c.dpto,&c.cp,&c.establecimiento,&c.rama,&c.finalizacion,&c.notamat,&c.notauni,&c.estado,&c.aprobado);
     if(auxdni==c.dni && c.estado==1){
        if(c.notamat==-1 && c.notauni==-1){
        fflush(stdin);
        printf("Ingrese nota de materia especifica: \n");
        scanf("%f",&c.notamat);
        fflush(stdin);
        printf("Ingrese nota de universidad en la argentina: \n");
        scanf("%f",&c.notauni);
        fflush(stdin);
        }
        if(c.notamat>=11 || c.notauni>=11){
            printf("Error\n\n");
            c.notamat=-1;
            c.notauni=-1;
        }
        if((c.notamat>=4 && c.notamat<=10) && (c.notauni>=4 && c.notauni<=10)){
            prom=(c.notamat+c.notauni)/2;
        }
        if(prom>=corte){
            c.aprobado=1;
        }
        }
    if(auxdni==c.dni && c.estado==0){
        printf("Ingresante dado de baja no se puede ingresar nota\n\n");
    }
    fprintf(fdaux,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %.2f %.2f %d %d\n",c.dni,c.nombre,c.apellido,c.fechaNac,c.sexo,c.localidad,c.calle,c.num,c.piso,c.dpto,c.cp,c.establecimiento,c.rama,c.finalizacion,c.notamat,c.notauni,c.estado,c.aprobado);
}
fclose(fd);
fclose(fdaux);
remove("ingreso.dat");
rename("ingresoaux.dat","ingreso.dat");
}
////////////////////////
void carga_notmat(){
ingresante l;
notas al1;
notas al2;
notas al3;
notas al4;
int auxdni;
int auxcod;
int parcialesAprobados = 0;
/////////////////////////
al1.aprobadomat = -1;
al1.desaprobado = -1;
al1.final1 = -1;
al1.parcial1 = -1;
al1.parcial2 = -1;
al1.parcial3 = -1;
al1.recuperatorio1 = -1;
al1.recuperatorio2 = -1;
al1.recuperatorio3 = -1;
/////////////////////////
al2.aprobadomat = -1;
al2.desaprobado = -1;
al2.final1 = -1;
al2.parcial1 = -1;
al2.parcial2 = -1;
al2.parcial3 = -1;
al2.recuperatorio1 = -1;
al2.recuperatorio2 = -1;
al2.recuperatorio3 = -1;
/////////////////////////
al3.aprobadomat = -1;
al3.desaprobado = -1;
al3.final1 = -1;
al3.parcial1 = -1;
al3.parcial2 = -1;
al3.parcial3 = -1;
al3.recuperatorio1 = -1;
al3.recuperatorio2 = -1;
al3.recuperatorio3 = -1;
/////////////////////////
al4.aprobadomat = -1;
al4.desaprobado = -1;
al4.final1 = -1;
al4.parcial1 = -1;
al4.parcial2 = -1;
al4.parcial3 = -1;
al4.recuperatorio1 = -1;
al4.recuperatorio2 = -1;
al4.recuperatorio3 = -1;
/////////////////////////
FILE*fd;
FILE*lista1;
FILE*lista2;
FILE*lista3;
FILE*lista4;
fd=fopen("ingreso.dat","rb");
lista1=fopen("notaOrg.dat","ab");
lista2=fopen("notaProg.dat","ab");
lista3=fopen("notaAlg.dat","ab");
lista4=fopen("notaMat.dat","ab");
if(fd==NULL && lista1==NULL && lista2==NULL && lista3==NULL && lista4==NULL)return -1;
printf("Ingrese Codigo de Materia:0(Organizacion) 1(Programacion) 2(Algoritmo) 3(Matematica I)\n");
scanf("%d",&auxcod);
printf("Ingrese DNI:\n");
scanf("%d",&auxdni);
while(!feof(fd)){
     fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&l.dni,&l.nombre,&l.apellido,&l.fechaNac,&l.sexo,&l.localidad,&l.calle,&l.num,&l.piso,&l.dpto,&l.cp,&l.establecimiento,&l.rama,&l.finalizacion,&l.notamat,&l.notauni,&l.estado,&l.aprobado);
     if(auxdni==l.dni && l.aprobado==1 && l.estado==1 && auxcod==0){
        printf("**********Organizacion de Computadoras***********\n");
        al1.aprobadomat=-1;
        al1.desaprobado=-1;
        printf("Ingrese nota del primer parcial:\n");
        scanf("%f",&al1.parcial1);
        fflush(stdin);
        al1.recuperatorio1=-1;
        fflush(stdin);
        if(al1.parcial1>=0 && al1.parcial1<=3){ // SI REPROBO ENTONCES PREGUNTA RECUPERATORIO
            printf("Ingrese nota de recuperatorio:\n");
            scanf("%f",&al1.recuperatorio1);
            fflush(stdin);
            if(al1.recuperatorio1>=0 && al1.recuperatorio1<=3){ //DESAPROBO MATERIA
                printf("Desaprobo la materia\n");
                al1.desaprobado=1;
                fflush(stdin);
            }else{
               //APROBO MATERIA
               parcialesAprobados++;
            }
        }else{
            //APROBO MATERIA SIN IR A RECUPERATORIO
            parcialesAprobados++;
        }

        if(parcialesAprobados == 1){ //SI APROBO EL PRIMER PARCIAL, PREGUNTA SOBRE EL SEGUNDO
            printf("Ingrese nota del segundo parcial:\n");
            scanf("%f",&al1.parcial2);
            fflush(stdin);
            al1.recuperatorio2=-1;
            fflush(stdin);
            if(al1.parcial2>=0 && al1.parcial2<=3){ // SI DESAPROBO EL SEGUNDO PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al1.recuperatorio2);
                fflush(stdin);
                if(al1.recuperatorio2>=0 && al1.recuperatorio2<=3){ //DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al1.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO EL SEGUNDO PARCIAL SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if(parcialesAprobados == 2){ //SI APROBO EL PRIMER Y EL SEGUNDO PARCIAL
            printf("Ingrese nota del tercer parcial:\n");
            scanf("%f",&al1.parcial3);
            fflush(stdin);
            al1.recuperatorio3=-1;
            fflush(stdin);
            if(al1.parcial3>=0 && al1.parcial3<=3){ //SI DESAPROBO EL TERCER PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al1.recuperatorio3);
                fflush(stdin);
                if(al1.recuperatorio3>=0 && al1.recuperatorio3<=3){ //SI DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al1.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if((al1.parcial3>=4 && al1.parcial3<=10)||(al1.recuperatorio3>=4 && al1.recuperatorio3<=10)){
            printf("Aprobo cursada\n");
            al1.desaprobado=0;
            fflush(stdin);
        }

        if(al1.parcial1>=7 && al1.parcial2>=7 && al1.parcial3>=7){
                al1.final1=(al1.parcial1+al1.parcial2+al1.parcial3)/3;
                al1.aprobadomat=1;
                printf("Alumno promocionado\n");
        }
        if(al1.desaprobado==0 && al1.aprobadomat==-1){
                printf("Ingrese nota de final:\n");
                scanf("%f",&al1.final1);
                if(al1.final1>=4 && al1.final1<=10){
                al1.aprobadomat=1;
                }
                if(al1.final1>=0 && al1.final1<=3){
                al1.aprobadomat=0;
                }
            }
            al1.codmat=0;
            fprintf(lista1,"%d %s %s %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d %d %d\n",l.dni,l.nombre,l.apellido,l.rama,al1.parcial1,al1.recuperatorio1,al1.parcial2,al1.recuperatorio2,al1.parcial3,al1.recuperatorio3,al1.final1,al1.desaprobado,al1.aprobadomat,al1.codmat);
        }
        if(auxdni==l.dni && l.aprobado==1 && l.estado==1 && auxcod==1){
        printf("**********Programacion de Computadoras***********\n");
        al2.aprobadomat=-1;
        al2.desaprobado=-1;
        printf("Ingrese nota del primer parcial:\n");
        scanf("%f",&al2.parcial1);
        fflush(stdin);
        al2.recuperatorio1=-1;
        fflush(stdin);
        if(al2.parcial1>=0 && al2.parcial1<=3){ // SI REPROBO ENTONCES PREGUNTA RECUPERATORIO
            printf("Ingrese nota de recuperatorio:\n");
            scanf("%f",&al2.recuperatorio1);
            fflush(stdin);
            if(al2.recuperatorio1>=0 && al2.recuperatorio1<=3){ //DESAPROBO MATERIA
                printf("Desaprobo la materia\n");
                al2.desaprobado=1;
                fflush(stdin);
            }else{
               //APROBO MATERIA
               parcialesAprobados++;
            }
        }else{
            //APROBO MATERIA SIN IR A RECUPERATORIO
            parcialesAprobados++;
        }

        if(parcialesAprobados == 1){ //SI APROBO EL PRIMER PARCIAL, PREGUNTA SOBRE EL SEGUNDO
            printf("Ingrese nota del segundo parcial:\n");
            scanf("%f",&al2.parcial2);
            fflush(stdin);
            al2.recuperatorio2=-1;
            fflush(stdin);
            if(al2.parcial2>=0 && al2.parcial2<=3){ // SI DESAPROBO EL SEGUNDO PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al2.recuperatorio2);
                fflush(stdin);
                if(al2.recuperatorio2>=0 && al2.recuperatorio2<=3){ //DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al2.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO EL SEGUNDO PARCIAL SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if(parcialesAprobados == 2){ //SI APROBO EL PRIMER Y EL SEGUNDO PARCIAL
            printf("Ingrese nota del tercer parcial:\n");
            scanf("%f",&al2.parcial3);
            fflush(stdin);
            al2.recuperatorio3=-1;
            fflush(stdin);
            if(al2.parcial3>=0 && al2.parcial3<=3){ //SI DESAPROBO EL TERCER PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al2.recuperatorio3);
                fflush(stdin);
                if(al2.recuperatorio3>=0 && al2.recuperatorio3<=3){ //SI DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al2.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if((al2.parcial3>=4 && al2.parcial3<=10)||(al2.recuperatorio3>=4 && al2.recuperatorio3<=10)){
            printf("Aprobo cursada\n");
            al2.desaprobado=0;
            fflush(stdin);
        }

        if(al2.parcial1>=7 && al2.parcial2>=7 && al2.parcial3>=7){
                al2.final1=(al2.parcial1+al2.parcial2+al2.parcial3)/3;
                al2.aprobadomat=1;
                printf("Alumno promocionado\n");
        }
        if(al2.desaprobado==0 && al2.aprobadomat==-1){
                printf("Ingrese nota de final:\n");
                scanf("%f",&al2.final1);
                if(al2.final1>=4 && al2.final1<=10){
                al2.aprobadomat=1;
                }
                if(al2.final1>=0 && al2.final1<=3){
                al2.aprobadomat=0;
                }
            }
            al2.codmat=1;
            fprintf(lista2,"%d %s %s %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d %d %d\n",l.dni,l.nombre,l.apellido,l.rama,al2.parcial1,al2.recuperatorio1,al2.parcial2,al2.recuperatorio2,al2.parcial3,al2.recuperatorio3,al2.final1,al2.desaprobado,al2.aprobadomat,al2.codmat);
        }
        if(auxdni==l.dni && l.aprobado==1 && l.estado==1 && auxcod==2){
        printf("**********Algoritmos***********\n");
        al3.aprobadomat=-1;
        al3.desaprobado=-1;
        printf("Ingrese nota del primer parcial:\n");
        scanf("%f",&al3.parcial1);
        fflush(stdin);
        al3.recuperatorio1=-1;
        fflush(stdin);
        if(al3.parcial1>=0 && al3.parcial1<=3){ // SI REPROBO ENTONCES PREGUNTA RECUPERATORIO
            printf("Ingrese nota de recuperatorio:\n");
            scanf("%f",&al3.recuperatorio1);
            fflush(stdin);
            if(al3.recuperatorio1>=0 && al3.recuperatorio1<=3){ //DESAPROBO MATERIA
                printf("Desaprobo la materia\n");
                al3.desaprobado=1;
                fflush(stdin);
            }else{
               //APROBO MATERIA
               parcialesAprobados++;
            }
        }else{
            //APROBO MATERIA SIN IR A RECUPERATORIO
            parcialesAprobados++;
        }

        if(parcialesAprobados == 1){ //SI APROBO EL PRIMER PARCIAL, PREGUNTA SOBRE EL SEGUNDO
            printf("Ingrese nota del segundo parcial:\n");
            scanf("%f",&al3.parcial2);
            fflush(stdin);
            al3.recuperatorio2=-1;
            fflush(stdin);
            if(al3.parcial2>=0 && al3.parcial2<=3){ // SI DESAPROBO EL SEGUNDO PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al3.recuperatorio2);
                fflush(stdin);
                if(al3.recuperatorio2>=0 && al3.recuperatorio2<=3){ //DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al3.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO EL SEGUNDO PARCIAL SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if(parcialesAprobados == 2){ //SI APROBO EL PRIMER Y EL SEGUNDO PARCIAL
            printf("Ingrese nota del tercer parcial:\n");
            scanf("%f",&al3.parcial3);
            fflush(stdin);
            al3.recuperatorio3=-1;
            fflush(stdin);
            if(al3.parcial3>=0 && al3.parcial3<=3){ //SI DESAPROBO EL TERCER PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al3.recuperatorio3);
                fflush(stdin);
                if(al3.recuperatorio3>=0 && al3.recuperatorio3<=3){ //SI DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al3.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if((al3.parcial3>=4 && al3.parcial3<=10)||(al3.recuperatorio3>=4 && al3.recuperatorio3<=10)){
            printf("Aprobo cursada\n");
            al3.desaprobado=0;
            fflush(stdin);
        }

        if(al3.parcial1>=7 && al3.parcial2>=7 && al3.parcial3>=7){
                al3.final1=(al3.parcial1+al3.parcial2+al3.parcial3)/3;
                al3.aprobadomat=1;
                printf("Alumno promocionado\n");
        }
        if(al3.desaprobado==0 && al3.aprobadomat==-1){
                printf("Ingrese nota de final:\n");
                scanf("%f",&al3.final1);
                if(al3.final1>=4 && al3.final1<=10){
                al3.aprobadomat=1;
                }
                if(al3.final1>=0 && al3.final1<=3){
                al3.aprobadomat=0;
                }
            }
            al3.codmat=2;
            fprintf(lista3,"%d %s %s %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d %d %d\n",l.dni,l.nombre,l.apellido,l.rama,al3.parcial1,al3.recuperatorio1,al3.parcial2,al3.recuperatorio2,al3.parcial3,al3.recuperatorio3,al3.final1,al3.desaprobado,al3.aprobadomat,al3.codmat);
        }
        if(auxdni==l.dni && l.aprobado==1 && l.estado==1 && auxcod==3){
        printf("**********Matematica I***********\n");
        al4.aprobadomat=-1;
        al4.desaprobado=-1;
        printf("Ingrese nota del primer parcial:\n");
        scanf("%f",&al4.parcial1);
        fflush(stdin);
        al4.recuperatorio1=-1;
        fflush(stdin);
        if(al4.parcial1>=0 && al4.parcial1<=3){ // SI REPROBO ENTONCES PREGUNTA RECUPERATORIO
            printf("Ingrese nota de recuperatorio:\n");
            scanf("%f",&al4.recuperatorio1);
            fflush(stdin);
            if(al4.recuperatorio1>=0 && al4.recuperatorio1<=3){ //DESAPROBO MATERIA
                printf("Desaprobo la materia\n");
                al4.desaprobado=1;
                fflush(stdin);
            }else{
               //APROBO MATERIA
               parcialesAprobados++;
            }
        }else{
            //APROBO MATERIA SIN IR A RECUPERATORIO
            parcialesAprobados++;
        }

        if(parcialesAprobados == 1){ //SI APROBO EL PRIMER PARCIAL, PREGUNTA SOBRE EL SEGUNDO
            printf("Ingrese nota del segundo parcial:\n");
            scanf("%f",&al4.parcial2);
            fflush(stdin);
            al4.recuperatorio2=-1;
            fflush(stdin);
            if(al4.parcial2>=0 && al4.parcial2<=3){ // SI DESAPROBO EL SEGUNDO PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al4.recuperatorio2);
                fflush(stdin);
                if(al4.recuperatorio2>=0 && al4.recuperatorio2<=3){ //DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al4.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO EL SEGUNDO PARCIAL SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if(parcialesAprobados == 2){ //SI APROBO EL PRIMER Y EL SEGUNDO PARCIAL
            printf("Ingrese nota del tercer parcial:\n");
            scanf("%f",&al4.parcial3);
            fflush(stdin);
            al4.recuperatorio3=-1;
            fflush(stdin);
            if(al4.parcial3>=0 && al4.parcial3<=3){ //SI DESAPROBO EL TERCER PARCIAL
                printf("Ingrese nota de recuperatorio:\n");
                scanf("%f",&al4.recuperatorio3);
                fflush(stdin);
                if(al4.recuperatorio3>=0 && al4.recuperatorio3<=3){ //SI DESAPROBO EL RECUPERATORIO
                    printf("Desaprobo la materia\n");
                    al4.desaprobado=1;
                    fflush(stdin);
                }else{
                    //APROBO EL RECUPERATORIO
                    parcialesAprobados++;
                }
            }else{
                //APROBO SIN IR A RECUPERATORIO
                parcialesAprobados++;
            }
        }


        if((al4.parcial3>=4 && al4.parcial3<=10)||(al4.recuperatorio3>=4 && al4.recuperatorio3<=10)){
            printf("Aprobo cursada\n");
            al4.desaprobado=0;
            fflush(stdin);
        }

        if(al4.parcial1>=7 && al4.parcial2>=7 && al4.parcial3>=7){
                al4.final1=(al4.parcial1+al4.parcial2+al4.parcial3)/3;
                al4.aprobadomat=1;
                printf("Alumno promocionado\n");
        }
        if(al4.desaprobado==0 && al4.aprobadomat==-1){
                printf("Ingrese nota de final:\n");
                scanf("%f",&al4.final1);
                if(al4.final1>=4 && al4.final1<=10){
                al4.aprobadomat=1;
                }
                if(al4.final1>=0 && al4.final1<=3){
                al4.aprobadomat=0;
                }
            }
            al4.codmat=3;
            fprintf(lista4,"%d %s %s %d %.2f %.2f %.2f %.2f %.2f %.2f %.2f %d %d %d\n",l.dni,l.nombre,l.apellido,l.rama,al4.parcial1,al4.recuperatorio1,al4.parcial2,al4.recuperatorio2,al4.parcial3,al4.recuperatorio3,al4.final1,al4.desaprobado,al4.aprobadomat,al4.codmat);
        }
}//FIN WHILE
fclose(fd);
fclose(lista1);
fclose(lista2);
fclose(lista3);
fclose(lista4);
}
/////////////////////
void consulta_ingreso(){
int opcion3;
printf("1-Detalle de Alumnos por rama y sexo\n");
printf("2-Nota maxima de la universidad argentina\n");
printf("3-Nota maxima en materia especifica\n");
printf("4-Cantidad de alumnos que desaprobaron el curso de ingreso\n");
printf("5-Cantidad de alumnos que aprobaron el curso de ingreso\n");
printf("6-Mostrar ingresantes\n");
printf("7-Salir\n");
scanf("%d",&opcion3);
while(opcion3!=8){
    switch(opcion3){
    case 1:detalle();
    break;
    case 2:not_max_uni();
    break;
    case 3:not_max_mat();
    break;
    case 4:cant_des_ing();
    break;
    case 5:cant_apro_ing();
    break;
    case 6:mostrar_archivo();
    break;
    case 7:return 0;
    break;
    }
printf("1-Detalle de Alumnos por rama y sexo\n");
printf("2-Nota maxima de la universidad argentina\n");
printf("3-Nota maxima en materia especifica\n");
printf("4-Cantidad de alumnos que desaprobaron el curso de ingreso\n");
printf("5-Cantidad de alumnos que aprobaron el curso de ingreso\n");
printf("6-Mostrar ingresantes\n");
printf("7-Salir\n");
scanf("%d",&opcion3);
}
}
/////////////////////////
void consulta_matpri(){
int opcion4;
printf("1-Cantidad de alumnos que aprobaron todas las materias\n");
printf("2-Materia que mas se desaprobo\n");
printf("3-Alumno que obtuvo la nota maxima en finales\n");
printf("4-Salir\n");
scanf("%d",&opcion4);
while(opcion4!=5){
    switch(opcion4){
    case 1:cant_alum();
    break;
    case 2:mat_des();
    break;
    case 3:not_max_alum();
    break;
    case 4:return 0;
    }
printf("1-Cantidad de alumnos que aprobaron todas las materias\n");
printf("2-Materia que mas se desaprobo\n");
printf("3-Alumno que obtuvo la nota maxima en finales\n");
printf("4-Salir\n");
scanf("%d",&opcion4);
}
}
////////////////////////

//////////////
void altas(){
int auxdni;
ingresante a;
FILE*fd;
FILE*fdaux;
fd=fopen("ingreso.dat","r");
fdaux=fopen("ingresoaux.dat","a");
if(fd==NULL)return -1;
printf("Ingrese DNI:\n");
scanf("%d",&auxdni);
while(!feof(fd)){
    fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&a.dni,&a.nombre,&a.apellido,&a.fechaNac,&a.sexo,&a.localidad,&a.calle,&a.num,&a.piso,&a.dpto,&a.cp,&a.establecimiento,&a.rama,&a.finalizacion,&a.notamat,&a.notauni,&a.estado,&a.aprobado);
    if(auxdni==a.dni && a.estado==0){
        a.estado=1;
    }
    if(auxdni==a.dni && a.estado==1){
        printf("Ingresante ya esta dado de alta\n\n");
    }
 fprintf(fdaux,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %.2f %.2f %d %d\n",a.dni,a.nombre,a.apellido,a.fechaNac,a.sexo,a.localidad,a.calle,a.num,a.piso,a.dpto,a.cp,a.establecimiento,a.rama,a.finalizacion,a.notamat,a.notauni,a.estado,a.aprobado);
}
fclose(fd);
fclose(fdaux);
remove("ingreso.dat");
rename("ingresoaux.dat","ingreso.dat");
}
//////////////
void bajas(){
int auxdni;
ingresante b;
FILE*fd;
FILE*fdaux;
fd=fopen("ingreso.dat","r");
fdaux=fopen("ingresoaux.dat","a");
if(fd==NULL)return -1;
printf("Ingrese DNI:\n");
scanf("%d",&auxdni);
while(!feof(fd)){
    fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&b.dni,&b.nombre,&b.apellido,&b.fechaNac,&b.sexo,&b.localidad,&b.calle,&b.num,&b.piso,&b.dpto,&b.cp,&b.establecimiento,&b.rama,&b.finalizacion,&b.notamat,&b.notauni,&b.estado,&b.aprobado);
    if(auxdni==b.dni && b.estado==1){
        b.estado=0;
    }
    if(auxdni==b.dni && b.estado==0){
        printf("Ingresante ya esta dado de baja\n\n");
    }
 fprintf(fdaux,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %.2f %.2f %d %d\n",b.dni,b.nombre,b.apellido,b.fechaNac,b.sexo,b.localidad,b.calle,b.num,b.piso,b.dpto,b.cp,b.establecimiento,b.rama,b.finalizacion,b.notamat,b.notauni,b.estado,b.aprobado);
}
fclose(fd);
fclose(fdaux);
remove("ingreso.dat");
rename("ingresoaux.dat","ingreso.dat");
}
//////////////
void modi(){
int auxdni;
ingresante m;
FILE*fd;
FILE*fdaux;
fd=fopen("ingreso.dat","r");
fdaux=fopen("ingresoaux.dat","a");
if(fd==NULL)return -1;
printf("Ingrese DNI:\n");
scanf("%d",&auxdni);
while(!feof(fd)){
   fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&m.dni,&m.nombre,&m.apellido,&m.fechaNac,&m.sexo,&m.localidad,&m.calle,&m.num,&m.piso,&m.dpto,&m.cp,&m.establecimiento,&m.rama,&m.finalizacion,&m.notamat,&m.notauni,&m.estado,&m.aprobado);
   if(auxdni==m.dni && m.estado==1){
    fflush(stdin);
    printf("Ingrese nombre: \n");
    scanf("%s",m.nombre);
    fflush(stdin);
    printf("Ingrese apellido: \n");
    scanf("%s",m.apellido);
    fflush(stdin);
    printf("Ingrese fecha de nacimiento: (MM/DD/AAAA)\n");
    scanf("%s",&m.fechaNac);
    fflush(stdin);
    printf("Ingrese sexo: m(masculino) f(femenino)\n");
    scanf("%c",&m.sexo);
    fflush(stdin);
    printf("Ingrese localidad: \n");
    scanf("%s",m.localidad);
    fflush(stdin);
    printf("Ingrese calle: \n");
    scanf("%s",m.calle);
    fflush(stdin);
    printf("Ingrese numero: \n");
    scanf("%d",&m.num);
    fflush(stdin);
    printf("Ingrese piso: \n");
    scanf("%d",&m.piso);
    fflush(stdin);
    printf("Ingrese departamento: \n");
    scanf("%d",&m.dpto);
    fflush(stdin);
    printf("Ingrese codigo postal: \n");
    scanf("%d",&m.cp);
    fflush(stdin);
    printf("Ingrese establecimiento: \n");
    scanf("%s",m.establecimiento);
    fflush(stdin);
    printf("Ingrese rama: 1(tecnico) 2(ciencias sociales) 3(comercial)\n");
    scanf("%d",&m.rama);
    fflush(stdin);
    printf("Ingrese anio de finalizacion de estudios: \n");
    scanf("%d",&m.finalizacion);
    fflush(stdin);
    m.estado=1;
   }
   if(auxdni==m.dni && m.estado==0){
    printf("Ingresante dado de baja no se puede modificar\n\n");
   }
fprintf(fdaux,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %.2f %.2f %d %d\n",m.dni,m.nombre,m.apellido,m.fechaNac,m.sexo,m.localidad,m.calle,m.num,m.piso,m.dpto,m.cp,m.establecimiento,m.rama,m.finalizacion,m.notamat,m.notauni,m.estado,m.aprobado);
}
fclose(fd);
fclose(fdaux);
remove("ingreso.dat");
rename("ingresoaux.dat","ingreso.dat");
}
//////////////

////////////////
void detalle(){
int aux;
int aux2;
FILE *fd;
ingresante d;
fd=fopen("ingreso.dat","r");
if(fd==NULL)return -1;
printf("Ingrese busqueda por sexo(1) o rama(2):\n");
scanf("%d",&aux);
switch(aux){
    case 1:printf("Masculino(1) Femenino(2)\n");
           scanf("%d",&aux2);
    break;
    case 2:printf("Tecnico(3) Ciencias Sociales(4) Comercial(5)\n");
           scanf("%d",&aux2);
    break;
}
while(!feof(fd))
        {
    fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&d.dni,&d.nombre,&d.apellido,&d.fechaNac,&d.sexo,&d.localidad,&d.calle,&d.num,&d.piso,&d.dpto,&d.cp,&d.establecimiento,&d.rama,&d.finalizacion,&d.notamat,&d.notauni,&d.estado,&d.aprobado);
    switch(aux2){
    case 1:if(d.sexo=='m'){
    printf("******************************\n");
    printf("DNI:%d Nombre y Apellido:%s %s MM/DD/AAAA:%s Sexo:%c Localidad:%s Calle:%s Numero:%d Piso:%d Departamento:%d Codigo Postal:%d Establecimiento:%s Rama:%d Finalizacion:%d Nota materia:%.2f Nota universidad:%.2f %d %d\n",d.dni,d.nombre,d.apellido,d.fechaNac,d.sexo,d.localidad,d.calle,d.num,d.piso,d.dpto,d.cp,d.establecimiento,d.rama,d.finalizacion,d.notamat,d.notauni,d.estado,d.aprobado);
    printf("******************************\n\n");
    }
    break;
    case 2:if(d.sexo=='f'){
    printf("******************************\n");
    printf("DNI:%d Nombre y Apellido:%s %s MM/DD/AAAA:%s Sexo:%c Localidad:%s Calle:%s Numero:%d Piso:%d Departamento:%d Codigo Postal:%d Establecimiento:%s Rama:%d Finalizacion:%d Nota materia:%.2f Nota universidad:%.2f %d %d\n",d.dni,d.nombre,d.apellido,d.fechaNac,d.sexo,d.localidad,d.calle,d.num,d.piso,d.dpto,d.cp,d.establecimiento,d.rama,d.finalizacion,d.notamat,d.notauni,d.estado,d.aprobado);
    printf("******************************\n\n");
    }
    break;
    case 3:if(d.rama==1){
    printf("******************************\n");
    printf("DNI:%d Nombre y Apellido:%s %s MM/DD/AAAA:%s Sexo:%c Localidad:%s Calle:%s Numero:%d Piso:%d Departamento:%d Codigo Postal:%d Establecimiento:%s Rama:%d Finalizacion:%d Nota materia:%.2f Nota universidad:%.2f %d %d\n",d.dni,d.nombre,d.apellido,d.fechaNac,d.sexo,d.localidad,d.calle,d.num,d.piso,d.dpto,d.cp,d.establecimiento,d.rama,d.finalizacion,d.notamat,d.notauni,d.estado,d.aprobado);
    printf("******************************\n\n");
    }
    break;
    case 4:if(d.rama==2){
    printf("******************************\n");
    printf("DNI:%d Nombre y Apellido:%s %s MM/DD/AAAA:%s Sexo:%c Localidad:%s Calle:%s Numero:%d Piso:%d Departamento:%d Codigo Postal:%d Establecimiento:%s Rama:%d Finalizacion:%d Nota materia:%.2f Nota universidad:%.2f %d %d\n",d.dni,d.nombre,d.apellido,d.fechaNac,d.sexo,d.localidad,d.calle,d.num,d.piso,d.dpto,d.cp,d.establecimiento,d.rama,d.finalizacion,d.notamat,d.notauni,d.estado,d.aprobado);
    printf("******************************\n\n");
    }
    break;
    case 5:if(d.rama==3){
    printf("******************************\n");
    printf("DNI:%d Nombre y Apellido:%s %s MM/DD/AAAA:%s Sexo:%c Localidad:%s Calle:%s Numero:%d Piso:%d Departamento:%d Codigo Postal:%d Establecimiento:%s Rama:%d Finalizacion:%d Nota materia:%.2f Nota universidad:%.2f %d %d\n",d.dni,d.nombre,d.apellido,d.fechaNac,d.sexo,d.localidad,d.calle,d.num,d.piso,d.dpto,d.cp,d.establecimiento,d.rama,d.finalizacion,d.notamat,d.notauni,d.estado,d.aprobado);
    printf("******************************\n\n");
    }
    break;
    }
    }
fclose(fd);
}
////////////////
void not_max_uni(){
float max=0;
char maxnombre[10];
char maxapellido[10];
ingresante nu;
FILE*fd;
fd=fopen("ingreso.dat","r");
if(fd==NULL)return -1;
while(!feof(fd)){
     fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&nu.dni,&nu.nombre,&nu.apellido,&nu.fechaNac,&nu.sexo,&nu.localidad,&nu.calle,&nu.num,&nu.piso,&nu.dpto,&nu.cp,&nu.establecimiento,&nu.rama,&nu.finalizacion,&nu.notamat,&nu.notauni,&nu.estado,&nu.aprobado);
     if(nu.notauni>max){
        max=nu.notauni;
        strcpy(maxnombre,nu.nombre);
        strcpy(maxapellido,nu.apellido);
        }
     }
     printf("******************************************************************\n");
     printf("Nota maxima:%.2f Nombre y Apellido: %s %s\n",max,maxnombre,maxapellido);
     printf("******************************************************************\n\n");
fclose(fd);
}
////////////////
void not_max_mat(){
float max=0;
char maxnombre[10];
char maxapellido[10];
ingresante nm;
FILE*fd;
fd=fopen("ingreso.dat","r");
if(fd==NULL)return -1;
while(!feof(fd)){
     fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&nm.dni,&nm.nombre,&nm.apellido,&nm.fechaNac,&nm.sexo,&nm.localidad,&nm.calle,&nm.num,&nm.piso,&nm.dpto,&nm.cp,&nm.establecimiento,&nm.rama,&nm.finalizacion,&nm.notamat,&nm.notauni,&nm.estado,&nm.aprobado);
     if(nm.notamat>max){
        max=nm.notamat;
        strcpy(maxnombre,nm.nombre);
        strcpy(maxapellido,nm.apellido);
        }
     }
     printf("******************************************************************\n");
     printf("Nota maxima:%.2f Nombre y Apellido: %s %s\n",max,maxnombre,maxapellido);
     printf("******************************************************************\n\n");
fclose(fd);
}
////////////////
void cant_des_ing(){
int cantd=0;
ingresante cd;
FILE*fd;
fd=fopen("ingreso.dat","r");
if(fd==NULL)return -1;
while(!feof(fd)){
    fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&cd.dni,&cd.nombre,&cd.apellido,&cd.fechaNac,&cd.sexo,&cd.localidad,&cd.calle,&cd.num,&cd.piso,&cd.dpto,&cd.cp,&cd.establecimiento,&cd.rama,&cd.finalizacion,&cd.notamat,&cd.notauni,&cd.estado,&cd.aprobado);
    if(cd.estado==1 && cd.aprobado==0){
        cantd++;
        }
    if(cd.aprobado==0){
        printf("DNI:%d Nombre y Apellido:%s %s\n",cd.dni,cd.nombre,cd.apellido);
    }
    }
printf("Cantidad de ingresantes desaprobados:%d\n\n",cantd);
fclose(fd);
}
////////////////
void cant_apro_ing(){
int canta=0;
ingresante ca;
FILE*fd;
fd=fopen("ingreso.dat","r");
if(fd==NULL)return -1;
while(!feof(fd)){
    fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&ca.dni,&ca.nombre,&ca.apellido,&ca.fechaNac,&ca.sexo,&ca.localidad,&ca.calle,&ca.num,&ca.piso,&ca.dpto,&ca.cp,&ca.establecimiento,&ca.rama,&ca.finalizacion,&ca.notamat,&ca.notauni,&ca.estado,&ca.aprobado);
    if(ca.estado=1 && ca.aprobado==1){
        canta++;
    }
    if(ca.aprobado==1){
    printf("DNI:%d Nombre y Apellido:%s %s\n",ca.dni,ca.nombre,ca.apellido);
    }
  }
printf("Cantidad de ingresantes aprobados:%d\n\n",canta);
fclose(fd);
}
////////////////
void mostrar_archivo(){
ingresante m;
FILE*fd;
fd=fopen("ingreso.dat","r");
if(fd==NULL)return -1;
while(!feof(fd)){
    fscanf(fd,"%d %s %s %s %c %s %s %d %d %d %d %s %d %d %f %f %d %d\n",&m.dni,&m.nombre,&m.apellido,&m.fechaNac,&m.sexo,&m.localidad,&m.calle,&m.num,&m.piso,&m.dpto,&m.cp,&m.establecimiento,&m.rama,&m.finalizacion,&m.notamat,&m.notauni,&m.estado,&m.aprobado);
    printf("******************************\n");
    printf("DNI:%d Nombre y Apellido:%s %s MM/DD/AAAA:%s Sexo:%c Localidad:%s Calle:%s Numero:%d Piso:%d Departamento:%d Codigo Postal:%d Establecimiento:%s Rama:%d Finalizacion:%d Nota materia:%.2f Nota universidad:%.2f %d %d\n",m.dni,m.nombre,m.apellido,m.fechaNac,m.sexo,m.localidad,m.calle,m.num,m.piso,m.dpto,m.cp,m.establecimiento,m.rama,m.finalizacion,m.notamat,m.notauni,m.estado,m.aprobado);
    printf("******************************\n\n");
    }
fclose(fd);
}
////////////////
void cant_alum(){
int cont1=0;
int cont2=0;
int cont3=0;
int cont4=0;
ingresante i1;
ingresante i2;
ingresante i3;
ingresante i4;
notas al6;
notas al7;
notas al8;
notas al9;
FILE*lista1;
FILE*lista2;
FILE*lista3;
FILE*lista4;
lista1=fopen("notaOrg.dat","rb");
lista2=fopen("notaProg.dat","rb");
lista3=fopen("notaAlg.dat","rb");
lista4=fopen("notaMat.dat","rb");
if(lista1==NULL && lista2==NULL && lista3==NULL && lista4==NULL)return -1;
while(!feof(lista1)){
    fscanf(lista1,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i1.dni,&i1.nombre,&i1.apellido,&i1.rama,&al6.parcial1,&al6.recuperatorio1,&al6.parcial2,&al6.recuperatorio2,&al6.parcial3,&al6.recuperatorio3,&al6.final1,&al6.desaprobado,&al6.aprobadomat,&al6.codmat);
    if(al6.aprobadomat==1){
        cont1++;
    }
    }
    printf("*************************************\n");
    printf("Alumnos que aprobaron Organizacion:%d\n",cont1);
    printf("*************************************\n\n");
while(!feof(lista4)){
    fscanf(lista4,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i4.dni,&i4.nombre,&i4.apellido,&i4.rama,&al9.parcial1,&al9.recuperatorio1,&al9.parcial2,&al9.recuperatorio2,&al9.parcial3,&al9.recuperatorio3,&al9.final1,&al9.desaprobado,&al9.aprobadomat,&al9.codmat);
    if(al9.aprobadomat==1){
        cont4++;
    }
    }
    printf("*************************************\n");
    printf("Alumnos que aprobaron Matematica I:%d\n",cont4);
    printf("*************************************\n\n");
while(!feof(lista3)){
    fscanf(lista3,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i3.dni,&i3.nombre,&i3.apellido,&i3.rama,&al8.parcial1,&al8.recuperatorio1,&al8.parcial2,&al8.recuperatorio2,&al8.parcial3,&al8.recuperatorio3,&al8.final1,&al8.desaprobado,&al8.aprobadomat,&al8.codmat);
    if(al8.aprobadomat==1){
        cont3++;
    }
    }
    printf("*************************************\n");
    printf("Alumnos que aprobaron Algoritmos:%d\n",cont3);
    printf("*************************************\n\n");
while(!feof(lista2)){
    fscanf(lista2,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i2.dni,&i2.nombre,&i2.apellido,&i2.rama,&al7.parcial1,&al7.recuperatorio1,&al7.parcial2,&al7.recuperatorio2,&al7.parcial3,&al7.recuperatorio3,&al7.final1,&al7.desaprobado,&al7.aprobadomat,&al7.codmat);
    if(al7.aprobadomat==1){
        cont2++;
    }
    }
    printf("*************************************\n");
    printf("Alumnos que aprobaron Programacion:%d\n",cont2);
    printf("*************************************\n\n");

fclose(lista1);
fclose(lista2);
fclose(lista3);
fclose(lista4);
}
////////////////
void mat_des(){
int alumc=0;
int alumc1=0;
int alumc2=0;
int alumc3=0;
int aluma=0;
int aluma1=0;
int aluma2=0;
int aluma3=0;
int alumb=0;
int alumb1=0;
int alumb2=0;
int alumb3=0;
int alumd=0;
int alumd1=0;
int alumd2=0;
int alumd3=0;
ingresante i5;
ingresante i6;
ingresante i7;
ingresante i8;
notas ala;
notas alb;
notas alc;
notas ald;
FILE*lista1;
FILE*lista2;
FILE*lista3;
FILE*lista4;
lista1=fopen("notaOrg.dat","rb");
lista2=fopen("notaProg.dat","rb");
lista3=fopen("notaAlg.dat","rb");
lista4=fopen("notaMat.dat","rb");
if(lista1==NULL && lista2==NULL && lista3==NULL && lista4==NULL)return -1;
while(!feof(lista1)){
    fscanf(lista1,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i5.dni,&i5.nombre,&i5.apellido,&i5.rama,&ala.parcial1,&ala.recuperatorio1,&ala.parcial2,&ala.recuperatorio2,&ala.parcial3,&ala.recuperatorio3,&ala.final1,&ala.desaprobado,&ala.aprobadomat,&ala.codmat);
    if(ala.desaprobado==1){
        alumc++;
    }
    if(ala.desaprobado==1 && i5.rama==1){
        alumc1 ++;
    }
    if(ala.desaprobado==1 && i5.rama==2){
        alumc2 ++;
    }
    if(ala.desaprobado==1 && i5.rama==3){
        alumc3 ++;
    }
    }
////////////////////////////////////////////////////////////////////////////////
while(!feof(lista2)){
    fscanf(lista2,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i6.dni,&i6.nombre,&i6.apellido,&i6.rama,&alb.parcial1,&alb.recuperatorio1,&alb.parcial2,&alb.recuperatorio2,&alb.parcial3,&alb.recuperatorio3,&alb.final1,&alb.desaprobado,&alb.aprobadomat,&alb.codmat);
    if(alb.desaprobado==1){
        aluma++;
    }
    if(alb.desaprobado==1 && i6.rama==1){
        aluma1 ++;
    }
    if(alb.desaprobado==1 && i6.rama==2){
        aluma2 ++;
    }
    if(alb.desaprobado==1 && i6.rama==3){
        aluma3 ++;
    }
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
while(!feof(lista3)){
    fscanf(lista3,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i7.dni,&i7.nombre,&i7.apellido,&i7.rama,&alc.parcial1,&alc.recuperatorio1,&alc.parcial2,&alc.recuperatorio2,&alc.parcial3,&alc.recuperatorio3,&alc.final1,&alc.desaprobado,&alc.aprobadomat,&alc.codmat);
    if(alc.desaprobado==1){
        alumb++;
    }
    if(alc.desaprobado==1 && i7.rama==1){
        alumb1 ++;
    }
    if(alc.desaprobado==1 && i7.rama==2){
        alumb2 ++;
    }
    if(alc.desaprobado==1 && i7.rama==3){
        alumb3 ++;
    }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
while(!feof(lista4)){
    fscanf(lista4,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&i8.dni,&i8.nombre,&i8.apellido,&i8.rama,&ald.parcial1,&ald.recuperatorio1,&ald.parcial2,&ald.recuperatorio2,&ald.parcial3,&ald.recuperatorio3,&ald.final1,&ald.desaprobado,&ald.aprobadomat,&ald.codmat);
    if(ald.desaprobado==1){
        alumd++;
    }
    if(ald.desaprobado==1 && i8.rama==1){
        alumd1 ++;
    }
    if(ald.desaprobado==1 && i8.rama==2){
        alumd2 ++;
    }
    if(ald.desaprobado==1 && i8.rama==3){
        alumd3 ++;
    }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(alumc>aluma && alumc>alumb && alumc>alumd){

    if(alumc1>alumc2 && alumc1>alumc3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Organizacion de Computadoras,cantidad total de desaprobados de %d,la rama que mas desaprobo es  tecnico con %d\n",alumc,alumc1);
        printf("***********************************************************************************\n\n");
    }
    if(alumc2>alumc1 && alumc2>alumc3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Organizacion de Computadoras,cantidad total de desaprobados de %d,la rama que mas desaprobo es ciencias sociales con %d\n",alumc,alumc2);
        printf("***********************************************************************************\n\n");
    }
    if(alumc3>alumc1 && alumc3>alumc2){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Organizacion de Computadoras,cantidad total de desaprobados de %d,la rama que mas desaprobo es comercial con %d\n",alumc,alumc3);
        printf("***********************************************************************************\n\n");
    }
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(aluma>alumc && aluma>alumb && aluma>alumd){

    if(aluma1>aluma2 && aluma1>aluma3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Programacion de Computadoras,cantidad total de desaprobados de %d,la rama que mas desaprobo es la tecnico con %d\n",aluma,aluma1);
        printf("***********************************************************************************\n\n");
    }
    if(aluma2>aluma1 && aluma2>aluma3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Programacion de Computadoras,cantidad total de desaprobados de %d,la rama que mas desaprobo es ciencias sociales con %d\n",aluma,aluma2);
        printf("***********************************************************************************\n\n");
    }
    if(aluma3>aluma1 && aluma3>aluma2){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Programacion de Computadoras,cantidad total de desaprobados de %d,la rama que mas desaprobo es comercial con %d\n",aluma,aluma3);
        printf("***********************************************************************************\n\n");
    }
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(alumb>alumc && alumb>aluma && alumb>alumd){

    if(alumb1>alumb2 && alumb1>alumb3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Algoritmos,cantidad total de desaprobados de %d,la rama que mas desaprobo es la tecnico con %d\n",alumb,alumb1);
        printf("***********************************************************************************\n\n");
    }
    if(alumb2>alumb1 && alumb2>alumb3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Algoritmos,cantidad total de desaprobados de %d,la rama que mas desaprobo es ciencias sociales con %d\n",alumb,alumb2);
        printf("***********************************************************************************\n\n");
    }
    if(alumb3>alumb1 && alumb3>alumb2){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Algoritmos,cantidad total de desaprobados de %d,la rama que mas desaprobo es comercial con %d\n",alumb,alumb3);
        printf("***********************************************************************************\n\n");
    }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(alumd>alumc && alumd>aluma && alumd>alumb){

    if(alumd1>alumd2 && alumd1>alumd3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Matematica I,cantidad total de desaprobados de %d,la rama que mas desaprobo es la tecnico con %d\n",alumd,alumd1);
        printf("***********************************************************************************\n\n");
    }
    if(alumd2>alumd1 && alumd2>alumd3){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Matematica I,cantidad total de desaprobados de %d,la rama que mas desaprobo es ciencias sociales con %d\n",alumd,alumd2);
        printf("***********************************************************************************\n\n");
    }
    if(alumd3>alumd1 && alumd3>alumd2){
        printf("***********************************************************************************\n");
        printf("Materia mas desaprobada Matematica I,cantidad total de desaprobados de %d,la rama que mas desaprobo es comercial con %d\n",alumd,alumd3);
        printf("***********************************************************************************\n\n");
    }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
fclose(lista1);
fclose(lista2);
fclose(lista3);
fclose(lista4);
}
////////////////
void not_max_alum(){
float max1=0;
float max2=0;
float max3=0;
float max4=0;
char maxnombre1[10];
char maxapellido1[10];
char maxnombre2[10];
char maxapellido2[10];
char maxnombre3[10];
char maxapellido3[10];
char maxnombre4[10];
char maxapellido4[10];
ingresante ia;
ingresante ib;
ingresante ic;
ingresante id;
notas ale;
notas alf;
notas alg;
notas alh;
FILE*lista1;
FILE*lista2;
FILE*lista3;
FILE*lista4;
lista1=fopen("notaOrg.dat","rb");
lista2=fopen("notaProg.dat","rb");
lista3=fopen("notaAlg.dat","rb");
lista4=fopen("notaMat.dat","rb");
if(lista1==NULL && lista2==NULL && lista3==NULL && lista4==NULL)return -1;
while(!feof(lista1)){
    fscanf(lista1,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&ia.dni,&ia.nombre,&ia.apellido,&ia.rama,&ale.parcial1,&ale.recuperatorio1,&ale.parcial2,&ale.recuperatorio2,&ale.parcial3,&ale.recuperatorio3,&ale.final1,&ale.desaprobado,&ale.aprobadomat,&ale.codmat);
    if(ale.final1>max1){
        max1=ale.final1;
        strcpy(maxnombre1,ia.nombre);
        strcpy(maxapellido1,ia.apellido);
    }
}
while(!feof(lista2)){
    fscanf(lista2,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&ib.dni,&ib.nombre,&ib.apellido,&ib.rama,&alf.parcial1,&alf.recuperatorio1,&alf.parcial2,&alf.recuperatorio2,&alf.parcial3,&alf.recuperatorio3,&alf.final1,&alf.desaprobado,&alf.aprobadomat,&alf.codmat);
    if(alf.final1>max2){
        max2=alf.final1;
        strcpy(maxnombre2,ib.nombre);
        strcpy(maxapellido2,ib.apellido);
    }
}
while(!feof(lista3)){
    fscanf(lista3,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&ic.dni,&ic.nombre,&ic.apellido,&ic.rama,&alg.parcial1,&alg.recuperatorio1,&alg.parcial2,&alg.recuperatorio2,&alg.parcial3,&alg.recuperatorio3,&alg.final1,&alg.desaprobado,&alg.aprobadomat,&alg.codmat);
    if(alg.final1>max3){
        max3=alg.final1;
        strcpy(maxnombre3,ic.nombre);
        strcpy(maxapellido3,ic.apellido);
    }
}
while(!feof(lista4)){
    fscanf(lista4,"%d %s %s %d %f %f %f %f %f %f %f %d %d %d\n",&id.dni,&id.nombre,&id.apellido,&id.rama,&alh.parcial1,&alh.recuperatorio1,&alh.parcial2,&alh.recuperatorio2,&alh.parcial3,&alh.recuperatorio3,&alh.final1,&alh.desaprobado,&alh.aprobadomat,&alh.codmat);
    if(alh.final1>max4){
        max4=alh.final1;
        strcpy(maxnombre4,id.nombre);
        strcpy(maxapellido4,id.apellido);
    }
}
if(max1>max2 && max1>max3 && max1> max4){
    printf("************************************************\n");
    printf("Nota Maxima:%.2f Nombre y Apellido:%s %s Materia Organizacion de Computadoras\n",max1,maxnombre1,maxapellido1);
    printf("************************************************\n\n");
}
if(max2>max1 && max2>max3 && max2> max4){
    printf("************************************************\n");
    printf("Nota Maxima:%.2f Nombre y Apellido:%s %s Materia Programacion de Computadoras\n",max2,maxnombre2,maxapellido2);
    printf("************************************************\n\n");
}
if(max3>max1 && max3>max2 && max3> max4){
    printf("************************************************\n");
    printf("Nota Maxima:%.2f Nombre y Apellido:%s %s Materia Algoritmos\n\n",max3,maxnombre3,maxapellido3);
    printf("************************************************\n\n");
}
if(max4>max1 && max4>max2 && max4> max3){
    printf("************************************************\n");
    printf("Nota Maxima:%.2f Nombre y Apellido:%s %s Materia Matematica I\n",max4,maxnombre4,maxapellido4);
    printf("************************************************\n\n");
}
fclose(lista1);
fclose(lista2);
fclose(lista3);
fclose(lista4);
}
////////////////
void nota_corte(){
int auxcorte;
printf("Ingrese nota de corte:\n");
scanf("%d",&auxcorte);
auxcorte=corte;
}
////////////////
int main()
{
    int salir=0;
    int opcion;

    while(salir==0){
        opcion=-1;
        ver_menu();
        fflush(stdin);
        scanf("%d",&opcion);


        if(opcion==8)salir=1;
        else if(opcion==1)actualizacion();
        else if(opcion==2)carga_alumnos();
        else if(opcion==3)carga_examingre();
        else if(opcion==4)carga_notmat();
        else if(opcion==5)consulta_ingreso();
        else if(opcion==6)consulta_matpri();
        else if(opcion==7)nota_corte();
        }
   return 0;
}
