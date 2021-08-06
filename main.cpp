#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <chrono>
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
    vector <string> cant_follow; //se debe parsear;
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

vector<string> cantFollow(string s, string del = " "){
    vector<string> cFollow;
    int start = 0;
    int end = s.find(del);
    int aux = 0;
    while (end != -1) {
        cFollow.push_back(s.substr(start, end - start));
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    string aux2 = s.substr(start, end - start);
    cFollow.push_back(aux2); //cuando no calce queda vacio;
    return cFollow;
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
            
        }
        aux++;
        start = end + del.size();
        end = s.find(del, start);     
    }
    shift->cant_follow = cantFollow(s.substr(start, end - start),"|");  
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
                        
                        //TAGcout<<"Turnos por trabajador vulnerado\n";
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
        if(suma > workers[i].MaxTotalMinutes)
            { 
                //TAGcout<<"trabajador :" << i << " total sobre trabajo: " <<suma <<" \n";                     
                score =score - 10 ;
                
            }
        if(suma < workers[i].MinTotalMinutes ){ //.MaxTotalMinutes[turno-1]

                
                //TAGcout<<"trabajador :" << i << " total under trabajo: " <<suma <<" \n";  
                score =score - 10 ;
                
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
                    //cout<<"trabaja muchos turnos consecutivos\n";
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
                    //cout<<"trabajador " << i << " pocos turnos consecutivos\n";
                    score -=80;
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
    for(int i = 0; i<Cantidad_empleados; i++){
        sumOfWeekends[i] = 0;
    }
    while(index<SECTION_HORIZON)
    {
        for(int i = 0 ; i<Cantidad_empleados;i++)
        {
            if(MATRIX[i][index] != 0 || MATRIX[i][index + 1] != 0)
            {   
                
                sumOfWeekends[i] = sumOfWeekends[i] + 1;
                
                
            }
        }
        
        index+=7;
    }
    for(int i = 0 ; i<Cantidad_empleados;i++)
        {
            if(sumOfWeekends[i]>workers[i].MaxWeekends)
                    {
                        //cout<<i << " "<< index << " " << sumOfWeekends[i]  <<" dia trabajado\n";
                        score-=100*(sumOfWeekends[i]);
                    }
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
                   //cout<<"Empleado : "<<i <<" trabaja en dias libres\n";
                   score-=1000;
               }
           }
            
        }
    }
    return score;
}

int CantFollowRestriction(int** MATRIX,vector<shift> turnos,int Cantidad_empleados,int SECTION_HORIZON ){
    int score = 0;
    for(int i = 0; i<Cantidad_empleados ; i++){
        for(int j = 0; j<SECTION_HORIZON -1 ; j++){
            int presente = MATRIX[i][j] ;
            int futuro = MATRIX[i][j+1] ;
            
            if(futuro != 0 && presente !=0){
                for(int w = 0; w<turnos[presente-1].cant_follow.size(); w++){
                    string a = turnos[presente-1].cant_follow[w];
                    if(a.compare("\n") != 3){
                    
                    //cout<<a.compare("\n")<<"\n";
                    //cout<<turnos[presente-1].cant_follow[w][0];
                    //cout<<turnos[futuro-1].ShiftID<<"\n";
                    
                    //cout<<turnos[presente-1].cant_follow[w].compare(turnos[futuro-1].ShiftID);
                    
                    if(turnos[futuro-1].ShiftID[0] == turnos[presente-1].cant_follow[w][0] ){
                            //cout<<"Presente " << presente<< " " <<i << " " << j <<" no puede ser seguido por :" << turnos[futuro-1].ShiftID[0]<<"\n";
                            score -=100;
                        }
                    }
                }
            }
        }
    }

    return score;
}

void copyMatrix(int** Original, int** copia,int Cantidad_empleados,int SECTION_HORIZON){
    for(int i = 0; i<Cantidad_empleados ; i++){
        for(int j = 0; j<SECTION_HORIZON ; j++){
            copia[i][j] = Original[i][j];
            
            }
    }
}

void emptySumOfShift(int** sum_ofshift,int Cantidad_empleados,int turnos_max){
    for(int i = 0; i<Cantidad_empleados; i++){
        for(int j = 0; j<turnos_max+1;j++){
            sum_ofshift[i][j] = 0;
           
        }
    }
}

double Acceptance(double score_actual, double score_pasado,double T,double EulerConstant){

    if(score_actual > score_pasado){
        
        return 1;
    }else if(score_actual == score_pasado){
        return -1;
    }
    
    else{
        double EulerConstant = 2.718281828459045235;
        //cout<<EulerConstant<<  " Base \n";
        
        double exponent = (score_actual - score_pasado)/T;
        //cout<<exponent<<  " Exponente " << T << " : Temperatura\n";
        return pow(EulerConstant,exponent);
    }
     
}

void bestSolutionPrint(int** MATRIX,int Cantidad_empleados,int SECTION_HORIZON,vector<staff> workers,vector<shift> turnos){

    for(int i = 0 ; i<Cantidad_empleados; i++){
        string line;
        cout<<workers[i].ID << ":";
        line.append(workers[i].ID);
        line.append(":");
        for(int j = 0; j<SECTION_HORIZON ; j++){
            int t = MATRIX[i][j];
             
            if(t !=0){

                string shiftId = turnos[t-1].ShiftID;
                
                if(j + 1 ==SECTION_HORIZON){
                    cout<<" (" << j << "," << shiftId << ")"; 
                    line.append(" (");
                    line.append(j);
                    line.append(",");
                    line.append(shiftId );
                    line.append(")");

                }else{
                    cout<<" (" << j << "," << shiftId << ")";
                    line.append(" (");
                    line.append(j);
                    line.append(",");
                    line.append(shiftId );
                    line.append(")");
                }
                
            }
            
        }
        cout<<"\n";
    }

}

int main()
{
    srand((unsigned)(time(0)));
    bool copiar = false;
    int flags = 0;
    prueba.insert(prueba.begin(),2);
    /*
    staff test;
    workers.push_back(test);
    workers.push_back(new staff());
    */
    ifstream fileStream;
    string route = "nsp_instancias/instances1_24/";
    route.append("Instance1.txt");
    fileStream.open(route);
    if(fileStream.is_open())
    {

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
                        cout<<turnos.back().ShiftID<<"\n";                      
                                               
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
    int** aux_matrix       = new int*[Cantidad_empleados];
    int** movimiento       = new int*[Cantidad_empleados];
    for(int i=0; i<Cantidad_empleados; i++)
    {
        MATRIX[i]          = new int[SECTION_HORIZON];
        aux_matrix[i]      = new int[SECTION_HORIZON];
        movimiento[i]      = new int[SECTION_HORIZON]; 
        ShiftsPerWorker[i] = new int[turnos_max + 1];//turnos_max es cantidad de turnos sin contar el turno 0->no trabaja
        sum_ofshift[i]     = new int[turnos_max + 1];
    }
    //Inicializa la matriz de desicion de manera aleatoria
    initMatrix(MATRIX,Cantidad_empleados,SECTION_HORIZON,turnos_max);

    //se inicializa la matriz de cantidad de turnos
    initShiftPerWorker(ShiftsPerWorker,Cantidad_empleados,turnos_max + 1);


    copyMatrix(MATRIX,aux_matrix,Cantidad_empleados,SECTION_HORIZON);
    double score = 0;
    score = 0;
    score +=sumOfShift(MATRIX,sum_ofshift,ShiftsPerWorker,Cantidad_empleados,SECTION_HORIZON,turnos_max + 1,workers);
    score +=ShiftTimesSum(sum_ofshift,workers,Cantidad_empleados,turnos_max + 1,turnos);
    score +=maxConsecutiveShifts(MATRIX,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=minConsecutiveShifts(MATRIX,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=MaxConsecutiveWeekendWork(MATRIX,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=MustDayoff(MATRIX,libres,Cantidad_empleados,SECTION_HORIZON);
    score +=CantFollowRestriction(MATRIX,turnos,Cantidad_empleados,SECTION_HORIZON);

   

    emptySumOfShift(ShiftsPerWorker,Cantidad_empleados,turnos_max);
    double score_final = -1*pow(10,5);
    double mejor_score = -1*pow(10,5);
    double T                   = abs(score) * 10;
    double Reset_T             = abs(score) * 10;
    int Reset_max              = 0;
    int Tol                    = 15;
    double alpha               = 0.99;
    double EulerConstant = 2.718281828459045235;
    double iterations         = 1000;
    double index              = 0;
    score_final        = score;
    int estancado      = 1;
    int iter_estancado = iterations/5;
    double score_pasado;
    int i = 0;
    int  j = 0 ;
    double Maximo= -1*pow(10,5);
    while(index < iterations){
        bool flag = true;
        //cout<< "De vuelta a iterar\n";
        
        for(int i = 0; i<Cantidad_empleados; i++){
            if(flag){
                for( int  j = 0 ;j<SECTION_HORIZON ; j++){
                    int turno = aux_matrix[i][j];                    
                    if(flag){
                        
                        for(int w = 0; w<turnos.size() +1;w++){
                            
                            if(turno != w){
                                aux_matrix[i][j] = w;
                            }
                            score = 0;
                            score +=sumOfShift(aux_matrix,sum_ofshift,ShiftsPerWorker,Cantidad_empleados,SECTION_HORIZON,turnos_max + 1,workers);                        
                            score +=ShiftTimesSum(sum_ofshift,workers,Cantidad_empleados,turnos_max + 1,turnos);
                            score +=maxConsecutiveShifts(aux_matrix,workers,Cantidad_empleados,SECTION_HORIZON);
                            score +=minConsecutiveShifts(aux_matrix,workers,Cantidad_empleados,SECTION_HORIZON);
                            score +=MaxConsecutiveWeekendWork(aux_matrix,workers,Cantidad_empleados,SECTION_HORIZON);
                            score +=MustDayoff(aux_matrix,libres,Cantidad_empleados,SECTION_HORIZON);
                            score +=CantFollowRestriction(aux_matrix,turnos,Cantidad_empleados,SECTION_HORIZON);
                            
                            unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
                            default_random_engine e(seed);
                            uniform_real_distribution<double> distR(0,1);
                            double eval = pow(EulerConstant,(abs(score_pasado-score_pasado))/T);
                            double p = distR(e);
                            
                            emptySumOfShift(ShiftsPerWorker,Cantidad_empleados,turnos_max);
                            emptySumOfShift(sum_ofshift,Cantidad_empleados,turnos_max);
                      
                            double Accept =  Acceptance(score,score_final,T,EulerConstant);
                            
                            cout<<"Score actual : " <<score<< " Mejor Score : "<<score_final << " Estancado : " << estancado <<"\n";
                            score_pasado  = score;
                            
                            if( score >  score_final){
                                estancado = 0;
                                score_final = score;
                            
                                flag = false; //alguna mejora, cambio de vecindario
                                copyMatrix(aux_matrix,MATRIX,Cantidad_empleados,SECTION_HORIZON);
                                
                                cout<<"Score total: "<< score_final <<"\n";
                               
                                break;
                               
                            }else if(p<Accept && Accept != -1)
                            {
                                
                                //cout<<"Se acepta un movimiento peor\n";
                                flag = false;
                                break;
                            }
                            else{
                                
                                aux_matrix[i][j] = turno;
                            }
                        }
                    }else{
                        
                        break;
                    }
                }
            }else{
                break;
            }
        }
        if(score_final == 0){
            copyMatrix(MATRIX,movimiento,Cantidad_empleados,SECTION_HORIZON);
            Maximo = score_final;
            break;
        }
        
        if(score <=score_final){
            
            
            estancado +=1;
        }
        if(estancado > iter_estancado){
            cout<<estancado <<" estancado \n";
            Reset_max +=1;
            
            
            cout<<score_final;
            
            //index = 0;
            T = Reset_T;
            estancado = 0;
            if(Maximo < score_final){
                Maximo = score_final;
                copyMatrix(MATRIX,movimiento,Cantidad_empleados,SECTION_HORIZON);
            }
            
            score_final = -1*pow(10,5);
            initMatrix(aux_matrix,Cantidad_empleados,SECTION_HORIZON,turnos_max);
            
         
        }

        T = T*(1 -(index+1)/iterations);
        index++;
    }
    cout<<score_final<<"\n";
    cout<<Maximo<<"\n";
    for(int i  = 0; i<Cantidad_empleados; i++){
        for(int j = 0; j<SECTION_HORIZON;j ++){
            if(j + 1 ==SECTION_HORIZON){
                cout<<movimiento[i][j]<< " \n";
            }else{
                cout<<movimiento[i][j]<< " ";
            }
        }
    }
    score= 0;
    score +=sumOfShift(movimiento,sum_ofshift,ShiftsPerWorker,Cantidad_empleados,SECTION_HORIZON,turnos_max + 1,workers);                        
    score +=ShiftTimesSum(sum_ofshift,workers,Cantidad_empleados,turnos_max + 1,turnos);
    score +=maxConsecutiveShifts(movimiento,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=minConsecutiveShifts(movimiento,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=MaxConsecutiveWeekendWork(movimiento,workers,Cantidad_empleados,SECTION_HORIZON);
    score +=MustDayoff(movimiento,libres,Cantidad_empleados,SECTION_HORIZON);
    score +=CantFollowRestriction(movimiento,turnos,Cantidad_empleados,SECTION_HORIZON);

    emptySumOfShift(ShiftsPerWorker,Cantidad_empleados,turnos_max);
    emptySumOfShift(sum_ofshift,Cantidad_empleados,turnos_max);
    cout<<score<<"\n";
    bestSolutionPrint(movimiento,Cantidad_empleados,SECTION_HORIZON,workers,turnos);

    //--------------------------------------------------------------------------------------------------------------------------------//
    

    return 0 ;
}   
