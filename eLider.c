#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int calcularId(int r,int cont, int id);
void calculoLider(int id, int v[2],int r,int soylider,int cont);

void main(int argc, char* argv[]){
	int id=0, idMayor=0, vueltas=0;
	int lider[2];
	int p,r,n;
	int soylider=0;

	srand(time(NULL));
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	
	while(vueltas!=2){
		switch(r){
		case 0:	
			id=calcularId(r,vueltas,id);
			if(vueltas==0){		
				lider[0]=id;
				lider[1]=r;
			}
			else if(vueltas==1){
				MPI_Recv(&lider,2,MPI_INT,7,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);			
			}
			MPI_Send(&lider,2,MPI_INT,1,0,MPI_COMM_WORLD);
		break;
		case 1:
			MPI_Recv(&lider,2,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,2,0,MPI_COMM_WORLD);	
		break;
		case 2:
			MPI_Recv(&lider,2,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,3,0,MPI_COMM_WORLD);
		break;
		case 3:
			MPI_Recv(&lider,2,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,4,0,MPI_COMM_WORLD);
		break;
		case 4:
			MPI_Recv(&lider,2,MPI_INT,3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,5,0,MPI_COMM_WORLD);
		break;
		case 5:
			MPI_Recv(&lider,2,MPI_INT,4,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,6,0,MPI_COMM_WORLD);
		break;
		case 6:
			MPI_Recv(&lider,2,MPI_INT,5,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,7,0,MPI_COMM_WORLD);
		break;
		case 7:
			MPI_Recv(&lider,2,MPI_INT,6,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			id=calcularId(r,vueltas,id);
			calculoLider(id,lider,r,soylider,vueltas);
			MPI_Send(&lider,2,MPI_INT,0,0,MPI_COMM_WORLD);
		break;
		}
	vueltas++;
	}
	MPI_Finalize();
}

int calcularId(int r,int cont,int id){
	if(cont==0){
		r=r+20;
		return (rand()%r);
	}
	else return id;
}

void calculoLider(int id, int v[2],int r,int soylider,int cont){
	if(cont==0){	
		if(id>v[0]){
			v[0]=id;
			v[1]=r;	
			soylider=1;
		}
	}
	else{
		if(id!=v[0]){
			soylider=0;
			printf("Soy proceso: %d, y el Rango del Lider es: %d\n",r,v[1]);		
		}
		else{
			printf("Soy proceso: %d, y Soy el Lider\n",r);
		}
	}	
}
