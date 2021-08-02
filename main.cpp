#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


struct staff{
    string ID;
    string MaxShifts;
    int MaxTotalMinutes;
    int MinTotalMinutes;
    int MaxConsecutiveShifts;
    int MinConsecutiveShifts;
    int MinConsecutiveDaysOff;
    int MaxWeekends;


};

struct shift{
    string ShiftID;
    int mins;
    string cant_follow; //se debe parsear;
};

struct days_off{
    string EmployeeID;
    int DayIndexes;
};

struct shift_on_request{
    string EmployeeID;
    int Day;
    string ShiftID;
    int Weight;

};

struct shift_off_request
{
    string EmployeeID;
    int Day;
    string ShiftID;
    int Weight;
};

struct cover
{
    int Day;
    string ShiftID;
    int Requirement;
    int Weight_for_under;
    int Weight_for_over;
};




//Flags to parse .txt
string sections[7] = {"SECTION_HORIZON",
                    "SECTION_SHIFTS",
                    "SECTION_STAFF",
                    "SECTION_DAYS_OFF",
                    "SECTION_SHIFT_ON_REQUESTS",
                    "SECTION_SHIFT_OFF_REQUESTS",
                    "SECTION_COVER"};

bool flag[7] = {false,
                false,
                false,
                false,
                false,
                false,
                false};

    

//Variables Globales

int SECTION_HORIZON = 0;
vector<staff> workers;
vector<shift> turnos;
vector<days_off> libres;
vector<shift_on_request> on_request;
vector<shift_off_request> off_request;
vector<cover> cubrir;
vector<int> prueba;

void tokenize(string s, string del = " ")
{
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    
    while (end != -1) {
        cout<<aux<<'\n';
        cout << s.substr(start, end - start) << endl;
        start = end + del.size();
        end = s.find(del, start);
        aux++;
    }
    cout<<aux<<'\n';
    cout << s.substr(start, end - start);
}

void addShift(shift* shift,string s, string del = " "){
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            shift->ShiftID = s.substr(start, end - start);
        }
        else if(aux == 1){
            shift->mins = stoi(s.substr(start, end - start));
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    shift->cant_follow = s.substr(start, end - start);  
    turnos.push_back(*shift);


}

void addStaff(staff* staff,string s, string del = " "){
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            staff->ID = s.substr(start, end - start);
        }
        else if(aux == 1){
            staff->MaxShifts = s.substr(start, end - start);
        }
        else if(aux == 2){
            staff->MaxTotalMinutes = stoi(s.substr(start, end - start));
        }
        else if(aux == 3){
            staff->MinTotalMinutes = stoi(s.substr(start, end - start));
            
        }
        else if(aux == 4){
            staff->MaxConsecutiveShifts = stoi(s.substr(start, end - start));
        }
        else if(aux == 5){
            staff->MinConsecutiveShifts= stoi(s.substr(start, end - start));
            
        }
        else if(aux == 6){
            staff->MinConsecutiveDaysOff = stoi(s.substr(start, end - start));
            
        }

        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    //shift->cant_follow = s.substr(start, end - start); 
    staff->MaxWeekends = stoi(s.substr(start, end - start));
    workers.push_back(*staff);


}

void addDaysOff(days_off* section,string s, string del = "")
{
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            section->EmployeeID = s.substr(start, end - start);
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    section->DayIndexes = stoi(s.substr(start, end - start));  
    libres.push_back(*section);
}

void addShiftOnRequest(shift_on_request* section,string s, string del = "")

{
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            section->EmployeeID = s.substr(start, end - start);
        }
        else if(aux == 1){
            section->Day= stoi(s.substr(start, end - start));
        }
        else if(aux == 2){
            section->ShiftID = s.substr(start, end - start);
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    section->Weight = stoi(s.substr(start, end - start));  
    on_request.push_back(*section);
}

void addShiftOffRequest(shift_off_request* section,string s, string del = "")
{
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            section->EmployeeID = s.substr(start, end - start);
        }
        else if(aux == 1){
            section->Day= stoi(s.substr(start, end - start));
        }
        else if(aux == 2){
            section->ShiftID = s.substr(start, end - start);
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    section->Weight = stoi(s.substr(start, end - start));  
    off_request.push_back(*section);
}
void addCover(cover* section,string s, string del = "")
{
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            section->Day = stoi(s.substr(start, end - start));
        }
        else if(aux == 1){
            section->ShiftID= s.substr(start, end - start);
        }
        else if(aux == 2){
            section->Requirement = stoi(s.substr(start, end - start));
        }
        else if(aux == 3){
            section->Weight_for_under = stoi(s.substr(start, end - start));
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    section->Weight_for_over = stoi(s.substr(start, end - start));  
    cubrir.push_back(*section);
}

int random_num(int start, int end) 
{
    int range = (end - start) + 1;
    int random_int = start + (rand()%range);
    return random_int;
}

void initMatrix(int** MATRIX, int row,int SECTION_HORIZON)
{
    for(int i = 0; i<row;i++){
        for(int j = 0; j<SECTION_HORIZON ; j++){
            int randNum = random_num(0,1);
            
            MATRIX[i][j] = randNum;
            if(j + 1 == SECTION_HORIZON){
                cout<<randNum<<"\n";
            }
            else{
                cout<<randNum<<" ";
            }            
        }
    }
}

void initShiftPerWorker(int** ShiftsPerWorker , int Cantidad_empleados,int turnos_max){
    for(int i = 0; i< Cantidad_empleados ; i++){
        for(int j = 0; j< turnos_max ; j++){
            ShiftsPerWorker[i][j] = 0;
        }
    }

}

void sumOfShift(int** MATRIX, int** ShiftsPerWorker,int row, int SECTION_HORIZON)
{
    cout<<row<<" Cantidad de empleados "<<"\n";
    for(int i = 0; i<row ; i++)
    {
        for(int j = 0 ; j<SECTION_HORIZON ; j ++)
        {
            int tipo_turno = MATRIX[i][j];
            
            if(tipo_turno != 0){
                
                ShiftsPerWorker[i][tipo_turno] = ShiftsPerWorker[i][tipo_turno] + 1;
            } 
            if(j +1 == SECTION_HORIZON){
                cout<<ShiftsPerWorker[i][1]<<"\n";
            }
            

        }
        
    }
    
}








int main()
{
    bool copiar = false;
    int flags = 0;
    prueba.insert(prueba.begin(),2);
    /*
    staff test;
    workers.push_back(test);
    workers.push_back(new staff());
    */
    ifstream fileStream;
    fileStream.open("nsp_instancias/instances1_24/Instance1.txt");
    if(fileStream.is_open()){

        cout<<"Abierto\n";
        string line;
        while(getline(fileStream,line)){
            line.append("\n");
            if(line[0] != '#'){
                if(line[1] != '\n' && !copiar){    
                    for(int i = flags; i<7 ; i++){
                        if(line.compare(sections[i]) == 2){
                        flags = i;
                        copiar = true; //me situa en el .txt
                            break; 
                        } 
                    }

                }else if(line[1] != '\n' && copiar){
                    switch (flags)
                    {
                    case 0:
                    
                        SECTION_HORIZON = stoi(line);

                    break;
                    case 1:
                    {
                        shift* aux = new shift();                  
                        //tokenize(line,",");
                        addShift(aux,line,",");
                        cout<<turnos.size()<<"\n";                      
                                               
                    }
                    break;
                    case 2:
                    {
                        staff* aux = new staff();
                        //tokenize(line,",");
                        addStaff(aux,line,",");
                        
                    }
                    
                    break;
                    
                    case 3:
                    {
                        days_off* aux = new  days_off();
                        addDaysOff(aux,line,",");
                    }

                    break;

                    case 4:
                    {
                        shift_on_request* aux = new  shift_on_request();
                        addShiftOnRequest(aux,line,",");
                    }

                    break;
                    case 5:
                    {
                        shift_off_request* aux = new  shift_off_request();
                        addShiftOffRequest(aux,line,",");
                    }

                    break;

                    case 6:
                    {
                        cover* aux = new  cover();
                        addCover(aux,line,",");
                    }

                    break;
                    
                    default:
                        break;
                    }
                    

                }else if(line[1] == '\n' && copiar){
                    copiar = false;
                }
                
            }
                    
        }
        /*
        vector<days_off> libres;
        vector<shift_on_request> on_request;
        vector<shift_off_request> off_request;
        vector<cover> cubrir;
        */
        
        fileStream.close();
    
    }else{
        cout<<"Cerrado";
    }
    int turnos_max = 1;//cantidad maxima de turnos
    int turnos_min = 0;//cantidad minima de turnos
    int Cantidad_empleados = workers.size();
    int randNum = rand()%(turnos_max-turnos_min + 1) + turnos_min;
    //Se inicializa la matriz de decision
    //se inicializa la matriz de turnos por worker

    int** MATRIX          = new int*[Cantidad_empleados];
    int** ShiftsPerWorker = new int*[Cantidad_empleados];
    for(int i=0; i<Cantidad_empleados; i++)
    {
        MATRIX[i]          = new int[SECTION_HORIZON];
        ShiftsPerWorker[i] = new int[turnos_max + 1];//en vez de 1, cantidad de turnos
    }
    //Inicializa la matriz de desicion de manera aleatoria
    initMatrix(MATRIX,Cantidad_empleados,SECTION_HORIZON);

    //se inicializa la matriz de cantidad de turnos
    initShiftPerWorker(ShiftsPerWorker,Cantidad_empleados,turnos_max + 1);

    //re inicializar en cada iteracion
    //while(iterations < MaxIterations)

    sumOfShift(MATRIX,ShiftsPerWorker,Cantidad_empleados,SECTION_HORIZON);

}
