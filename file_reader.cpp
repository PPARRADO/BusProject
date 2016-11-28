#include "file_reader.h"

int ALGO_File_Check(const char *_file_name) {
    struct stat s;
    //Check if the file exist
    if( stat(_file_name,&s) == 0 ) {
        if( S_ISREG(s.st_mode) ) {
            //Then check if the file is the right type
            if ( strlen(_file_name) < 5 || _file_name[strlen(_file_name)-3] != 'c' || _file_name[strlen(_file_name)-2] != 's' || _file_name[strlen(_file_name)-1] != 'v' ) {
                cout << "|-ERR :" << endl ;
                cout << "|-\tWrong file type : .CSV ONLY" << endl ;
                return 1 ;
            } else {
                cout << "|-File found : " << _file_name << endl ;
            }
        } else {
            cout << "|-ERR :" << endl ;
            cout << "|-\tWrong file name or does not exist." << endl ;
            return 1 ;
        }
    } else {
        cout << "|-ERR :" << endl ;
        cout << "|-\tWrong file name or does not exist." << endl ;
        return 1 ;
    }

    return 0 ;
}

double ALGO_File_Char_To_Double(char* _number) {
    double _double = 0 ;
    sscanf(_number,"%lf",&_double) ;
    return _double ;
}

double ALGO_File_Char_To_Minute(char* _number) {
    double hour = -1 ;
    double minute = 0 ;
    char* char_value = new char[ALGO_CHAR_LENGTH] ;
    sprintf(char_value, "") ;
    for( unsigned int i = 0 ; i < strlen(_number) ; i++ ) {
        if( _number[i] == ':' ) {
            hour = ALGO_File_Char_To_Double(char_value) ;
            sprintf(char_value, "") ;
        } else {
            sprintf(char_value, "%s%c", char_value, _number[i]) ;
        }
    }

    minute = ALGO_File_Char_To_Double(char_value) ;
    if( hour > 0 ) {
        minute += hour*60 ;
    }

    return minute ;
}

vector<int> ALGO_File_Init_Data(int _line_number, int _direction) {
    vector<int> data ;
    data.push_back(0) ; //H-depart
    data.push_back(0) ; //H-arrivee
    data.push_back(0) ; //T-depart
    data.push_back(0) ; //T-arrivee
    data.push_back(0) ; //Distance
    data.push_back(_line_number) ; //N-ligne
    data.push_back(_direction) ; //Sens

    return data ;
}

vector<vector<vector<int> > > ALGO_File_Read_Line_Horraires(FILE *_file, char *_reader) {
    vector<vector<vector<int> > > line_data ;
    int line_number = 0 ;

    ///SET FLAG READER TO ZERRO
    fseek(_file, 0, SEEK_SET) ;

    ///FIND THE TOTAL OF TRAJECT FOR EACH LINES
    int line_pos = 0 ;
    int line_direction = 0 ;
    while( !feof(_file) ) {
        fscanf(_file, "%s", _reader) ;
        if( feof(_file) ) {
            break ;
        }
        if( !strcmp(_reader, "ligne") ) { //Check line number
            if( fgetc(_file) == ' '  ) {
                fscanf(_file, "%s", _reader) ;
                line_pos = ALGO_File_Char_To_Double(_reader) ;
                line_direction = 0 ;
                if( line_data.size() > 0 ) {
                    if( line_data[line_data.size()-1].size() > 0 ) {
                        if( line_data[line_data.size()-1][line_data[line_data.size()-1].size()-1][5] == line_pos ) {
                            line_direction = 1 ;
                        }
                    }
                }
            }
        } else if( !strncmp(_reader, "Dist", 4) ) {
            int total_traject = 0 ;
            for( unsigned int i = 0 ; i < strlen(_reader) ; i++ ) {
                if( _reader[i] == ',' ) {
                    total_traject++ ;
                }
            }

            //Set vector and init value
            vector<vector<int> > internal_data ;
            for( int j = 0 ; j < total_traject ; j++ ) {
                internal_data.push_back(ALGO_File_Init_Data(line_pos, line_direction));
            }
            line_data.push_back(internal_data) ;
        }
    }

    ///SET FLAG READER TO ZERRO
    fseek(_file, 0, SEEK_SET) ;
    line_number = 0 ;

    ///SET EACH TRAJECT DISTANCES
    while( !feof(_file) ) {
        fscanf(_file, "%s", _reader) ;
        if( feof(_file) ) {
            break ;
        }
        if( !strncmp(_reader, "Dist", 4) ) {
            int start_saving = 0 ;
            int traject_number = 0 ;
            char* char_value = new char[ALGO_CHAR_LENGTH] ;
            sprintf(char_value, "") ;
            for( unsigned int i = 0 ; i < strlen(_reader) ; i++ ) {
                if( _reader[i] == ',' ) {
                    if( start_saving ) {
                        line_data[line_number][traject_number][4] = ALGO_File_Char_To_Double(char_value) ;
                        traject_number++ ;
                        sprintf(char_value, "") ;
                    } else {
                        start_saving = 1 ;
                    }
                } else {
                    if( start_saving ) {
                        sprintf(char_value, "%s%c", char_value, _reader[i]) ;
                    }
                }
            }
            line_data[line_number][traject_number][4] = ALGO_File_Char_To_Double(char_value) ;
            line_number++ ;
        }
    }

    ///SET FLAG READER TO ZERRO
    fseek(_file, 0, SEEK_SET) ;
    line_number = 0 ;


    ///SET EACH TRAJECT TERMINUS AND TIME
    while( !feof(_file) ) {
        fscanf(_file, "%s", _reader) ;
        if( feof(_file) ) {
            break ;
        }
        if( !strncmp(_reader, "T", 1) ) {
            int terminus_number = -1 ;
            int traject_number = 0 ;
            char* char_value = new char[ALGO_CHAR_LENGTH] ;
            sprintf(char_value, "") ;
            for( unsigned int i = 1 ; i < strlen(_reader) ; i++ ) {
                if( _reader[i] == ',' ) {
                    break ;
                } else {
                    sprintf(char_value, "%s%c", char_value, _reader[i]) ;
                }
            }
            terminus_number = ALGO_File_Char_To_Double(char_value) ;
            sprintf(char_value, "") ;


            int start_saving = 0 ;
            for( unsigned int i = 1 ; i < strlen(_reader) ; i++ ) {
                if( _reader[i] == ',' ) {
                    if( start_saving ) {
                        int hour = ALGO_File_Char_To_Minute(char_value) ;
                        if( hour > 0 && line_data[line_number][traject_number][0] == 0 ) {
                            line_data[line_number][traject_number][0] = hour ;
                            line_data[line_number][traject_number][2] = terminus_number ;
                        }
                        if( hour > 0 ) {
                            line_data[line_number][traject_number][1] = hour ;
                            line_data[line_number][traject_number][3] = terminus_number ;
                        }
                        traject_number++ ;
                        sprintf(char_value, "") ;
                    } else {
                        start_saving = 1 ;
                    }
                } else {
                    if( start_saving ) {
                        sprintf(char_value, "%s%c", char_value, _reader[i]) ;
                    }
                }
            }

            int hour = ALGO_File_Char_To_Minute(char_value) ;
            if( hour > 0 && line_data[line_number][traject_number][0] == 0 ) {
                line_data[line_number][traject_number][0] = hour ;
                line_data[line_number][traject_number][2] = terminus_number ;
            }
            if( hour > 0 ) {
                line_data[line_number][traject_number][1] = hour ;
                line_data[line_number][traject_number][3] = terminus_number ;
            }
        } else if( !strncmp(_reader, "Dist", 4) ) {
            line_number++ ;
        }
    }

    return line_data ;
}

vector<int> ALGO_File_Init_Data_Simple(int _line_size) {
    vector<int> data ;

    for( int i = 0 ; i < _line_size ; i++ ) {
        data.push_back(0) ;
    }

    return data ;
}

vector<vector<int> > ALGO_File_Read_Line_Distances(FILE *_file, char *_reader) {
    vector<int> line_top ;
    vector<int> line_left ;
    vector<vector<int> > line_data ;
    int line_number_alpha = 0 ;
    char* char_value = new char[ALGO_CHAR_LENGTH] ;
    sprintf(char_value, "") ;

    ///SET FLAG READER TO ZERRO
    fseek(_file, 0, SEEK_SET) ;

    ///FIND THE TERMINUS'S NAMES FROM THE TOP LINE
    fscanf(_file, "%s", _reader) ;
    for( unsigned int i = 1 ; i < strlen(_reader) ; i++ ) {
        if( _reader[i] == ',' ) {
            if( strlen(char_value) > 0 ) {
                line_top.push_back(ALGO_File_Char_To_Double(char_value)) ;
            }
            sprintf(char_value, "") ;
        } else {
            if( _reader[i] != 'T' ) {
                sprintf(char_value, "%s%c", char_value, _reader[i]) ;
            }
        }
    }
    if( strlen(char_value) > 0 ) {
        line_top.push_back(ALGO_File_Char_To_Double(char_value)) ;
    }

    ///FIND THE TERMINUS'S NAMES FROM THE LEFT LINE
    sprintf(char_value, "") ;
    while( !feof(_file) ) {
        fscanf(_file, "%s", _reader) ;
        if( feof(_file) ) {
            break ;
        }
        for( unsigned int i = 0 ; i < strlen(_reader) ; i++ ) {
            if( _reader[i] == ',' ) {
                if( strlen(char_value) > 0 ) {
                    line_left.push_back(ALGO_File_Char_To_Double(char_value)) ;
                    line_data.push_back(ALGO_File_Init_Data_Simple(line_top.size())) ;
                }
                sprintf(char_value, "") ;
                break ;
            } else {
                if( _reader[i] != 'T' ) {
                    sprintf(char_value, "%s%c", char_value, _reader[i]) ;
                }
            }
        }
    }
    if( strlen(char_value) > 0 ) {
        line_left.push_back(ALGO_File_Char_To_Double(char_value)) ;
    }

    ///SET FLAG READER TO ZERRO
    fseek(_file, 0, SEEK_SET) ;

    ///SAVE ALL VALUES
    fscanf(_file, "%s", _reader) ;
    while( !feof(_file) ) {
        fscanf(_file, "%s", _reader) ;
        if( feof(_file) ) {
            break ;
        }

        int start_saving = 0 ;
        int line_number_beta = 0 ;
        sprintf(char_value, "") ;
        for( unsigned int i = 0 ; i < strlen(_reader) ; i++ ) {
            if( _reader[i] == ',' ) {
                if( start_saving ) {
                    line_data[line_number_alpha][line_number_beta] = ALGO_File_Char_To_Double(char_value) ;
                    sprintf(char_value, "") ;
                    line_number_beta++ ;
                } else {
                    start_saving = 1 ;
                }
            } else {
                if( start_saving ) {
                    sprintf(char_value, "%s%c", char_value, _reader[i]) ;
                }
            }
        }
        if( start_saving ) {
            line_data[line_number_alpha][line_number_beta] = ALGO_File_Char_To_Double(char_value) ;
        }
        line_number_alpha++ ;
    }

    return line_data ;
}

void ALGO_File_Load(const char *_file_name) {
    FILE *file = NULL ;
    file = fopen(_file_name, "r") ;

    if( file != NULL ) { //Check if the file is correctly opened
        char *reader = new char[ALGO_CHAR_LONG_LENGTH] ;
        if( !strncmp(_file_name, "horaires.csv", 5)) {
           vector<vector<vector<int> > > result = ALGO_File_Read_Line_Horraires(file, reader) ;
/*
            for( int i = 0 ; i < result.size() ; i++ ) {
                cout << i << endl ;
                for( int j = 0 ; j < result[i].size() ; j++ ) {
                    cout << " - " << j << " -\t" << result[i][j][0] << endl ;
                    for( int k = 1 ; k < result[i][j].size() ; k++ ) {
                        cout << "     -\t" << result[i][j][k] << endl ;
                    }
                }
            }
*/
        } else if( !strncmp(_file_name, "dist_terminus.csv", 5)) {
           vector<vector<int> > result = ALGO_File_Read_Line_Distances(file, reader) ;
/*
            for( int i = 0 ; i < result.size() ; i++ ) {
                for( int j = 0 ; j < result[i].size() ; j++ ) {
                    cout << result[i][j] << " " ;
                }
                cout << endl ;
            }
*/
        } else if( !strncmp(_file_name, "terminus.csv", 5)) {
           vector<vector<int> > result = ALGO_File_Read_Line_Distances(file, reader) ;
/*
            for( int i = 0 ; i < result.size() ; i++ ) {
                for( int j = 0 ; j < result[i].size() ; j++ ) {
                    cout << result[i][j] << " " ;
                }
                cout << endl ;
            }
*/
        }
        fclose(file) ;
    }
}

int ALGO_File_Quick(const char *_file_name) {
    if( ALGO_File_Check(_file_name) ) return -1 ;
    ALGO_File_Load(_file_name) ;

    return 0 ;
}

Base* ALGO_File(int _show_data) {
    Base* base ;
    FILE* file = NULL ;
    vector<vector<vector<int> > > vec_horaires ;
    vector<vector<int> > vec_distances ;
    vector<vector<int> > vec_temps ;

    if( ALGO_File_Check("../horaires.csv") ) {
        exit(0) ;
    }
    file = fopen("../horaires.csv", "r") ;
    if( file != NULL ) { //Check if the file is correctly opened
        char *reader = new char[ALGO_CHAR_LONG_LENGTH] ;
        vec_horaires = ALGO_File_Read_Line_Horraires(file, reader) ;
        fclose(file) ;
    }
    file = NULL ;

    if( ALGO_File_Check("../dist_terminus.csv") ) {
        exit(0) ;
    }
    file = fopen("../dist_terminus.csv", "r") ;
    if( file != NULL ) { //Check if the file is correctly opened
        char *reader = new char[ALGO_CHAR_LONG_LENGTH] ;
        vec_distances = ALGO_File_Read_Line_Distances(file, reader) ;
        fclose(file) ;
    }
    file = NULL ;

    if( ALGO_File_Check("../terminus.csv") ) {
        exit(0) ;
    }
    file = fopen("../terminus.csv", "r") ;
    if( file != NULL ) { //Check if the file is correctly opened
        char *reader = new char[ALGO_CHAR_LONG_LENGTH] ;
        vec_temps = ALGO_File_Read_Line_Distances(file, reader) ;
        fclose(file) ;
    }

    if( _show_data ) {
        cout << "|- horaires : "<< endl ;
        for( int i = 0 ; i < vec_horaires.size() ; i++ ) {
            cout << i << endl ;
            for( int j = 0 ; j < vec_horaires[i].size() ; j++ ) {
                cout << " - " << j << " -\t" << vec_horaires[i][j][0] << endl ;
                for( int k = 1 ; k < vec_horaires[i][j].size() ; k++ ) {
                    cout << "     -\t" << vec_horaires[i][j][k] << endl ;
                }
            }
        }

        cout << "|- distance terminus : "<< endl ;
        for( int i = 0 ; i < vec_distances.size() ; i++ ) {
            for( int j = 0 ; j < vec_distances[i].size() ; j++ ) {
                cout << vec_distances[i][j] << " " ;
            }
            cout << endl ;
        }

        cout << "|- temps terminus : "<< endl ;
        for( int i = 0 ; i < vec_temps.size() ; i++ ) {
            for( int j = 0 ; j < vec_temps[i].size() ; j++ ) {
                cout << vec_temps[i][j] << " " ;
            }
            cout << endl ;
        }
    }

    vector<Trajet> HoraireEs;
    vector<Trajet> HoraireHs;

    if( vec_horaires.size() > 0 && vec_distances.size() > 0 && vec_temps.size() > 0 ) {
        if( vec_distances.size() == vec_temps.size() && vec_distances[0].size() == vec_temps[0].size() ) {

            //HoraireEs.push_back(Trajet(1,1,2,371,408,37,10,'a'));

            for( int i = 0 ; i < vec_horaires.size() ; i++ ) {
                for( int j = 0 ; j < vec_horaires[i].size() ; j++ ) {
                    char direction = vec_horaires[i][j][6]==0?'a':'r' ;
                    HoraireEs.push_back(Trajet(vec_horaires[i][j][5],vec_horaires[i][j][2], vec_horaires[i][j][3], vec_horaires[i][j][0], vec_horaires[i][j][1], vec_horaires[i][j][1] - vec_horaires[i][j][0], vec_horaires[i][j][4], direction));
                }
            }

            for( int i = 0 ; i < vec_distances.size() ; i++ ) {
                for( int j = 0 ; j < vec_distances[i].size() ; j++ ) {
                    HoraireHs.push_back(Trajet(0,i, j, 0, 0, vec_temps[i][j], vec_distances[i][j], 'n'));
                }
            }

            if( _show_data ) {
                cout << HoraireEs[HoraireEs.size()-1].getNumeroDeLigne() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getPointDepart() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getPointArrivee() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getHeureDepart() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getHeureArrivee() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getTemps() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getDistance() << endl ;
                cout << HoraireEs[HoraireEs.size()-1].getSens() << endl ;
                cout << endl ;

                cout << HoraireHs[24*2+12].getPointDepart() << endl ;
                cout << HoraireHs[24*2+12].getPointArrivee() << endl ;
                cout << HoraireHs[24*2+12].getTemps() << endl ;
                cout << HoraireHs[24*2+12].getDistance() << endl ;
            }

            base = new Base(HoraireEs, HoraireHs);
            base->setHorairHsSize(vec_distances.size()) ;
        } else {
            cout << "|-ERROR, dist. and time vector doesn't match..." << endl ;
            exit(0) ;
        }
    } else {
        cout << "|-ERROR, there is no data in your vector..." << endl ;
        exit(0) ;
    }

    return base ;
}
