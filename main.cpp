#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

fstream archivo;
ofstream archivo1;

string toBinary(int num){

    string bin, binario="";

    while(num>0){
        if(num%2==0){
            bin=bin+"0";
        }else{
            bin=bin+"1";
        }
        num=num/2;
    }

    for(int i=5;i>=0;i--){
       binario+=bin[i];
    }
    return binario;
}

string toString(string binario){

    int len=binario.size();

    if(len==24){

        string num, pal;
        int aux[]={1,2,4,8,16,32,64,128,256};
        int i=0;
        int digito;
        int res, cont=0;
        char letra;

        while(i<len){

            for(int j=0;j<=5;j++){
                num[j]=binario[i];
                i++;
            }
            for(int j=5;j>=0;j--){
                digito=num[j];
                if(digito=='1'){
                    res=res+aux[cont];
                }
                cont++;
            }
            letra=res;
            cont=0;
            pal+=letra;
            res=0;
        }
        return pal;

    }else{
        return 0;
    }

}

string numToAscii(int num){

    int cifras[4];
    int i=0;
    string binario="";

    while(num>0){
        cifras[i]=num%10;
        num=num/10;
        i++;
    }
    for(int j=i-1;j>=0;j--){
        char letra=cifras[j]+'0';
        int bite=letra;
        binario+=toBinary(bite);
    }

    return binario;
}

string decodificacion(string binario, int semilla){

    string copia=binario;
    int len=binario.size();
    int seed=semilla;
    int a=0;

    while(semilla<=len){

        for(int i=a;i<semilla;i++){
            if(i==semilla-1){
                binario[semilla-1]=copia[a];
            }else{
                binario[i]=copia[i+1];
            }
        }
        a=semilla;
        semilla=seed+semilla;

    }
    return binario;
}

string codificacion(string binario,int semilla){

    string copia=binario;
    int len=binario.size();
    int seed=semilla;
    int a=0;

    while(semilla<=len){

        for(int i=a;i<semilla;i++){
            if(i==a){
                binario[i]=copia[semilla-1];
            }else{
                binario[i]=copia[i-1];
            }
        }

        a=semilla;
        semilla=seed+semilla;

    }
    return binario;
}

int opciones(){
	cout<<"Operaciones"<<endl;
	cout<<"-----------"<<endl;
	cout<<endl;
	
	while(true){
		
		int opc;
		
        cout<<"Cobro por operacion: 1000"<<endl;
        cout<<"1: Consultar saldo: "<<endl;
		cout<<"2: Retirar dinero: "<<endl;
		cout<<"Elije una operacion: ";cin>>opc;

        if(opc==1 || opc==2){
			cout<<endl;
			return opc;
			break;
		}else{
			cout<<endl;
			cout<<"Error"<<endl;
		}
	}
}

int retirar(int saldo){

    int retiro, total;

    cout<<"Saldo actual: "<<saldo<<endl;
    cout<<"Cuanto deseas retirar?: ";cin>>retiro;

    total=saldo-retiro;

    if(total<0){
        cout<<"ERROR"<<endl;
        exit(0);
    }else{
        cout<<"tu nuevo saldo es: "<<total<<endl;
    }
    return total;
}

int main(){

    archivo.open("sudo.txt",ios::in);
    
    if(archivo.is_open()){
    	
    	int j=0;
    	string linea;
    	int array[50][3];
    	
    	while(!archivo.eof()){
    	
    		getline(archivo,linea);
    		int aux[3];
    		int cont=0, temp=0;
            bool ban=false;
    	
    		for(int i=0;i<int(linea.length());i++){
    	
    			if(linea.at(i)==',' && cont==0){
    				string cedula=linea.substr(temp,i);
    				cont=1;
					temp=i+1;
    				int ced=atoi(cedula.c_str());
    				aux[0]=ced;
                }else if(linea.at(i)==',' && cont==1 && ban==false){
                    string clave=linea.substr(temp,4);
                    cont=2; temp=i+1; ban=true;
                    int pass=atoi(clave.c_str());
    				aux[1]=pass;
				}else if(cont==2){
					string sal=linea.substr(temp);
					int saldo=atoi(sal.c_str());
					aux[2]=saldo;
    				cont+=1; temp=i;
				}
			}
		
		array[j][0]=aux[0];
		array[j][1]=aux[1];
		array[j][2]=aux[2];	
		j++;
		
		}

		archivo.close();
    	
        int user, pass, usr;
        int admin, disp;
    	bool ban=false;

    	cout<<"\t\t\t\t\tLOGIN DE USUARIO"<<endl;
    	cout<<"\t\t\t\t\t----------------"<<endl;

    	while(true){
    		
        	cout<<"\nCedula: ";cin>>user;
        	cout<<"Contrasena: ";cin>>pass;

        	for(int i=0;i<50;i++){
    			int ced=array[i][0];
    			int password=array[i][1];

                if(ced==user && pass==password){
                    admin=ced;
                    disp=array[i][2]-1000;
                    usr=i;
    				ban=true;
				}
			}
        	
        	if(ban){
            	cout<<"\nBienvenido al sistema\n"<<endl;
            	break;
        	}else{
            	cout<<"Usario o contrasena equivocada\n"<<endl;
	       }
    	}
    	
    	int opc=opciones();
    	
    	if(opc==1){
            cout<<"Tu saldo actual es: "<<disp<<endl;
            array[usr][2]=disp;
		}else if(opc==2){
            cout<<"Retirar dinero: "<<endl;
            cout<<"\n";
            array[usr][2]=retirar(disp);
		}

        // escribir archivo

        archivo1.open("sudo.txt");

        for(int i=0;i<j-1;i++){
            archivo1<<array[i][0]<<",";
            archivo1<<array[i][1]<<",";
            archivo1<<array[i][2]<<"\n";
        }

        archivo1.close();

	}else{
		cout<<"Error al abrir el archivo"<<endl;
	}

    return 0;
}
