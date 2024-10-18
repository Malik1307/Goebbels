#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>
#include <chrono>
#include <ctime>
#include<conio.h>
using namespace std;
int Max_Current_Users_Size = 80, Max_Rides_Size_Per_Person = 180;
int UsersCount = 0;
int Index_Of_Target_User;
int nsubscrip = 2;

int start_line = -1;
int end_line = -1;
int stations;
string zones[11][11] = {
    {"al_shohadaa", "ataba", "naguib", "saad", "zaghloul", "orabi", "nasser",
     "opera", "sadat"},

    {"al_sayyeda_zeinab", "el_malek_el_saleh", "mar_girgis", "el_zahraa",
     "dar_el_salam"},

    {"dokki", "bohooth", "cairo_university", "faisal", "giza",
     "omm_el_misryeen", "sakiat_mekki", "el_mounib"},

    {"al_ahram", "koleyet_el_banat", "cairo_stadium", "fair_zone", "abbassia",
     "abdou_pasha", "el_geish", "bab_el_shaaria"},

    {"saray_el_qobba", "hammamat_el_qobba", "kobri_el_qobba",
     "manshiet_el_sadr", "el_demerdash", "ghamra"},

    {"shobra_el_kheima", "koliet_el_zeraa", "mezallat", "khalafawy",
     "sainte_teresa", "road_elfarag", "massara"},

    {"hadayeq_el_maadi", "maadi", "thakanat_el_maadi", "tora_el_balad",
     "kozzika", "tora_el_asmant"},

    {"new_el_marg", "el_marg", "ezbet_el_nakhl", "ain_shams", "el_matareyya",
     "helmeyet_el_zaitoun", "hadayeq_el_zaitoun"},

    {"el_maasara", "hadayeq_helwan", "wadi_hof", "helwan_university",
     "ain_helwan", "helwan"},

    {"haroun", "heliopolis", "alf_masken", "el_shams_club", "el_nozha",
     "hesham_barakat", "qubaa", "omar_ibn_el_khattab", "haykestep",
     "adly_mansour"},

    {"maspero", "safaa_hijazy", "kit_kat", "sudan", "imbaba", "el_bohy",
     "el_qawmia", "ring_road", "rod_elfarg_corridor"} };

vector<vector<string>> lines{
    /*1st line*/ {"helwan",
                  "ain_helwan",
                  "helwan_university",
                  "wadi_hof",
                  "hadayeq_helwan",
                  "el_maasara",
                  "tora_el_asmant",
                  "kozzika",
                  "tora_el_balad",
                  "thakanat_el_maadi",
                  "maadi",
                  "hadayeq_el_maadi",
                  "dar_el_salam",
                  "el_zahraa",
                  "mar_girgis",
                  "el_malek_el_saleh",
                  "al_sayyeda_zeinab",
                  "saad",
                  "sadat",
                  "nasser",
                  "orabi",
                  "al_shohadaa",
                  "ghamra",
                  "el_demerdash",
                  "manshiet_el_sadr",
                  "kobri_el_qobba",
                  "hammamat_el_qobba",
                  "saray_el_qobba",
                  "hadayeq_el_zaitoun",
                  "helmeyet_el_zaitoun",
                  "el_matareyya",
                  "ain_shams",
                  "ezbet_el_nakhl",
                  "el_marg",
                  "new_el_marg"},

    /*2nd line*/ {"el_mounib",       "sakiat_mekki",   "omm_el_misryeen",
                  "giza",           "faisal",         "cairo_university",
                  "bohooth",        "dokki",          "opera",
                  "sadat",          "naguib",         "ataba",
                  "al_shohadaa",     "massara",        "road_elfarag",
                  "sainte_teresa",  "khalafawy",      "mezallat",
                  "koliet_el_zeraa", "shobra_el_kheima"},

    /*3rd line*/ {"adly_mansour",
                  "haykestep",
                  "omar_ibn_el_khattab",
                  "qubaa",
                  "hesham_barakat",
                  "el_nozha",
                  "el_shams_club",
                  "alf_masken",
                  "heliopolis",
                  "haroun",
                  "al_ahram",
                  "koleyet_el_banat",
                  "cairo_stadium",
                  "fair_zone",
                  "abbassia",
                  "abdou_pasha",
                  "el_geish",
                  "bab_el_shaaria",
                  "ataba",
                  "nasser",
                  "maspero",
                  "safaa_hijazy",
                  "kit_kat",
                  "sudan",
                  "imbaba",
                  "el_bohy",
                  "el_qawmia",
                  "ring_road",
                  "rod_elfarg_corridor"} };

void Display_Stations() {
    cout << setw(33) << left << "line 1:" << setw(33) << left << "line 2:"
    << "line 3:" << endl;

int maxStations = 0;
for (const auto& line : lines) {
    if (line.size() > maxStations)
        maxStations = line.size();
}

for (int j = 0; j < maxStations; ++j) {
    for (int i = 0; i < 3; ++i) {
        if (j < lines[i].size()) {
            cout << setw(2) << right << j + 1 << ')' << setw(30) << left
                << lines[i][j];
        }
        else {
            cout << setw(33) << left << "";
        }
    }
    cout << endl;
}
}

struct Date {
    int day;
    int month;
    int year;
    int hour;
    int minute;
};

struct Users {
    string First_Name;
    string Last_Name;
    int ID;
    string Email;
    bool Admin = 0;
    string Password;
    string Phone_Number;
    float Balance;
    int Rides_Count = 0;
    int stations;
};

struct Subscriptions {
    Date Start_Date;
    Date End_Date;
    bool have_ticket = 0;
    string Subscription_Type = "Isn't Available";
    int Subscription_Period;
    int Current_Supscripition_Value;
    int num_stations; //عدد محطات كل رحله بشراء تذكره
    int Remaining_Trips = 0;
    int current_zone;
    string sub_stations[35] = {};
    int Wallet = 0;
};

struct Rides {

    Date CheckInDate;
    Date CheckOutDate;
    int Ride_ID;
    string CheckInStation; // Lama Nest5m El Map Hykoon Ashal N3raf El Ma7ta k int
    string CheckOutStation;
    int Trip_Time;
    string Type = "";
};
struct admin_subsc {
    string name;
    int prices[4][3]{};
    // first dimnestion for nzones
    // second one for months
    // prices[0][0]refers to zone 1 at 1month
};
struct Accounts {
    Users AccUser;
    Subscriptions AccSub;
    vector<Rides> Ride4User;
};

Accounts* UserAccounts = new Accounts[Max_Current_Users_Size];


Date On_Time() { // no errors
    Date currentTime;

    auto now = chrono::system_clock::now();
    time_t nowTime = chrono::system_clock::to_time_t(now);
    struct tm* nowLocal = localtime(&nowTime);

    currentTime.day = nowLocal->tm_mday;
    currentTime.month = nowLocal->tm_mon + 1;
    currentTime.year = nowLocal->tm_year + 1900;
    currentTime.hour = nowLocal->tm_hour;
    currentTime.minute = nowLocal->tm_min;

    return currentTime;
}
  int check_enter_choice(int nlast_choice, bool add_exit_choice) {
    if (add_exit_choice) {
        cout << nlast_choice + 1 << ") "
    << "Return" << endl;
    }
    int choice;
    cin >> choice;
    if (choice == nlast_choice + 1) {
        return -1; // if he choose to exit the func
    }
    while (choice < 1 || choice > nlast_choice) {
        cout << "Please Enter a valid input: ";
        cin >> choice;
    }
    return choice;
}
void initializeSubscriptions(admin_subsc* subscr_admin) {
    // Initialize Public subscription
    subscr_admin[0].name = "Public";
    subscr_admin[0].prices[0][0] = 230;
    subscr_admin[0].prices[0][1] = 625;
    subscr_admin[0].prices[0][2] = 1500;
    subscr_admin[0].prices[1][0] = 290;
    subscr_admin[0].prices[1][1] = 790;
    subscr_admin[0].prices[1][2] = 2500;
    subscr_admin[0].prices[2][0] = 340;
    subscr_admin[0].prices[2][1] = 1000;
    subscr_admin[0].prices[2][2] = 3500;
    subscr_admin[0].prices[3][0] = 450;
    subscr_admin[0].prices[3][1] = 1250;
    subscr_admin[0].prices[3][2] = 4500;

    // Initialize Student subscription
    subscr_admin[1].name = "Student";
    subscr_admin[1].prices[0][1] = 33;
    subscr_admin[1].prices[1][1] = 41;
    subscr_admin[1].prices[2][1] = 50;
    subscr_admin[1].prices[3][1] = 65;

    // Update the number of existing subscriptions
    nsubscrip = 2; // There are two existing subscriptions: Public and Student
}

// to enter a valid choice and return it

bool display_menue_again(int choice, int end) {
    char edit_again;
    if (choice >= 1 && choice <= end) {
        cout << "Do you want to do any thing else [Y/N]?" << endl;
        cin >> edit_again;

        while (edit_again != 'Y' && edit_again != 'y' && edit_again != 'N' &&
            edit_again != 'n') {
            cout << "Please enter a valid input: ";
            cin >> edit_again;
        }

        if (edit_again == 'y' || edit_again == 'Y')
            return 1;
        else
            return 0;
    }
    return 0;
}

// ############################ Start Build  , Edit and Delete subscriptions
// FUNCTION for Admin ######################

// ***************************** End of subscription functions for Admin
// ************************************

// ############################ Start of Stations managment for Admin (add ,
// delete , edit )Station ###############

// **************************************   End OF Station managment for admin
// ******************************

// ####################################  start of print Users For Admin
// #######################

// **************************************   End OF edit users accounts for admin
// ******************************

// ####################################  start of print ride logs For Admin
// #######################
void Display_ride_logs() {
    cout << "All Ride Logs " << endl;
    cout << endl;
    for (int i = 0; i < UsersCount; i++) {
        if (i)
            cout << "****************************" << endl;
        cout << i + 1 << " User: " << UserAccounts[i].AccUser.First_Name << " "
            << UserAccounts[i].AccUser.ID << endl;
        for (int k = 0; k < UserAccounts[i].Ride4User.size(); k++) {
            cout << "Trip " << k + 1 << endl;
            cout << "\tDate: " << UserAccounts[i].Ride4User[k].CheckInDate.day << "/"
                << UserAccounts[i].Ride4User[k].CheckInDate.month << "/"
                << UserAccounts[i].Ride4User[k].CheckInDate.year << endl;
            cout << "\tTime: " << UserAccounts[i].Ride4User[k].CheckInDate.hour << ":"
                << UserAccounts[i].Ride4User[k].CheckInDate.minute << endl;
            cout << "\tStart location: "
                << UserAccounts[i].Ride4User[k].CheckInStation << endl;
            cout << "\tEnd location: " << UserAccounts[i].Ride4User[k].CheckOutStation
                << endl;
            cout << "\tduration: " << UserAccounts[i].Ride4User[k].Trip_Time;

            cout << "\t ride type"<<UserAccounts[Index_Of_Target_User].Ride4User[k].Type;
        }
    }
}




void register_subscription_stations_with_exchanging(
    string valid_stations[], string&exchang, int start_line, int start_station,
    int end_line, int end_station, string checkout_station) {
    int Index_Start_Line = start_line - 1;
    int Index_Start_Station = start_station - 1;
    int Index_End_Line = end_line - 1;
    int Index_End_Station = end_station - 1;
    int exchang_s = -1; // تحديد قيمة افتراضية
    int exchang_e = -1; // تحديد قيمة افتراضية

    int Valid = 0;

    //ايجاد رقم محطة التبادل في ال startline

    for (int Index_exchang_s = 0; Index_exchang_s < 35; Index_exchang_s++) {
        if (lines[Index_Start_Line][Index_exchang_s] == exchang) {
            exchang_s = Index_exchang_s;
            break;
        }
    }

    //ايجاد رقم محطة التبادل في ال endline
    for (int Index_exchang_e = 0; Index_exchang_e < 35; Index_exchang_e++) {
        if (lines[Index_End_Line][Index_exchang_e] == exchang) {
            exchang_e = Index_exchang_e;
            break;
        }
    }

    if (exchang_s != -1 && exchang_e != -1) {
        do {
            valid_stations[Valid] = lines[Index_Start_Line][Index_Start_Station];

            if (exchang_s > Index_Start_Station)
                Index_Start_Station++;

            else if (exchang_s < Index_Start_Station)
                Index_Start_Station--;

            Valid++;
        } while (lines[Index_Start_Line][Index_Start_Station] != exchang);

        int x = exchang_e;
        valid_stations[Valid] = lines[Index_End_Line][x];
        do {

            if (Index_End_Station > exchang_e)
                x++;
            else if (Index_End_Station < exchang_e)
                x--;
            else
                break;

            Valid++;
            valid_stations[Valid] = lines[Index_End_Line][x];

        } while (lines[Index_End_Line][x] != checkout_station);
        if (exchang == "al_shohadaa") {
            valid_stations[++Valid] = "ataba";
            valid_stations[++Valid] = "naguib";
            valid_stations[++Valid] = "nasser";
            valid_stations[++Valid] = "orabi";
        }
    }

  else
    {
  return ;

    }




    }
void register_subscription_stations_without_exchanging(string valid_stations[],int start_station,int end_station,int start_line){
    int Index_Start_Line = start_line - 1;
    int Index_Start_Station = start_station - 1;
    int Index_End_Station = end_station - 1;
    int Valid = 0;

    do {
        valid_stations[Valid] = lines[Index_Start_Line][Index_Start_Station];

        Valid++;

        if (Index_Start_Station > Index_End_Station)
            Index_Start_Station--;
        else if (Index_Start_Station < Index_End_Station)
            Index_Start_Station++;

        valid_stations[Valid] = lines[Index_Start_Line][Index_Start_Station];

    } while (Index_Start_Station != Index_End_Station);
}

bool check_station_in_the_subscribtion(string valid_stations[35],
    string station) {
    for (int i = 0; i < 35; i++)
        if (station == valid_stations[i])
            return 1;


    return 0;
}

int Passed_Stations(int Beginning_Line, int Beginning_Station, int Ending_Line,
    int Ending_Station) {
    int UPassed_Stations=0;
    for (int x = 0; x < 2; ++x) {

        if (Beginning_Line == Ending_Line) {
            UPassed_Stations = abs(Beginning_Station - Ending_Station);
            break;
        }

        else if (Beginning_Line == 1 && Ending_Line == 3) {
            UPassed_Stations = abs(20 - Beginning_Station) + abs(Ending_Station - 20);
            break;

        }

        else if (Beginning_Line == 2 && Ending_Line == 3) {
            UPassed_Stations = abs(12 - Beginning_Station) + abs(Ending_Station - 19);
            break;

        }

        else if (Beginning_Line == 1 && Ending_Line == 2) {
            int Shohdaa = abs(Beginning_Station - 22) + abs(Ending_Station - 13);
            int Sadat = abs(Beginning_Station - 19) + abs(Ending_Station - 10);
            UPassed_Stations = Shohdaa > Sadat ? Sadat : Shohdaa;
            break;

        }

        else {
            swap(Beginning_Line, Ending_Line);
            swap(Beginning_Station, Ending_Station);
        }
    }

    return UPassed_Stations;
}


bool check_balance(int money, int Wallet = 0) {
    if ((money + Wallet) > UserAccounts[Index_Of_Target_User].AccUser.Balance) {
        return 0;
    }
    UserAccounts[Index_Of_Target_User].AccUser.Balance -= (money + Wallet);
    return 1;
}
bool charge_wallet(int charge_money) {


    if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type != "Wallet") {
        if (!check_balance(charge_money, 25))
            return 0;
        UserAccounts[Index_Of_Target_User].AccSub.Wallet += charge_money;
        return 1;


    }

    if (!check_balance(charge_money))
        return 0;

    UserAccounts[Index_Of_Target_User].AccSub.Wallet += charge_money;
    return 1;
}

int Random_ID_Generate(int &ID) {
    ID = 1 + (rand() % 1000);
    for (int i = 0; i < UsersCount; i++)
        if (ID == UserAccounts[i].AccUser.ID) {
            ID = 1 + (rand() % 1000);
            i = -1;
        }

    return ID;
}

int TripTime(int stations) {
   return stations *2;

}

int How_Many_Zones(int Beginning_Line, int Beginning_Station, int Ending_Line,
    int Ending_Station) {

int s = -3, d = -3;
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (zones[i][j] == lines[Beginning_Line - 1][Beginning_Station - 1])
				s = i;
			if (zones[i][j] == lines[Ending_Line - 1][Ending_Station - 1])
				d = i;
		}
	}
	int zone;
	for (int x = 0; x < 2; ++x)
	{
		if (s == d)
			zone = 1;
		else if ((s == 7 && d == 8) || (s == 8 && d == 9))
			zone = 6;
		else if ((s == 8 && (d == 2 || d == 3 || d == 4 || d == 5)) || s == 8 && d == 10 || s == 7 && d == 9 || (s == 6 && (d == 7 || d == 9)))
			zone = 5;
		else if (s == 10 && (d == 6 || d == 7 || d == 9) || s == 0 && d == 8 || s == 1 && (d == 7 || d == 9) || s == 2 && (d == 6 || d == 7 || d == 9) || s == 3 && (d == 6 || d == 7) || s == 4 && (d == 6 || d == 9) || s == 5 && (d == 6 || d == 7 || d == 9))
			zone = 4 ;
		else if (s == 10 && (d == 1 || d == 2 || d == 3 || d == 4 || d == 5) || s == 0 && (d == 6 || d == 7 || d == 9) || s == 1 && (d == 2 || d == 3 || d == 4 || d == 5 || d == 8) || s == 3 && (d == 4 || d == 5) || s == 4 && d == 5)
			zone = 3 ;
		else if (s == 6 && d == 8 || s == 4 && d == 7 || s == 3 && d == 9 || s == 1 && d == 6 || s == 0 && (d == 1 || d == 2 || d == 3 || d == 4 || d == 5 || d == 10))
			zone = 2 ;
		else
			swap(s, d);
	}
    return zone;
}
//bool isFileEmpty(const string& filename) {
//    ifstream file(filename);
//    return file.peek() == ifstream::traits_type::eof();
//}
//
//void User_Data_From_File() {
//    fstream From_File("User.txt", ios::in);
//
//    if (!From_File.is_open()) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//    int i = 0;
//    while (i < Max_Current_Users_Size &&
//        From_File >> UserAccounts[i].AccUser.First_Name) {
//        From_File >> UserAccounts[i].AccUser.Last_Name;
//        From_File >> UserAccounts[i].AccUser.Email;
//        From_File >> UserAccounts[i].AccUser.Password;
//        From_File >> UserAccounts[i].AccUser.Phone_Number;
//        From_File >> UserAccounts[i].AccUser.ID >> UserAccounts[i].AccUser.Balance;
//        i++;
//    }
//    UsersCount = i; // Done
//
//    From_File.close();
//}
//void User_Data_To_File() {
//    fstream To_File("User.txt", ios::out | ios::app);
//
//    if (!To_File.is_open()) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//    for (int i = 0; i < UsersCount; ++i)
//        To_File << UserAccounts[i].AccUser.First_Name << " "
//        << UserAccounts[i].AccUser.ID << " "
//        << UserAccounts[i].AccUser.Email << " "
//        << UserAccounts[i].AccUser.Password << " "
//        << UserAccounts[i].AccUser.Phone_Number << " "
//        << UserAccounts[i].AccUser.Balance << endl;
//
//    To_File.close();
//}
//
//void Rides_Data_From_File() {
//    Rides Temp;
//    fstream From_File("Rides.txt", ios::in);
//    if (!From_File) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//    int i = 0;
//    while (i < Max_Current_Users_Size && !From_File.eof()) {
//        for (int j = 0; j < UserAccounts->AccUser.Rides_Count; j++) {
//            UserAccounts->Ride4User.push_back(Temp);
//            From_File >> UserAccounts[i].Ride4User[j].Ride_ID;
//            From_File >> UserAccounts[i].Ride4User[j].CheckInStation;
//            From_File >> UserAccounts[i].Ride4User[j].CheckOutStation;
//            From_File >> UserAccounts[i].Ride4User[j].CheckInDate.year;
//            From_File >> UserAccounts[i].Ride4User[j].CheckInDate.month;
//            From_File >> UserAccounts[i].Ride4User[j].CheckInDate.day;
//            From_File >> UserAccounts[i].Ride4User[j].CheckInDate.hour;
//            From_File >> UserAccounts[i].Ride4User[j].CheckInDate.minute;
//            From_File >> UserAccounts[i].Ride4User[j].CheckOutDate.year;
//            From_File >> UserAccounts[i].Ride4User[j].CheckOutDate.month;
//            From_File >> UserAccounts[i].Ride4User[j].CheckOutDate.day;
//            From_File >> UserAccounts[i].Ride4User[j].CheckOutDate.hour;
//            From_File >> UserAccounts[i].Ride4User[j].CheckOutDate.minute;
//
//            From_File >> UserAccounts[i].Ride4User[j].Trip_Time;
//        }
//        i++;
//    }
//
//    From_File.close();
//}
//void Rides_Data_To_File() {
//    fstream To_File("Rides.txt", ios::out | ios::app);
//    if (!To_File.is_open()) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//    int i = 0;
//    while (i < Max_Current_Users_Size && !To_File.eof()) {
//        for (int j = 0; j < UserAccounts->AccUser.Rides_Count; j++) {
//            To_File << UserAccounts[i].Ride4User[j].Ride_ID << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckInStation << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckOutStation << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckInDate.year << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckInDate.month << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckInDate.day << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckInDate.hour << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckInDate.minute << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckOutDate.year << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckOutDate.month << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckOutDate.day << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckOutDate.hour << " ";
//            To_File << UserAccounts[i].Ride4User[j].CheckOutDate.minute << " ";
//
//            To_File << UserAccounts[i].Ride4User[j].Trip_Time << '\n';
//        }
//        i++;
//    }
//
//    To_File.close();
//}
//
//void subs_data_to_file() {
//    fstream To_File;
//    To_File.open("subs.txt", ios::out | ios::app);
//
//    if (!To_File.is_open()) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//    for (int i = 0; i < UsersCount; ++i) {
//        To_File << UserAccounts[i].AccSub.Subscription_Type << " ";
//        To_File << UserAccounts[i].AccSub.Start_Date.year << " ";
//        To_File << UserAccounts[i].AccSub.Start_Date.month << " ";
//        To_File << UserAccounts[i].AccSub.Start_Date.day << " ";
//        To_File << UserAccounts[i].AccSub.End_Date.year << " ";
//        To_File << UserAccounts[i].AccSub.End_Date.month << " ";
//        To_File << UserAccounts[i].AccSub.End_Date.day << " ";
//        To_File << endl;
//    }
//    To_File.close();
//}
//void subs_data_from_file() {
//    fstream From_File("subs.txt", ios::in);
//
//    if (!From_File.is_open()) {
//        cout << "Error opening file." << endl;
//        return;
//    }
//    int i = 0;
//    while (i < Max_Current_Users_Size && !From_File.eof()) {
//        From_File >> UserAccounts[i].AccSub.Subscription_Type;
//        From_File >> UserAccounts[i].AccSub.Rides_Count;
//        From_File >> UserAccounts[i].AccSub.Start_Date.year;
//        From_File >> UserAccounts[i].AccSub.Start_Date.month;
//        From_File >> UserAccounts[i].AccSub.Start_Date.day;
//        From_File >> UserAccounts[i].AccSub.End_Date.year;
//        From_File >> UserAccounts[i].AccSub.End_Date.month;
//        From_File >> UserAccounts[i].AccSub.End_Date.day;
//    }
//    From_File.close();
//}


//void Clear_File(string File_Path) {
//
//    fstream Clear(File_Path, ios::out | ios::trunc);
//    Clear.close();
//}
void Print_Line_Stations(int Specific_Line) {
    cout << "line " << Specific_Line << ':' << endl;
    for (int j = 0; j < lines[Specific_Line - 1].size(); ++j) {

        cout << j + 1 << ')' << lines[Specific_Line - 1][j];
        cout << endl;
    }
}

//string mesh_dis_play(int& Regist_Start_Line, int& Regist_Start_Station,
//    int& Regist_End_Line, int& Regist_End_Station) {
//
//    Display_Stations();
//
//    do {
//        cout << "Enter Start Line Number" << endl;
//        cin >> Regist_Start_Line;
//
//    } while (Regist_Start_Line < 1 || Regist_Start_Line > 3);
//    Print_Line_Stations(Regist_Start_Line);
//    cout << "Entet Start Station Number" << endl;
//    cin >> Regist_Start_Station;
//    while (lines[Regist_Start_Line - 1][Regist_Start_Station - 1].empty()) {
//        cout << "Invalid Station Number" << endl;
//        cout << "Entet Start Station Number" << endl;
//        cin >> Regist_Start_Station;
//    }
//    string CheckInStation =
//        lines[Regist_Start_Line - 1][Regist_Start_Station - 1];
//    cout << CheckInStation << endl;
//
//    Display_Stations();
//    do {
//        cout << "Enter End Line Number" << endl;
//        cin >> Regist_End_Line;
//
//    } while (Regist_End_Line < 1 || Regist_End_Line > 3);
//
//    Print_Line_Stations(Regist_End_Line);
//    cout << "Entet End Station Number" << endl;
//    cin >> Regist_End_Station;
//    while (lines[Regist_End_Line - 1][Regist_End_Station - 1].empty()) {
//        cout << "Invalid Station Number" << endl;
//        cout << "Entet End Station Number" << endl;
//        cin >> Regist_End_Station;
//    }
//    string CheckOutStation = lines[Regist_End_Line - 1][Regist_End_Station - 1];
//    cout << CheckOutStation << endl;
//
//    return CheckOutStation;
//}

bool Wallet_Charge() {

    int choice;
    cout << "Please Enter the amount you need to charge the card \n";
    cout << "1) 10 L.E\t";
    cout << "2) 50 L.E\n";
    cout << "3) 100 L.E\t";
    cout << "4) 200 L.E\n";
    cout << "5) Others";
    cin >> choice;
    switch (choice) {
    case 1:
        return charge_wallet(10);
        break;
    case 2:
        return  charge_wallet(50);

        break;
    case 3:
        return charge_wallet(100);

        break;

    case 4:
        return  charge_wallet(200);

        break;
    case 5:
        int charging_money;
        cin >> charging_money;
        while (charging_money % 10 != 0) {
            cout << "Please Enter Charging money in multyples of 10 like 10 , 20 ,30 "
                "and so on..."
                << endl;
            cin >> charging_money;
        }
        return charge_wallet(charging_money);




        break;
    }
    return 0;

}

void wallet_subsc() {
    if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type == "Wallet") {
        int Wallet_Choice;
        cout << "You have a wallet subscription\nIf you Want To Charge It Press "
            "'1' \n For return Press '2' "
            << endl;
        cin >> Wallet_Choice;
        while (Wallet_Choice < 1 && Wallet_Choice > 2) {
            cout << "Please Enter a valid number" << endl;
            cin >> Wallet_Choice;
        }
        if (Wallet_Choice == 1) {
            bool Return = Wallet_Charge();
            if (Return == 0)
                return;
        }

        else if (Wallet_Choice == 2)
            return;
    }

    if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type !=
        "Wallet" && UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type != "Isn't Available") {
        cout << "You Have Another Subscription\n Do You Want To Cancel It? \n If "
            "You Want To Cancel It Press '1' for return Press '2' "
            << endl;
        int Cancel_Choice;
        cin >> Cancel_Choice;
        while (Cancel_Choice != 1 && Cancel_Choice != 2) {
            cout << "Please Enter a valid number" << endl;
            cin >> Cancel_Choice;
        }
        if (Cancel_Choice == 1) {
            cout << "********************Charge The Wallet********************\n";
            cout << "Obtaining Card Cost 25 For First Time\n  ";
            bool Return = Wallet_Charge();
            if (Return == 0)
                return;


            UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type = "Wallet";

        }
        else if (Cancel_Choice == 2)
            return;

    }
    else // لو معندوش اي اشتراك
    {
        cout << "********************Charge The Wallet********************\n";
        cout << "Obtaining Card Cost 25 For First Time\n  ";
        bool Return = Wallet_Charge();
        if (Return == 0)
            return;


        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type = "Wallet";

    }
}

// check_balance(price_of_subscription);

//   // تحقق مما إذا كان نوع الاشتراك هو "بطاقة محفظة النقدية"
//   else if () {
//     float amount;
//     cout << "Please enter the amount of wallet ";
//     cin >> amount;

//     // تحقق مما إذا كان يمكن شحن المبلغ في البطاقة دون تجاوز الحد الأقصى
//     if (UserAccounts.AccUser.Balance + amount <= 400) {
//       UserAccounts.AccUser.Balance += amount;
//       cout << "Amount " << amount
//            << " LE added to Cash Wallet successfully.\n";
//     } else {
//       cout << "Cannot add amount. wallet limit exceeded.";
//     }
//   }
// }

// // calling the function to update the file containing users' information
// }
void View_History_Of_Rides() {

    for (int k = 0; k < UserAccounts[Index_Of_Target_User].Ride4User.size();
        k++) {
        cout << "Trip " << k + 1 << endl;
        cout << "\tDate: "
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckInDate.day
            << "/"
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckInDate.month
            << "/"
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckInDate.year
            << endl;
        cout << "\tTime: "
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckInDate.hour
            << ":"
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckInDate.minute
            << endl;
        cout << "\tStart location: "
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckInStation
            << endl;
        cout << "\tEnd location: "
            << UserAccounts[Index_Of_Target_User].Ride4User[k].CheckOutStation
            << endl;
        cout << "\tduration: "
            << UserAccounts[Index_Of_Target_User].Ride4User[k].Trip_Time;
            cout << "\t ride type"<<UserAccounts[Index_Of_Target_User].Ride4User[k].Type;
    }

    cout << endl;
    cout << "Press 1 to return to the main menu" << endl;
    ;
    int choice;
    cin >> choice;
    while (choice != 1) {
        View_History_Of_Rides();
        cin >> choice;
    }
    return;
}
void Update_Info() {
    int choice;

    cout << "1 : to upgrade the phone number \n ";
    cout << "2 : to upgrade the name \n ";
    cout << "3 : to upgrade the password \n ";

    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Enter the new phone number \n";
        cin >> UserAccounts[Index_Of_Target_User].AccUser.Phone_Number;
        break;
    case 2:
        cout << "Enter the new first name  \n ";
        cin >> UserAccounts[Index_Of_Target_User].AccUser.First_Name;
        cout << "Enter the new last name  \n ";
        cin >> UserAccounts[Index_Of_Target_User].AccUser.Last_Name;
        break;
    case 3:
        cout << "Enter the new password \n";
        cin >> UserAccounts[Index_Of_Target_User].AccUser.Password;
        break;
    }
}
/*void Bu() {//Buy
  int choice;
  cout << "\t\tSubscriptions Types\t\t" << endl << endl;
  cout << "\t 1)Wallet Subscription" << endl;
  cout << "\t 2)Public Subscription" << endl;
  cout << "\t 3)Student Subscription" << endl;
  cin >> choice;
  switch (choice) {
  case 1:
    wallet_subsc();
    break;
  case 2:
    public_subsc();
    break;
  case 3:
    Student_Subscription();
    break;

  default:
    break;
  }
}
*/

void Date_Updater(int number_of_months, Accounts& useraccount) {
    int check = number_of_months + useraccount.AccSub.End_Date.month;
    if (check > 12) {
        useraccount.AccSub.End_Date.month = check - 12;
        useraccount.AccSub.End_Date.year += 1;
    }
    else
        useraccount.AccSub.End_Date.month = check;
}
void Renew_Subscription(admin_subsc* subscr_admin) {

    int sub_index;

    for (int i = 0; i < nsubscrip; ++i) {

        if (subscr_admin[i].name ==
            UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type) {
            sub_index = i;
            break;
        }
    }

    int price;
    int sub_period =
        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period;
    int sub_period_ind;
    int nzones = UserAccounts[Index_Of_Target_User].AccSub.current_zone; //

    if (sub_period == 1)
        sub_period_ind = 0;
    else if (sub_period == 3)
        sub_period_ind = 1;
    else
        sub_period_ind = 2;

    price = subscr_admin[sub_index].prices[nzones][sub_period_ind];
    if (check_balance(price)) {

        Date st_date = On_Time();
        UserAccounts[Index_Of_Target_User].AccSub.Start_Date.year = st_date.year;
        UserAccounts[Index_Of_Target_User].AccSub.Start_Date.month = st_date.month;
        UserAccounts[Index_Of_Target_User].AccSub.Start_Date.day = st_date.day;
        Date_Updater(sub_period, UserAccounts[Index_Of_Target_User]);
        UserAccounts[Index_Of_Target_User].AccSub.Remaining_Trips = 60 * sub_period;

    }

    else {
        cout << "Insuffcient balance\n";
        return;
    }
}
int get_place_subscrip(admin_subsc* subscr_admin) {
    cout << "Which Suubscripition You Want To Choose\n";

    for (int i = 0; i < nsubscrip; i++)
        cout << i + 1 << ") " << subscr_admin[i].name << endl;


    int choice = check_enter_choice(nsubscrip, 1);

    return choice -1; // because it will be an  index of array
}

int Price_Of_Subscripition(admin_subsc* subscr_admin, int zone, int place) {
    int Choice;
    int Price;

    cout << "Choose Subscription Period You Want\n";

    if (subscr_admin[place].name == "Student") {
        int StudentChoice;
        if (zone == 1 || zone == 2) {
            cout << "1) Quarter Year Subscription: "<< subscr_admin[place].prices[zone - 1][1] << " L.E\n";
            Price=subscr_admin[place].prices[zone - 1][1];
        }
        else if (zone == 3 || zone == 4) {
            cout << "1) Quarter Year Subscription: "<< subscr_admin[place].prices[2][1];
            Price = subscr_admin[place].prices[2][1];
        }
        else {

            cout << "1) Quarter Year Subscription: "<< subscr_admin[place].prices[3][1];
            Price=subscr_admin[place].prices[3][1];
        }

        cout << "2) Return\n";
        cout << "Enter Your Choice: \n";

        cin >> StudentChoice;
        if (StudentChoice == 2)
            return -1;
        if (!check_balance(Price)) {
            cout << "No Sufficient Balance" << endl;
            return -1;
        }

        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 3;
        return Price;

    }

    if (zone == 1) {

        cout << "1) Monthly Subscription: "
            << subscr_admin[place].prices[zone - 1][0] << " L.E\n";
        cout << "2) Quarter Year Subscription: "
            << subscr_admin[place].prices[zone - 1][1] << " L.E\n";
        cout << "3) Annual Subscription: "
            << subscr_admin[place].prices[zone - 1][2] << " L.E\n";
        cout << "4) Return\n";
        cin >> Choice;

        if (Choice == 4)
            return -1;
        Price = subscr_admin[place].prices[zone - 1][Choice - 1];
    }
    else if (zone == 2) {
        cout << "1) Monthly Subscription: "
            << subscr_admin[place].prices[zone - 1][0] << " L.E\n";
        cout << "2) Quarter Year Subscription: "
            << subscr_admin[place].prices[zone - 1][1] << " L.E\n";
        cout << "3) Annual Subscription: "
            << subscr_admin[place].prices[zone - 1][2] << " L.E\n";
        cout << "4) Return\n";
        cin >> Choice;

        if (Choice == 4)
            return -1;
        Price = subscr_admin[place].prices[zone - 1][Choice - 1];
    }
    else if (zone == 3 || zone == 4) {
        cout << "1) Monthly Subscription: " << subscr_admin[place].prices[2][0]
            << " L.E\n";
        cout << "2) Quarter Year Subscription: " << subscr_admin[place].prices[2][1]
            << " L.E\n";
        cout << "3) Annual Subscription: " << subscr_admin[place].prices[2][2]
            << " L.E\n";
        cout << "4) Return\n";
        cin >> Choice;

        if (Choice == 4)
            return -1;
        Price = subscr_admin[place].prices[2][Choice - 1];
    }
    else if (zone == 5 || zone == 6) {
        cout << "1) Monthly Subscription: " << subscr_admin[place].prices[3][0]
            << " L.E\n";
        cout << "2) Quarter Year Subscription: " << subscr_admin[place].prices[3][1]
            << " L.E\n";
        cout << "3) Annual Subscription: " << subscr_admin[place].prices[3][2]
            << " L.E\n";

        cout << "4) Return\n";
        cin >> Choice;

        if (Choice == 4)
            return -1;
        Price = subscr_admin[place].prices[3][Choice - 1];
    }
    cout << "The Price of the subscription is " << Price << " L.E"
        << endl;
    cout << "1) Continue" << endl;
    cout << "2) Return" << endl;
    int Countinue_or_Not = check_enter_choice(2, 0);
    if (Countinue_or_Not == 2)
        return -1;
    if (!check_balance(Price)) {
        cout << "No Sufficient Balance" << endl;
        return -1;
    }

    if (Choice == 1)
        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 1;
    else if (Choice == 2)
        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 3;

    else if (Choice == 3)
        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 12;
    else {
        cout << "Invalide Choice\n";
        return 0;
    }

    return Price;
}

void Purchase_Subscripition(admin_subsc* subscr_admin, string zones[11][11]) {
    int Regist_Start_Line;
    int Regist_End_Line;
    int Regist_Start_Station;
    int Regist_End_Station;
Display_Stations();

    do {
        cout << "Enter Start Line Number" << endl;
        cin >> Regist_Start_Line;

    } while (Regist_Start_Line < 1 || Regist_Start_Line > 3);
    Print_Line_Stations(Regist_Start_Line);
    cout << "Entet Start Station Number" << endl;
    cin >> Regist_Start_Station;
    while (lines[Regist_Start_Line - 1][Regist_Start_Station - 1].empty()) {
        cout << "Invalid Station Number" << endl;
        cout << "Entet Start Station Number" << endl;
        cin >> Regist_Start_Station;
    }
    string CheckInStation =
        lines[Regist_Start_Line - 1][Regist_Start_Station - 1];
    cout << CheckInStation << endl;

    Display_Stations();
    do {
        cout << "Enter End Line Number" << endl;
        cin >> Regist_End_Line;

    } while (Regist_End_Line < 1 || Regist_End_Line > 3);

    Print_Line_Stations(Regist_End_Line);
    cout << "Entet End Station Number" << endl;
    cin >> Regist_End_Station;
    while (lines[Regist_End_Line - 1][Regist_End_Station - 1].empty()) {
        cout << "Invalid Station Number" << endl;
        cout << "Entet End Station Number" << endl;
        cin >> Regist_End_Station;
    }
    string CheckOutStation = lines[Regist_End_Line - 1][Regist_End_Station - 1];
    cout << CheckOutStation << endl;

    int place = get_place_subscrip(subscr_admin);




cout<<"sads\n";
    int num_of_zones = How_Many_Zones(Regist_Start_Line, Regist_Start_Station,
        Regist_End_Line, Regist_End_Station);


        cout<<"sdsd\n";


    int price_of_subscription = Price_Of_Subscripition(subscr_admin, num_of_zones, place);
    if (price_of_subscription == -1){
            cout<<"-1";
        return;

    }



    UserAccounts[Index_Of_Target_User].AccSub.current_zone = num_of_zones;
    UserAccounts[Index_Of_Target_User].AccSub.Current_Supscripition_Value =
        price_of_subscription;
    Date Subscription = On_Time();
    UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type =
        subscr_admin[place].name;
    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.year = Subscription.year;
    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.month =
        Subscription.month;
    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.day = Subscription.day;

    UserAccounts[Index_Of_Target_User].AccSub.End_Date.year = Subscription.year;
    UserAccounts[Index_Of_Target_User].AccSub.End_Date.month =
        Subscription.month;
    UserAccounts[Index_Of_Target_User].AccSub.End_Date.day = Subscription.day;

    int Period_Of_Subscription =
        UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period;

    switch (Period_Of_Subscription) {

    case 1: // 1 month

        UserAccounts[Index_Of_Target_User].AccSub.End_Date.month =
            Subscription.month + 1;
        UserAccounts[Index_Of_Target_User].AccSub.current_zone = num_of_zones;
        if (UserAccounts[Index_Of_Target_User].AccSub.End_Date.month > 12) {
            UserAccounts[Index_Of_Target_User].AccSub.End_Date.year += 1;
            UserAccounts[Index_Of_Target_User].AccSub.End_Date.month -= 12;
        }

        break;
    case 3: // 3 months
        UserAccounts[Index_Of_Target_User].AccSub.End_Date.month =
            Subscription.month + 3;

        if (UserAccounts[Index_Of_Target_User].AccSub.End_Date.month > 12) {
            UserAccounts[Index_Of_Target_User].AccSub.End_Date.year += 1;
            UserAccounts[Index_Of_Target_User].AccSub.End_Date.month -= 12;
        }
        break;
    case 12: // 12 months
        UserAccounts[Index_Of_Target_User].AccSub.End_Date.year += 1;
        break;
    }
    UserAccounts[Index_Of_Target_User].AccSub.Remaining_Trips =
        60 * Period_Of_Subscription;
    string Exchange;
    if (Regist_Start_Line != Regist_End_Line) {
        for (int Lafa = 0; Lafa < 2; Lafa++) {
            if (Regist_Start_Line == 1 && Regist_End_Line == 2)
                Exchange = "al_shohadaa";


            else if (Regist_Start_Line == 1 && Regist_End_Line == 3)
                Exchange = "nasser";
            else if (Regist_Start_Line == 2 && Regist_End_Line == 3)
                Exchange = "ataba";

            swap(Regist_Start_Line, Regist_End_Line);
            swap(Regist_Start_Station, Regist_End_Station);
        }
        register_subscription_stations_with_exchanging(
            UserAccounts[Index_Of_Target_User].AccSub.sub_stations, Exchange,
            Regist_Start_Line, Regist_Start_Station, Regist_End_Line,
            Regist_End_Station, CheckOutStation);

    }
    else

        register_subscription_stations_without_exchanging(
            UserAccounts[Index_Of_Target_User].AccSub.sub_stations,
            Regist_Start_Station, Regist_End_Station, Regist_Start_Line);
}

void upgrade_subscription(admin_subsc* subscr_admin, string zones[11][11]) {

    int price;
    int choice;

    cout << "1-change plan\n";
    cout << "2-extend plan\n";
    choice = check_enter_choice(2, 1);
    if (choice == -1) {
        return;
    }
    if (choice == 1) {
        Purchase_Subscripition(subscr_admin, zones); //////////fake error
    }

    else if (choice == 2) {
        if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type ==
            "Student") {

            cout << "There is no extend for this plan you can only renew \n";
            upgrade_subscription(subscr_admin, zones);
        }

        int sub_index;

        for (int i = 0; i < nsubscrip; ++i) {

            if (subscr_admin[i].name ==
                UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type) {
                sub_index = i;
                break;
            }
        }

        if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period == 1) {
            ;
            int choice;
            cout << " 1 - Extend to 3 monthes\n 2 - Extend to 1 year \n";
            choice = check_enter_choice(2, 1);
            if (choice == -1) {
                upgrade_subscription(subscr_admin, zones);
            }
            switch (choice) {
            case 1:
                price =
                    subscr_admin[sub_index].prices[UserAccounts[Index_Of_Target_User]
                    .AccSub.current_zone][1];
                if (check_balance(price)) {
                    Date st_date = On_Time();
                    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.year =
                        st_date.year;
                    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.month =
                        st_date.month;
                    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.day =
                        st_date.day;
                    UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 3;
                    UserAccounts[Index_Of_Target_User].AccSub.Remaining_Trips = 60 * 3;

                    Date_Updater(3, UserAccounts[Index_Of_Target_User]);
                }

                else {
                    cout << "Insuffcient Balance Please Recharge \n";
                }
                break;

            case 2:
                price =
                    subscr_admin[sub_index].prices[UserAccounts[Index_Of_Target_User]
                    .AccSub.current_zone][2];
                if (check_balance(price)) {
                    Date st_date = On_Time();
                    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.year =
                        st_date.year;
                    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.month =
                        st_date.month;
                    UserAccounts[Index_Of_Target_User].AccSub.Start_Date.day =
                        st_date.day;
                    UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 12;
                    UserAccounts[Index_Of_Target_User].AccSub.Remaining_Trips = 60 * 12;

                    Date_Updater(12, UserAccounts[Index_Of_Target_User]);
                }
                else {
                    cout << "Insuffcient Balance Please Recharge \n";
                    upgrade_subscription(subscr_admin, zones);
                }
                break;
            }

        }
        else if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period ==
            3) {
            int choice;
            cout << " 1 - Extend to 1 year \n";
            choice = check_enter_choice(1, 1);
            if (choice == -1)
                upgrade_subscription(subscr_admin, zones);

        }

        else if (choice == 1) {
            if (check_balance(price)) {//
                Date st_date = On_Time();
                UserAccounts[Index_Of_Target_User].AccSub.Start_Date.year =
                    st_date.year;
                UserAccounts[Index_Of_Target_User].AccSub.Start_Date.month =
                    st_date.month;
                UserAccounts[Index_Of_Target_User].AccSub.Start_Date.day = st_date.day;
                UserAccounts[Index_Of_Target_User].AccSub.Subscription_Period = 12;
                Date_Updater(12, UserAccounts[Index_Of_Target_User]);
            }
            else {
                cout << "Insuffcient Balance Please Recharge \n";
                upgrade_subscription(subscr_admin, zones);
            }

        }
        else {
            cout << "You Can't extend your plan more than one year";
            upgrade_subscription(subscr_admin, zones);
        }
    }
}
void show_start_end_date() {
    cout << "Start date :   "
        << UserAccounts[Index_Of_Target_User].AccSub.Start_Date.year << "/"
        << UserAccounts[Index_Of_Target_User].AccSub.Start_Date.month << "/"
        << UserAccounts[Index_Of_Target_User].AccSub.Start_Date.day << endl;
    cout << "End date :   "
        << UserAccounts[Index_Of_Target_User].AccSub.End_Date.year << "/"
        << UserAccounts[Index_Of_Target_User].AccSub.End_Date.month << "/"
        << UserAccounts[Index_Of_Target_User].AccSub.End_Date.day << endl;
}

void show_sub_info() {
    cout << "Hello " << UserAccounts[Index_Of_Target_User].AccUser.First_Name
        << " Here is your subscription info \n";
    show_start_end_date();
    cout << "Rides count :  "
        << UserAccounts[Index_Of_Target_User].AccUser.Rides_Count;
}
void Manage_Subscription(admin_subsc* subscr_admin, string zones[11][11]) {
    int choice;
    cout << "------------------------------Upgrade or renew "
        "subscription--------------------- \n";
    cout << "1)Charge Wallet\n";
    cout << "2)-Show subscription info\n";
    cout << "3)-Upgrade subscription\n";
    cout << "4)-renew subscription\n";


    choice = check_enter_choice(4, 1);

    if (choice == 1)
        Wallet_Charge();

    if (choice == 2)
        show_sub_info();

    if (choice == 3)
        upgrade_subscription(subscr_admin, zones);

    if (choice == 4)
        Renew_Subscription(subscr_admin);
}

bool check_in_time()
{
    Date check_in_time = On_Time();




    if (UserAccounts[Index_Of_Target_User].AccSub.End_Date.year < check_in_time.year || (UserAccounts[Index_Of_Target_User].AccSub.End_Date.year == check_in_time.year && UserAccounts[Index_Of_Target_User].AccSub.End_Date.month < check_in_time.month)
        ||
        (UserAccounts[Index_Of_Target_User].AccSub.End_Date.year == check_in_time.year && UserAccounts[Index_Of_Target_User].AccSub.End_Date.month == check_in_time.month && UserAccounts[Index_Of_Target_User].AccSub.End_Date.day < check_in_time.day))
    {
        // End date is before current date
        return false;
    }
    else
    {
        // End date is after or equal to current date
        return true;
    }
}



void Succesfuly_CheckIn(int Count) {

    Date Checkin = On_Time();
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInDate.year = Checkin.year;
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInDate.month =
        Checkin.month;

    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInDate.day =
        Checkin.day;

    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInDate.hour =
        Checkin.hour;
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInDate.minute = Checkin.minute;

}







bool Check_In(int& Beginning_Line, int& Beginning_Station, int& Ending_Line, int& Ending_Station, int Tickets_Prices[]) {
    int Count = UserAccounts[Index_Of_Target_User].AccUser.Rides_Count;

cout << "1\n";
string Chosen;

        cout << "2\n";
    if (UserAccounts[Index_Of_Target_User].AccSub.have_ticket)
    {
cout << "3\n";
        Display_Stations();
        do {
            cout << "Enter start line \n";
            cin >> Beginning_Line;
            if (Beginning_Line > 0 && Beginning_Line < 4)
                break;

        } while (true);
        // UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 0;

        Print_Line_Stations(Beginning_Line);

        do {
            cout << "enter start station number : ";
            cin >> Beginning_Station;

            if (Beginning_Station > 0 && Beginning_Station < 36)
                break;

        } while (true);

        Chosen = lines [Beginning_Line - 1][Beginning_Station - 1];


        Rides temp;
        UserAccounts[Index_Of_Target_User].Ride4User.push_back(temp);
        UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInStation = Chosen;

        Succesfuly_CheckIn(Count);
        return 1;
    }

    if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type == "Wallet") {
        if (UserAccounts[Index_Of_Target_User].AccSub.Wallet < Tickets_Prices[0])
        {
            cout << "You Don't Have Enough In Your Wallet\n Charge It And Recheckin\n";
            return 0;
        }
        UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInStation = Chosen;

        Succesfuly_CheckIn(Count);
        return 1;

    }

    else if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type == "Isn't Available")
    {
        cout << "You don't have ticket or any subscription Plan\n";
        return 0;
    }

    else if (!(UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type == "Isn't Available"))
    {

        if (UserAccounts[Index_Of_Target_User].AccSub.Remaining_Trips <= 0 || check_in_time() == 0)
            return false;


        Display_Stations();
        do {
            cout << "Enter start line \n";
            cin >> Beginning_Line;
            Print_Line_Stations(Beginning_Line);
            if (Beginning_Line > 0 && Beginning_Line < 4)
                break;

        } while (true);

        //Wallet..Remaining Trips

        do {
            cout << "enter start station number : ";
            cin >> Beginning_Station;
            if (lines[Beginning_Line - 1][Beginning_Station - 1].empty())
                continue;
            if (Beginning_Station > 0 && Beginning_Station < 36)
                break;

        } while (true);
         Chosen = lines[Beginning_Line - 1][Beginning_Station - 1];



        if (check_station_in_the_subscribtion(UserAccounts[Index_Of_Target_User].AccSub.sub_stations, Chosen))
        {
            UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckInStation = Chosen;

            Succesfuly_CheckIn(Count);
            return 1;
        }

        else
        {
            cout << "This station is not in your Subscription plan \n";
            return 0;
        }


    }


}










void CheckOut1(int Count) {

    Date Checkout = On_Time();
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckOutDate.year =
        Checkout.year;
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckOutDate.month =
        Checkout.month;
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckOutDate.month =
        Checkout.day;
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckOutDate.month =
        Checkout.hour;
    UserAccounts[Index_Of_Target_User].Ride4User[Count].CheckOutDate.month =
        Checkout.minute;
    UserAccounts[Index_Of_Target_User].AccUser.Rides_Count++;


}


float ticket_price(int num_of_stations,int Tickets_Prices[])
{
    float final_price;
    if (num_of_stations <= 9)
    {
        final_price = Tickets_Prices[0];
    }
    else if (num_of_stations >= 10 && num_of_stations <= 16)
    {
        final_price = Tickets_Prices[1];
    }
    else if (num_of_stations >= 17 && num_of_stations <= 23)
    {
        final_price = Tickets_Prices[2];
    }
    else if (num_of_stations >= 24)
    {
        final_price = Tickets_Prices[3];
    }
    return final_price;
}

bool check_out(int start_line, int start_station,
     int Ticket_Prices[]) {

    int count = UserAccounts[Index_Of_Target_User].AccUser.Rides_Count;
    int Ending_Line, Ending_Station;



    string exchang;
    int num_stations = 0;


    Display_Stations();
    do {
        cout << "Enter start line \n";
        cin >> Ending_Line;
        if (Ending_Line > 0 && Ending_Line < 4)
            break;

    } while (true);

    Print_Line_Stations(Ending_Line);

    do {
        cout << "enter end station number : ";
        cin >> Ending_Station;

        if (!lines[Ending_Line - 1][Ending_Station - 1].empty())
            break;

    } while (true);




    string check_out_station = lines[Ending_Line - 1][Ending_Station - 1];
    cout << check_out_station << endl;
    UserAccounts[Index_Of_Target_User].Ride4User[count].CheckOutStation = check_out_station;

  int passed_stations =Passed_Stations(start_line, start_station, Ending_Line, Ending_Station);


    if (UserAccounts[Index_Of_Target_User].AccSub.have_ticket)
    {
        if (UserAccounts[Index_Of_Target_User].AccSub.num_stations < passed_stations) {
            UserAccounts[Index_Of_Target_User].Ride4User[count].Type = "Failed";
            cout << "Check Out Failed\n Pay The Fine And Exit \n";
            UserAccounts[Index_Of_Target_User].AccSub.num_stations = 0;
            UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 0;
            CheckOut1(count);
          UserAccounts[Index_Of_Target_User].Ride4User[count].Trip_Time  = TripTime(passed_stations ) ;
            return 1;
        }

        cout << "Check Out Success\n";
        UserAccounts[Index_Of_Target_User].AccSub.num_stations = 0;
        UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 0;
        CheckOut1(count);
        UserAccounts[Index_Of_Target_User].Ride4User[count].Trip_Time  = TripTime(passed_stations ) ;
        return 1;
    }



    if (UserAccounts[Index_Of_Target_User].AccSub.Subscription_Type == "Wallet") {
        int Price_Of_The_Ticket=ticket_price(passed_stations, Ticket_Prices);
        if (Price_Of_The_Ticket > UserAccounts[Index_Of_Target_User].AccSub.Wallet) {
            UserAccounts[Index_Of_Target_User].Ride4User[count].Type = "Failed";
            cout << "Check Out Failed\n Pay The Fine And Exit \n";
            CheckOut1(count);
            UserAccounts[Index_Of_Target_User].Ride4User[count].Trip_Time  = TripTime(passed_stations)  ;
            return 1;


        }

        cout << "Check Out Success\n";
      UserAccounts[Index_Of_Target_User].AccSub.Wallet -= Price_Of_The_Ticket;
        CheckOut1(count);
        UserAccounts[Index_Of_Target_User].Ride4User[count].Trip_Time  = TripTime(passed_stations ) ;

        return 1;
    }


 bool Successfuly_CheckOut = check_station_in_the_subscribtion(UserAccounts[Index_Of_Target_User].AccSub.sub_stations, check_out_station);

        if (Successfuly_CheckOut) {
            cout << "check out succesfully \n";
            UserAccounts[Index_Of_Target_User].AccSub.Remaining_Trips--;
            CheckOut1(count);
                    UserAccounts[Index_Of_Target_User].Ride4User[count].Trip_Time  = TripTime(passed_stations ) ;

            return 1;

        }

        else if (Successfuly_CheckOut == 0) {
            cout << "Check out failed\n Invalid station \n";
            cout << "Check Out Failed Invalid Station\n Pay The Fine And Exit \n";
            CheckOut1(count);
                    UserAccounts[Index_Of_Target_User].Ride4User[count].Trip_Time  = TripTime(passed_stations ) ;

            return 1;
        }















    ///////////////////////

    // call function to update balance
}




void Take_Ride(int &Beginning_Line, int &Beginning_Station, int &Ending_Line,
    int &Ending_Station, int Ticket_Price[], bool& Done_CheckIn,
    bool& Done_CheckOut) {



    cout << "1)Check In\n";
    cout << "2)Check Out\n";
    cout << "3)exit\n";

    int choice ;
    cin>>choice;

cout << "ttt";

    if (choice == 1 && Done_CheckIn) {
        cout << "Please Finish Your Trip First Before ReCheckIn\n";
        Take_Ride(Beginning_Line, Beginning_Station, Ending_Line, Ending_Station,
            Ticket_Price, Done_CheckIn, Done_CheckOut);

    }
    if (choice == 1 && !Done_CheckIn) {
cout << "kug";

        Done_CheckIn =
            Check_In(Beginning_Line, Beginning_Station, Ending_Line, Ending_Station,Ticket_Price);
        Take_Ride(Beginning_Line, Beginning_Station, Ending_Line, Ending_Station,
            Ticket_Price, Done_CheckIn, Done_CheckOut);
    }
    if (choice == 2 && !Done_CheckIn) {
        cout << "Please CheckIn First\n";
        Take_Ride(Beginning_Line, Beginning_Station, Ending_Line, Ending_Station,
            Ticket_Price, Done_CheckIn, Done_CheckOut);
    }
    if (choice == 2 && Done_CheckIn) {

        Done_CheckOut = check_out(Beginning_Line, Beginning_Station,
             Ticket_Price);
    if (choice == 3)
      {

    return;

      }
        if (Done_CheckOut) {

            return;
        }
    }
    if (choice == -1)
        return;
}




void Buy_Ticket(int Tickets_Prices[]) {
    cout << "**************Tickets Prices**************\n";
    cout << "1) " << Tickets_Prices[0] << " L.E From 1 Stations To 9 Stations\n";
    cout << "2) " << Tickets_Prices[1]
        << " L.E From 10 Stations To 16 Stations\n";
    cout << "3) " << Tickets_Prices[2]
        << " L.E From 17 Stations To 23 Stations\n";
    cout << "4) " << Tickets_Prices[3] << " L.E More Than 23 Stations\n";
    cout << "5)Return\n";
    int choice;
    cin >> choice;
    int Continuee;

    switch (choice) {
    case 1:
        cout << Tickets_Prices[0] << " L.E From 1 Stations To 9 Stations\n\n";
        cout << "1)Continue\n2)Return\n";
        cin >> Continuee;
        if (Continuee == 2)
            Buy_Ticket(Tickets_Prices);
        if (!check_balance(Tickets_Prices[0])) {
            cout << "You don't have enough balance\n";
            Buy_Ticket(Tickets_Prices);
        }

        UserAccounts[Index_Of_Target_User].AccSub.num_stations = 9;
        UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 1;
        break;
    case 2:
        cout << Tickets_Prices[1] << " L.E From 10 Stations To 16 Stations\n\n";
        cout << "1)Continue\n2)Return\n";
        cin >> Continuee;
        if (Continuee == 2)
            Buy_Ticket(Tickets_Prices);
        if (!check_balance(Tickets_Prices[1])) {
            cout << "You don't have enough balance\n";
            Buy_Ticket(Tickets_Prices);
        }

        UserAccounts[Index_Of_Target_User].AccSub.num_stations = 16;
        UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 1;
        break;
    case 3:
        cout << Tickets_Prices[2] << " L.E From 17 Stations To 23 Stations\n\n";
        cout << "1)Continue\n2)Return\n";
        cin >> Continuee;
        if (Continuee == 2)
            Buy_Ticket(Tickets_Prices);
        if (!check_balance(Tickets_Prices[2])) {
            cout << "You don't have enough balance\n";
            Buy_Ticket(Tickets_Prices);
        }

        UserAccounts[Index_Of_Target_User].AccSub.num_stations = 23;
        UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 1;
        break;
    case 4:
        cout << Tickets_Prices[3] << " L.E For More Than 23 Stations\n\n";
        cout << "1)Continue\n2)Return\n";
        cin >> Continuee;
        if (Continuee == 2)
            Buy_Ticket(Tickets_Prices);
        if (!check_balance(Tickets_Prices[3])) {
            cout << "You don't have enough balance\n";
            Buy_Ticket(Tickets_Prices);
        }
        UserAccounts[Index_Of_Target_User].AccSub.num_stations =39;
        UserAccounts[Index_Of_Target_User].AccSub.have_ticket = 1;
        break;

    case 5:
        return;

    default:
        cout << "Invalid Choice\n";
        Buy_Ticket(Tickets_Prices);
    }
}

void edit_station(int line) {


    Print_Line_Stations(line+1);
    int nstation = check_enter_choice(lines[line].size(), 1) - 1;
    if (nstation < 0)
        return;

    cout << "Please Enter the new name of the station:" << endl;
    string new_station;
    cin >> new_station;
    lines[line][nstation] = new_station;


}
void delete_station(int line) { // edit
    Print_Line_Stations(line+1);
    int nstation = check_enter_choice(lines[line].size(), 1) - 1;

    if (nstation < 0)
        return;
    lines[line].erase(lines[line].begin() + nstation);
}
void Add_station(int line, string zones[11][11]) {
    Print_Line_Stations(line+1);
    cout << "Please Enter the name of the station that you want to add" << endl;
    string new_station;
    cin >> new_station;
    cout << "Please Enter the position where you want to add the station in "
        "range [ 1 , "
        << lines[line].size() + 1 << " ]" << endl;
    int nstation = check_enter_choice(lines[line].size()+1, 0) ;
    nstation--;
    cout << "Please Enter The Number Of Zones Do You Want To Add On\n";
    int zone_number;
    cin >> zone_number;
    if (zones[zone_number][9].empty())
    {
        for (int i = 0; i < 10; i++)
        {
            if (zones[zone_number][i].empty())
            {
                zones[zone_number][i] = new_station;
                break;
            }
        }
    }
    else
    {
        if (!zones[zone_number][9].empty())
            return Add_station(line, zones);

    }



    lines[line].insert(lines[line].begin() + nstation, new_station);
}

void main_station_managment(string zones[11][11]) {
    int choice;
    do {
        cout << "Enter your choice: " << endl;
        cout << "1) Edit a station" << endl;
        cout << "2) Add a  station" << endl;
        cout << "3) Delete a station" << endl;
        choice = check_enter_choice(3, 1);
        if (choice == -1)
            return;
        cout << "Please Enter the number of the line that you want to work on "
            << endl;
        cout << "line (1)" << endl;
        cout << "line (2)" << endl;
        cout << "line (3)" << endl;
        int nline = check_enter_choice(3, 1);
        if (nline == -1)
            continue;
        nline--;
        switch (choice) {
        case 1:
            edit_station(nline);
            break;
        case 2:
            Add_station(nline, zones);
            break;
        case 3:
            delete_station(nline);
            break;

        default:
            break;
        }
    } while (display_menue_again(choice, 3));
}

void print_user_by_index(int Place) {
    if (!UserAccounts[Place].AccUser.ID)
        return;
    cout << "\n**\n";
    cout << "Name: ";
    cout << UserAccounts[Place].AccUser.First_Name + " " +
        UserAccounts[Place].AccUser.Last_Name
        << endl;
    cout << "ID: ";
    cout << UserAccounts[Place].AccUser.ID << endl;
    cout << "phone: ";
    cout << UserAccounts[Place].AccUser.Phone_Number << endl;
    cout << "Email: ";
    cout << UserAccounts[Place].AccUser.Email << endl;
    cout << "Rides Count: ";
    cout << UserAccounts[Place].AccUser.Rides_Count << endl;
    cout << "Authority: ";
    if (UserAccounts[Place].AccUser.Admin) {
        cout << "Admin" << endl;
        return;
    }
    cout << "User" << endl;
    cout << "Subscribtion Type: ";
    cout << UserAccounts[Place].AccSub.Subscription_Type << endl;
    cout << "Start date: ";
    cout << UserAccounts[Place].AccSub.Start_Date.day << " / "
        << UserAccounts[Place].AccSub.Start_Date.month << " / "
        << UserAccounts[Place].AccSub.Start_Date.year << " at "
        << UserAccounts[Place].AccSub.Start_Date.hour << endl;

    cout << "End date: ";
    cout << UserAccounts[Place].AccSub.End_Date.day << " / "
        << UserAccounts[Place].AccSub.End_Date.month << " / "
        << UserAccounts[Place].AccSub.End_Date.year << " at "
        << UserAccounts[Place].AccSub.End_Date.hour << endl;
    cout << "\n####################\n";
}
void view_by_name() {

    cout << "please enter the name " << endl;
    string name;
    cin >> name;
    for (int i = 0; i < UsersCount; i++) {
        if (UserAccounts[i].AccUser.First_Name == name) {
            print_user_by_index(i);
            return;
        }
    }
    cout << "Name isnot exist\n";
    // 1 and 1 to ask him if he wants to complete or not in all condition
}
int view_by_ID() {

    cout << "please enter the ID " << endl;
    int id;
    cin >> id;
    for (int i = 0; i < UsersCount; i++) {
        if (UserAccounts[i].AccUser.ID == id) {
            print_user_by_index(i);
            return i;
        }
    }
    cout << "ID isnot exist\n";

    return -1;
}
void view_all_users() {
    for (int i = 0; i < UsersCount; i++) {
        print_user_by_index(i);
    }
}
// **************************************   End OF print USERS  for admin
// ******************************

// ####################################  start of Edit users account For Admin
// #######################

void edit_name(int place) {
    cout << "Please Enter the new name: \n";
    cout << "First Name:";
    string Firstname;
    cin >> Firstname;
    UserAccounts[place].AccUser.First_Name = Firstname;
    cout << "\nLast Name:";
    int LastName;
    cin >> LastName;
    UserAccounts[place].AccUser.Last_Name = LastName;
}
void edit_email(int place) {
    cout << "Please Enter the new email: ";
    string email;
    cin >> email;
    UserAccounts[place].AccUser.Email = email;
}
void edit_balance(int place) {
    cout << "Please Enter the new balance: ";
    int balance;
    cin >> balance;
    UserAccounts[place].AccUser.Balance = balance;
}
void edit_password(int place) {
    cout << "Please Enter the new password: ";
    string password;
    cin >> password;
    UserAccounts[place].AccUser.Password = password;
}
void edit_phone_number(int place) {
    cout << "Please Enter the new phone number : ";
    string phone_num;
    cin >> phone_num;
    UserAccounts[place].AccUser.Phone_Number = phone_num;
}
void delete_userAcount(int place) {
    // PLACE IS INDEX
    for (int i = place; i < UsersCount; i++) {
        swap(UserAccounts[i], UserAccounts[i + 1]);

        // swap(a[2],a[3])
        // swap(a[3],a[4])
        // swap(a[i],a[i+1])  ((i=place))
    }
    if (UsersCount)
        UsersCount--;
}
void View_Name_ID() {

    for (int i = 0; i < UsersCount; i++) {
        cout << "Name: " << UserAccounts[i].AccUser.First_Name << endl;
        cout << "ID: " << UserAccounts[i].AccUser.ID << endl;
    }
}
void Edit_useraccount() {
    bool Is_first_loop = 1;
    bool is_user_deleted = 0;
    cout << "To edit " << endl;
    View_Name_ID();
    int place = view_by_ID();
    while (place == -1 && display_menue_again(1, 1))
        place = view_by_ID();
    if (place == -1)
        return;
    int choice;
    char edit_again;
    do {
        if (is_user_deleted)
            return Edit_useraccount();

        if (!Is_first_loop) {
            cout << "Do you want to complete editing on the same User ?" << endl;
            cout << "1) Yes " << endl;
            cout << "2) NO " << endl;
            int choice2 = check_enter_choice(2, 0);
            if (choice2 == 2)
                return Edit_useraccount();
        }

        cout << "what do you want to edit ?" << endl;
        cout << "1) Name" << endl;
        cout << "2) Email" << endl;
        cout << "3) Password" << endl;
        cout << "4) Phone number" << endl;
        cout << "5) Balance" << endl;
        cout << "6) delete a user" << endl;
        choice = check_enter_choice(6, 1);
        switch (choice) {
        case 1:
            print_user_by_index(place);
            edit_name(place);
            break;
        case 2:
            print_user_by_index(place);
            edit_email(place);
            break;
        case 3:
            print_user_by_index(place);
            edit_password(place);
            break;
        case 4:
            print_user_by_index(place);
            edit_phone_number(place);
            break;
        case 5:
            print_user_by_index(place);
            edit_balance(place);
            break;
        case 6:
            print_user_by_index(place);
            delete_userAcount(place);
            is_user_deleted = 1;
            break;
        }
        Is_first_loop = 0;
    } while (display_menue_again(choice, 6)); // func display ask user if he want to continue
}




void admin_view() {
    int choice;
    do {

        cout << "Enter your choice: " << endl;
        cout << "1) view by name " << endl;
        cout << "2) view by id  " << endl;
        cout << "3) view all users " << endl;
        cout << "4) Users Informations Edit\n";
        choice = check_enter_choice(4, 1);
        if (choice == -1)
            return;
        if (choice == 1)
            view_by_name();
        else if (choice == 2)
            view_by_ID();
        else if (choice == 3)
            view_all_users();
        else if (choice == 4)
            Edit_useraccount();

    } while (display_menue_again(choice, 4));
}

void build_new_subscr(admin_subsc* subscr_admin) {
    string Periods_Options[4] = { "zone 1", "zone 2", "zone 3&4", "zone 5&6" };
    cout << "Enter the Name of the subscription that you want to add: ";
    cin >> subscr_admin[nsubscrip].name;
    for (int nzone = 0; nzone < 4; nzone++) {
        cout << "Enter the price of " << Periods_Options[nzone] << " Monthly in "
            << subscr_admin[nsubscrip].name << " Subscription ";
        cin >> subscr_admin[nsubscrip].prices[nzone][0];
        cout << "Enter the price of " << Periods_Options[nzone]
            << " in Quarter year in " << subscr_admin[nsubscrip].name
            << " Subscription ";
        cin >> subscr_admin[nsubscrip].prices[nzone][1];
        cout << "Enter the price of " << Periods_Options[nzone] << " Yearly in "
            << subscr_admin[nsubscrip].name << " Subscription ";
        cin >> subscr_admin[nsubscrip].prices[nzone][2];
        cout << endl;
    }
    nsubscrip++;
}
void edit_subscr_name(int place, admin_subsc* subscr_admin) {
    cout << "Enter the new subscription name: ";
    string name;
    cin >> name;
    subscr_admin[place].name = name;
}
void display_prices_subsc(
    int place, int nzone,
    admin_subsc* subscr_admin) { // you can add a condition when subscription
    // apears to user to avoid
// displaying price if it equal zero
    cout << "1) Monthly Subscription:  " << subscr_admin[place].prices[nzone][0]
        << " L.E" << endl;
    cout << "2) Quarter Year Subscription: "
        << subscr_admin[place].prices[nzone][1] << " L.E" << endl;
    cout << "3) Annual Subscription:  " << subscr_admin[place].prices[nzone][2]
        << " L.E" << endl;
}
void edit_price_subsc_by_nzone(int place, int nzone,
    admin_subsc* subscr_admin) {
    // we have to edit on the main project function to access new prices
    cout << "Which Period do you want to edit?" << endl;
    display_prices_subsc(place, nzone, subscr_admin);
    int choice_period = check_enter_choice(3, 1) - 1;

    if (choice_period < 0)
        return;
    string periods[3]{ "Monthly", "Quartrer of year", "Annualy" };
    cout << "Please enter the new Price of " << periods[choice_period]
        << " Subscription: ";
    int price;
    cin >> price;
    subscr_admin[place].prices[nzone][choice_period] = price;
}
void edit_subscr_price(int place, admin_subsc* subscr_admin) {

    int nzone;
    do {
        cout << "enter the number of zone that you want to edit on its price"
            << endl;
        cout << "1.zone(1)" << endl;
        cout << "2.zone(2)" << endl;
        cout << "3.zone(3 or 4)" << endl;
        cout << "4.zone(5 or 6) " << endl;
        nzone = check_enter_choice(4, 1) - 1;
        if (nzone < 0)
            return;
        edit_price_subsc_by_nzone(place, nzone, subscr_admin);
    } while (display_menue_again(nzone, 4));
}
void delete_subscr(int place, admin_subsc* subscr_admin) {
    for (int i = place; i < nsubscrip; i++) {
        swap(subscr_admin[i], subscr_admin[i + 1]);

        // swap(a[2],a[3])
        // swap(a[3],a[4])
        // swap(a[i],a[i+1])  ((i=place))
    }
    if (nsubscrip)
        nsubscrip--;
}
void main_edit_subscr(
    admin_subsc* subscr_admin) { // retrace it and check its validatio
    int choice;
    do {

        int place = 0;
        cout << "**********************************\n";
        cout << "Enter your choice: " << endl;
        cout << "1.Edit subscription name" << endl;
        cout << "2.Edit subscription Prices" << endl;
        cout << "3.Delete a subscription" << endl;
        cout << "4.Add New subscription" << endl;
        choice = check_enter_choice(4, 1);
        if (nsubscrip == 0 && choice != 4) {
            cout << "#### NO SUBSCRIBTION PLEASE ADD at least one (choose 4 to add) "
                "#####"
                << endl;
            return main_edit_subscr(subscr_admin);
        }
        if (choice != 4 && choice != -1)
            place = get_place_subscrip(subscr_admin);

        if (place >= 0)
            switch (choice) {
            case 1:
                edit_subscr_name(place, subscr_admin);
                break;
            case 2:
                edit_subscr_price(place, subscr_admin);
                break;
            case 3:
                delete_subscr(place, subscr_admin);
                break;
            case 4:
                build_new_subscr(subscr_admin);
                break;
            case -1:
                return;
                break;
            }

    } while (display_menue_again(choice, 4));
}

void Manage_Tickets_Prices(int Tickets_Prices[]) {
    int choice;
    cout << "**************Tickets Prices**************\n";
    cout << "1) " << Tickets_Prices[0] << " L.E From 1 Stations To 9 Stations\n";
    cout << "2) " << Tickets_Prices[1]
        << " L.E From 10 Stations To 16 Stations\n";
    cout << "3) " << Tickets_Prices[2]
        << " L.E From 17 Stations To 23 Stations\n";
    cout << "4) " << Tickets_Prices[3] << " L.E More Than 23 Stations\n";
    cout << "5)Return\n";
    cin >> choice;
    int New_Price;
    switch (choice) {
    case 1:
        cout << Tickets_Prices[0] << " L.E From 1 Stations To 9 Stations\n\n";
        cout << "Enter The New Ticket Value\n";
        cin >> New_Price;
        Tickets_Prices[0] = New_Price;
        break;
    case 2:
        cout << Tickets_Prices[1] << " L.E From 10 Stations To 16 Stations\n\n";
        cout << "Enter The New Ticket Value\n";
        cin >> New_Price;
        Tickets_Prices[1] = New_Price;
        break;
    case 3:
        cout << Tickets_Prices[2] << " L.E From 17 Stations To 23 Stations\n\n";
        cout << "Enter The New Ticket Value\n";
        cin >> New_Price;
        Tickets_Prices[2] = New_Price;
        break;
    case 4:
        cout << Tickets_Prices[3] << " L.E More Than 23 Stations\n\n";
        cout << "Enter The New Ticket Value\n";
        cin >> New_Price;
        Tickets_Prices[3] = New_Price;
        break;
    case 5:
        return;

    default:
        cout << "Invalid Choice\n";
        Manage_Tickets_Prices(Tickets_Prices);
    }
}

string Secure_Pass(bool regist) {
    char ch;
    char pass[100];
    cout << "Enter Your Password:";
    ch = _getch();
    int index = 0;

    while (ch != 13) { // Enter Key ASCII
        if (ch == 8) { // Backspace ASCII
            if (index > 0) {
                cout << "\b \b"; // Move cursor back, erase character, move cursor back again
                index--;
            }
        }
        else {
            pass[index++] = ch;
            cout << '*';
        }
        ch = _getch();
    }

    pass[index] = '\0';
    cout << "\nShow The Password ? Y/N\n";
    char Show ;
    cin >> Show;
    while(Show!='Y'&&Show!='N'&&Show!='y'&&Show!='n'){
            cout<<"Invalid Input\n";
                    cin>>Show;
    }

    if (Show=='Y') {
            cout << pass << endl;
        }


    if (regist) {
        cout << "\nConfirm Password\n";
        char Confirmch;
        char Confirmpass[100];
        Confirmch = _getch();
        index = 0;

        while (Confirmch != 13) { // Enter Key ASCII
            if (Confirmch == 8) { // Backspace ASCII
                if (index > 0) {
                    cout << "\b \b";
                    index--;
                }
            }
            else {
                Confirmpass[index++] = Confirmch;
                cout << '*';
            }
                Confirmch = _getch();
        }
        cout << endl;
        Confirmpass[index] = '\0';

        cout << "\nIf You Want To Show The Password Press 1\n";
        char Show ;
    cin >> Show;
       while(Show!='Y'&&Show!='N'&&Show!='y'&&Show!='n'){
            cout<<"Invalid Input\n";
                    cin>>Show;
    }

        if (Show=='Y') {
            cout << Confirmpass << endl;
        }



        if (strcmp(pass, Confirmpass) != 0) {
            cout << "\nPasswords do not match!\n ";
            return Secure_Pass(true); // Recursively call with regist=true
        }
        else
            cout << "Matched\n";
    }

    return string(pass);
}
bool type_of_user(string mail)
{
    string check = "admn";
    int size_mail, size_check;
    size_mail = mail.size();
    size_check = check.size();
    for (int i = 0; i < size_mail; i++)
    {
        if (check[0] == mail[i])
        {
            if (check[1] == mail[i + 1])
            {
                if (check[2] == mail[i + 2])
                {
                    if (check[3] == mail[i + 3])
                    {
                        return true;
                    }
                    else continue;
                }
                else continue;
            }
            else continue;
        }
        else continue;
    }return false;
}
bool find(string mail) // find the user function
{

    for (int i = 0; i < UsersCount; i++)
        if (UserAccounts[i].AccUser.Email == mail)
            return true;

    return false;
}
bool Find_User(string Mail_Phone, string password) {
    int ID;
    for (int i = 0; i < UsersCount; i++)
        if ((UserAccounts[i].AccUser.Email == Mail_Phone ||
            UserAccounts[i].AccUser.Phone_Number == Mail_Phone) &&
            UserAccounts[i].AccUser.Password == password) {
            Index_Of_Target_User = i;
            return true;
        }
    return false;
}
void Register() {
    string mail;
    string FName;
    string LName;

    string Password;
    string Phone_Number;
    float Balance;

    do {
        cout << "Enter your First Name: ";
        cin >> FName;
        cout << "Enter your Last Name: ";
        cin >> LName;
        cout << "Enter your Email: ";
        cin >> mail;


        cout << "Enter your Phone Number:";
        cin >> Phone_Number;

        Password = Secure_Pass(1);
        if( UserAccounts[UsersCount].AccUser.Admin = type_of_user(mail)&&!find(mail))
            break;
        cout << "Entrer your Balance:";
        cin >> Balance;
    } while (find(mail));

    UserAccounts[UsersCount].AccUser.Admin = type_of_user(mail);
    UserAccounts[UsersCount].AccUser.First_Name = FName;
    UserAccounts[UsersCount].AccUser.Last_Name = LName;

    UserAccounts[UsersCount].AccUser.Email = mail;
    UserAccounts[UsersCount].AccUser.Password = Password;
    UserAccounts[UsersCount].AccUser.Phone_Number = Phone_Number;
    UserAccounts[UsersCount].AccUser.Balance = Balance;
    UserAccounts[UsersCount].AccUser.ID =
        Random_ID_Generate(UserAccounts[UsersCount].AccUser.ID);
    UsersCount++;
}

/////

/////

bool login() {
    string email_phone_num, password;

    cout << "Please enter email or phone number :      ";
    cin >> email_phone_num;

    password = Secure_Pass(0);
    if (!Find_User(email_phone_num, password)) {
        cout << "Invalid Email/Phone or password\n";
        return false;
    }

    return true;
}

/////////////Logic///////////
void User_Data_From_File() {
   fstream From_File("User.txt", ios::in);

    if (!From_File.is_open()) {
       cout << "Error opening file." << endl;
       return;
    }
   int i = 0;
    while (i < Max_Current_Users_Size &&
        From_File >> UserAccounts[i].AccUser.First_Name) {
        From_File >> UserAccounts[i].AccUser.Last_Name;
        From_File >> UserAccounts[i].AccUser.ID;
        From_File >> UserAccounts[i].AccUser.Email;
        From_File >> UserAccounts[i].AccUser.Admin;
        From_File >> UserAccounts[i].AccUser.Password;
        From_File >> UserAccounts[i].AccUser.Phone_Number;
        From_File >> UserAccounts[i].AccUser.Balance;
        From_File >> UserAccounts[i].AccUser.Rides_Count;
        From_File >> UserAccounts[i].AccUser.stations;
       i++;
    }
   UsersCount = i; // Done


   From_File.close();
}

void metro_system() {
    User_Data_From_File();

    string zones[11][11] = {

    {"al shohadaa", "ataba", "naguib", "saad", "zaghloul", "orabi", "nasser",
     "opera", "sadat"},

    {"al sayyeda zeinab", "el malek el saleh", "mar girgis", "el zahraa",
     "dar el salam"},

    {"dokki", "bohooth", "cairo university", "faisal", "giza",
     "omm el misryeen", "sakiat mekki", "el mounib"},

    {"al ahram", "koleyet el banat", "cairo stadium", "fair zone", "abbassia",
     "abdou pasha", "el geish", "bab el shaaria"},

    {"saray el qobba", "hammamat el qobba", "kobri el qobba",
     "manshiet el sadr", "el demerdash", "ghamra"},

    {"shobra el kheima", "koliet el zeraa", "mezallat", "khalafawy",
     "sainte teresa", "road el farag", "massara"},

    {"hadayeq el maadi", "maadi", "thakanat el maadi", "tora el balad",
     "kozzika", "tora el asmant"},

    {"new el marg", "el marg", "ezbet el nakhl", "ain shams", "el matareyya",
     "helmeyet el zaitoun", "hadayeq el zaitoun"},

    {"el maasara", "hadayeq helwan", "wadi hof", "helwan university",
     "ain helwan", "helwan"},

    {"haroun", "heliopolis", "alf masken", "el shams club", "el nozha",
     "hesham barakat", "qubaa", "omar ibn el khattab", "haykestep",
     "adly mansour"},

    {"maspero", "safaa hijazy", "kit kat", "sudan", "imbaba", "el bohy",
     "el qawmia", "ring road", "rod el farg corridor"} };



    int Tickets_Prices[4] = {6, 8, 12, 15};

    admin_subsc Subscripitions_Plans[10];

    initializeSubscriptions(Subscripitions_Plans);

    int choice;
    bool loggedIn = false;
    while (!loggedIn) {
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Register();
                break;
            case 2:
                loggedIn = login();
                break;
            case 3:
                cout << "Exiting program." << endl;
                // No need to delete UserAccounts here if it's not dynamically allocated
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        // Assuming UserAccounts and Index_Of_Target_User are defined elsewhere
        // and their usage is correct
        if (loggedIn) {
            if (UserAccounts[Index_Of_Target_User].AccUser.Admin) {
                while (true) {
                    cout << "1)Ticket Prices\n";
                    cout << "2)Subscriptions Management\n";
                    cout << "3)User Management\n";
                    cout << "4)Stations Management\n";
                    cout << "5)Peak Hours\n";

                    cout << "6)Statstics\n";

                    cout << "7)Log Out\n";
                    cout << "Enter your choice: ";
                    int Admin_Choice;
                    cin >> Admin_Choice;
                    switch (Admin_Choice) {
                        case 1:
                            Manage_Tickets_Prices(Tickets_Prices);
                            break;
                        case 2:
                            main_edit_subscr(Subscripitions_Plans);
                            break;
                        case 3:
                            admin_view();
                            break;
                        case 4:
                            main_station_managment(zones);
                            break;
//                            case 5:
//                            ad_peak_hours();
//                            break;

//                            case 6:
//                            ad_statistics_station();
//                            break;

                        case 7:
                            loggedIn = false;
                            metro_system();
                            break;
                        default:
                            check_enter_choice(7, 0);
                    }
                }
            } else {
                while (true) {
                          int BeginingLine, EndLine, BeginingStation, EndStation;
                            bool Done_CheckIn = false;
                            bool Done_CheckOut = false;
                    cout << "1)Buy A Ticket \n";
                    cout << "2)Take A Ride \n";
                    cout << "3)Purchase A Subscription Plan \n";
                    cout << "4)Manage Subscription\n";
                    cout << "5)Update Info \n";
                    cout << "6)View History Of Rides \n";
                    cout << "7)Log Out \n";
                    int User_Choice;
                    cout << "Enter your choice: ";
                    cin >> User_Choice;
                    switch (User_Choice) {
                        case 1:
                            Buy_Ticket(Tickets_Prices);
                            break;
                        case 2:
                            Take_Ride(BeginingLine, BeginingStation, EndLine, EndStation, Tickets_Prices, Done_CheckIn, Done_CheckOut);


                            break;
                        case 3:
                            Purchase_Subscripition(Subscripitions_Plans, zones);
                            break;
                        case 4:

                            Manage_Subscription(Subscripitions_Plans, zones);
                            break;

                        case 5:
                            Update_Info();
                            break;
                        case 6:
                            View_History_Of_Rides();
                            break;
                        case 7:
                            loggedIn = false;
                            metro_system();
                            break;
                        default:
                            check_enter_choice(7, 0);
                    }
                }
            }
        }
    }
}

int main() {
    metro_system();

    return 0;


}
