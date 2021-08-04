#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


struct staff{
    string ID;
    vector<string> MaxShifts;// no hay turno 0 en esta representacion
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
    vector<string> DayIndexes;
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

void addShift(shift* shift,string s, string del = " ")
{
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        if(aux == 0){
            shift->ShiftID = s.substr(start, end - start);
        }
        else if(aux == 1){
            shift->mins = stoi(s.substr(start, end - start));//tokenizar
            cout<<shift->mins<<"\n";
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    shift->cant_follow = s.substr(start, end - start);  
    turnos.push_back(*shift);


}

string parseShift(string s,string del = " ")
{
    string aux2;
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {

        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    aux2 = s.substr(start, end - start);
    return aux2;
}

vector<string> maxshift(string s, string del = " "){
    vector<string> shiftType;
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        
        string aux2 =  parseShift(s.substr(start, end - start),"=");
        shiftType.push_back(aux2);
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    string aux2 =  parseShift(s.substr(start, end - start),"=");
    shiftType.push_back(aux2);
    return shiftType;
    

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
            staff->MaxShifts = maxshift(s.substr(start, end - start),"|"); //sirve para un turno
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

vector<string> DayIndexesTokenizer(string s,string del = "")
{
    vector<string> DaysOff;
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        DaysOff.push_back(s.substr(start, end - start));
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    DaysOff.push_back(s.substr(start, end - start));
    return DaysOff;

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
        else{
            string we = s.substr(start, end - start);
            
            (section->DayIndexes).push_back(we);
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    string aux2  = s.substr(start, end - start);
 
    (section->DayIndexes).push_back(aux2); 
    
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

void initMatrix(int** MATRIX, int cantidad_empleados,int SECTION_HORIZON,int turnos_max)
{
    for(int i = 0; i<cantidad_empleados;i++){
        for(int j = 0; j<SECTION_HORIZON ; j++){
            int randNum = random_num(0,turnos_max);
            
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

int sumOfShift(int** MATRIX, int** sum_ofshift,int** ShiftsPerWorker,int cantidad_empleados, int SECTION_HORIZON,int turnos_max,vector<staff> shifts)
{
    int score = 0;
    cout<<cantidad_empleados<<" Cantidad de empleados "<<"\n";
    for(int i = 0; i<cantidad_empleados ; i++)
    {
        for(int j = 0 ; j<SECTION_HORIZON ; j ++)
        {
            int tipo_turno = MATRIX[i][j]; // tipo de turno;
            
            if(tipo_turno != 0){
                ShiftsPerWorker[i][tipo_turno] = ShiftsPerWorker[i][tipo_turno] + 1;
            } 
            if(j +1 == SECTION_HORIZON){ //sumamos todos los turnos de un worker
                for(int turno = 1; turno < turnos_max ; turno++){  //parte en 1 porque el turno 0 no se cuenta


                //1.MaxShift esta definida sin el turno 0(se puede arreglar para mayor consistencia)
                //2.turnos_maximos es la cantidad de turnos maximos por worker
               
                    int turnos_maximos = stoi(workers[i].MaxShifts[turno-1]); 
                    sum_ofshift[i][turno] = ShiftsPerWorker[i][turno];

                    
                    if(ShiftsPerWorker[i][turno] > turnos_maximos){
                        
                        score =score - 10;
                        
                    }else{
                        
                    }
                    
                }
                 }
            }
        }
    return score;   
    
}

int ShiftTimesSum(int** sum_ofshift, vector<staff> workers,int Cantidad_empleados,int turnos_max,vector<shift> shifts){
    int score = 0;
    for(int i = 0; i<Cantidad_empleados;i++){
        int suma = 0;
        for(int turno = 1; turno < turnos_max ; turno++){  //parte en 1 porque el turno 0 no se cuenta 
            
            suma = suma + sum_ofshift[i][turno]*shifts[turno-1].mins;

            
        }
        if(suma > workers[i].MaxTotalMinutes )
            {   
                
                
                score =score - 10;
                
            }
        if(suma < workers[i].MinTotalMinutes ){ //.MaxTotalMinutes[turno-1]

                
                
                score -=10;
                
            }
    }
    return score;
}

int maxConsecutiveShifts(int** MATRIX,vector<staff> workers,int Cantidad_empleados,int SECTION_HORIZON){
    int score = 0;
    for(int i = 0; i<Cantidad_empleados; i++){
        int aux = 0;
        for(int j = 0; j<SECTION_HORIZON ; j++){
            if(MATRIX[i][j] != 0 ){
                aux++;
                if(aux > workers[i].MaxConsecutiveShifts){
                    score -=10;
                }
            }else{
                aux = 0;
            }

            
        }
    }
    return score;
}

int minConsecutiveShifts(int** MATRIX,vector<staff> workers,int Cantidad_empleados,int SECTION_HORIZON){
    int score = 0;
    for(int i = 0; i<Cantidad_empleados; i++){
        int aux = 0;
        for(int j = 0; j<SECTION_HORIZON ; j++){
            if(MATRIX[i][j] == 0 )
            {
                aux++;
                if(aux > workers[i].MinConsecutiveShifts)
                {
                    score -=10;
                }
            }else{
                aux = 0;
            } 
        }
    }
    return score;
}

int MaxConsecutiveWeekendWork(int** MATRIX,vector<staff> workers,int Cantidad_empleados,int SECTION_HORIZON ){
    int index = 5;
    int score = 0;
    int* sumOfWeekends = new int[Cantidad_empleados];
    while(index<SECTION_HORIZON)
    {
        for(int i = 0 ; i<Cantidad_empleados;i++)
        {
            if(MATRIX[i][index] != 0 || MATRIX[i][index + 1] != 0)
            {
                sumOfWeekends[i] = sumOfWeekends[i] + 1;
                
            }
        }
        for(int i = 0 ; i<Cantidad_empleados;i++)
        {
            if(sumOfWeekends[i]>workers[i].MaxWeekends)
                    {
                        score-=10;
                    }
        }
        index+=5;
    }
    return score;

}

int MustDayoff(int** MATRIX, vector<days_off> libres,int Cantidad_empleados,int SECTION_HORIZON){
    int score = 0;
    for(int i = 0; i<Cantidad_empleados; i++){
        for(int j = 0; j<SECTION_HORIZON ; j++){
           for(int w = 0 ; w<libres[i].DayIndexes.size(); w++){
               int aux = stoi(libres[i].DayIndexes[w]);
               if(MATRIX[i][j] != 0 && j == aux){
                   
                   score-=10;

               }
           }
            
        }
    }
    return score;
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
    if(fileStream.is_open())
    {

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


    int turnos_max = turnos.size();//cantidad de diferentes turfor(int turno = 1; turno < turnos_max ; turno++)nos
    cout<<"TURNOS MAX: "<<turnos_max<<"\n";
    int turnos_min = 0;//turno 0 = no trabaja
    int Cantidad_empleados = workers.size();
    
    int randNum = rand()%((turnos_max - turnos_min) + 1) + turnos_min;
    //Se inicializa la matriz de decision
    //se inicializa la matriz de turnos por worker

    int** MATRIX           = new int*[Cantidad_empleados];
    int** ShiftsPerWorker  = new int*[Cantidad_empleados];
    int** sum_ofshift      = new int*[Cantidad_empleados]; 
    for(int i=0; i<Cantidad_empleados; i++)
    {
        MATRIX[i]          = new int[SECTION_HORIZON];
        ShiftsPerWorker[i] = new int[turnos_max + 1];//turnos_max es cantidad de turnos sin contar el turno 0->no trabaja
        sum_ofshift[i]     = new int[turnos_max + 1];
    }
    //Inicializa la matriz de desicion de manera aleatoria
    initMatrix(MATRIX,Cantidad_empleados,SECTION_HORIZON,turnos_max);

    //se inicializa la matriz de cantidad de turnos
    initShiftPerWorker(ShiftsPerWorker,Cantidad_empleados,turnos_max + 1);

    // se define score inicial
    int score = 0;
        //re inicializar en cada iteracion
        //while(iterations < MaxIterations)
    
    score +=sumOfShift(MATRIX,sum_ofshift,ShiftsPerWorker,Cantidad_empleados,SECTION_HORIZON,turnos_max + 1,workers);
    score +=ShiftTimesSum(sum_ofshift,workers,Cantidad_empleados,turnos_max + 1,turnos);
    score +=maxConsecutiveShifts(MATRIX,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=minConsecutiveShifts(MATRIX,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=MaxConsecutiveWeekendWork(MATRIX,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=MustDayoff(MATRIX,libres,Cantidad_empleados,SECTION_HORIZON);

    cout<<"Score total: "<< score <<"\n";

}   
