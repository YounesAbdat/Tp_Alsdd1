#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
//=========================================================

// ANSI color escape codes
#define ANSI_COLOR_RESET   "\033[0m"
#define ANSI_COLOR_BLACK   "\033[30m"
#define ANSI_COLOR_RED     "\033[31m"
#define ANSI_COLOR_GREEN   "\033[32m"
#define ANSI_COLOR_YELLOW  "\033[33m"
#define ANSI_COLOR_BLUE    "\033[34m"
#define ANSI_COLOR_MAGENTA "\033[35m"
#define ANSI_COLOR_CYAN    "\033[36m"
#define ANSI_COLOR_WHITE   "\033[37m"
#define ANSI_COLOR_BG_BLACK   "\033[40m"
#define ANSI_COLOR_BG_RED     "\033[41m"
#define ANSI_COLOR_BG_GREEN   "\033[42m"
#define ANSI_COLOR_BG_YELLOW  "\033[43m"
#define ANSI_COLOR_BG_BLUE    "\033[44m"
#define ANSI_COLOR_BG_MAGENTA "\033[45m"
#define ANSI_COLOR_BG_CYAN    "\033[46m"
#define ANSI_COLOR_BG_WHITE   "\033[47m"
//==========================================================
//------------------------------Questions--------------------------------------
typedef struct question {
    int id;
    char domaine[100];
    int difficulte;
    char content[1000]; 
    char solution[1000];
    struct question *next;
} question;

typedef question *ptr;

//===========================================PLAYERS====================================
typedef struct player {
    int idp; // index of the player
    char pseudo[100];
    char date[1000];
    char domaines[1000];
    int n_partie; //nombre des parties joués   
    int score;
    struct player *next;
} player;
typedef player *qtr;

// Function prototype declarations
void free_list(ptr liste);
ptr choisir_question_aleatoire(ptr liste, char** propositions);
ptr add_question(ptr liste);
ptr delete_question(ptr liste, int target_id);
qtr add_player(qtr liste, ptr questions);
qtr delete_player(qtr liste, int target_idp);

//===============================machine abstract======================================
void allocate_question(ptr* p) {
    *p = (ptr)malloc(sizeof(question));
}

//-----------------------
int id(ptr p) {
    return(p->id);
}

char* domaine(ptr p) {
    return(p->domaine);
}

int difficulte(ptr p) {
    return(p->difficulte);
}

char* content(ptr p) {
    return p->content;
}

char* solution(ptr p) {
    return(p->solution);
}

ptr next_question(ptr p) {
    return (p->next);
}

//-----------------------------
void ass_id(ptr p, int x) {
    p->id = x;
}

void ass_domaine(ptr p, const char* str) {
    strcpy(p->domaine, str);  
}

//------------------------------
void ass_difficulte(ptr p, int x) {
    p->difficulte = x;
}

void ass_content(ptr p, const char* str) {
    strcpy(p->content, str);
}

void ass_solution(ptr p, const char* str) {
    strcpy(p->solution, str);
}

void ass_adr_question(ptr p, ptr q) {
    p->next = q;
}

//=======================================================================================

//---------------------------------------------------------------------------------------
void allocate_player(qtr* p) {
    *p = (qtr)malloc(sizeof(player));
}

//-----------------------
int idp(qtr p) {
    return(p->idp); 
}

char* pseudo(qtr p) {
    return(p->pseudo);
}

char* date(qtr p) {
    return(p->date);
}

char* domaines(qtr p) {
    return p->domaines;
}
int score(qtr p) {
    return(p->score);
}

int n_partie(qtr p) {
    return(p->n_partie);
}

qtr next_player(qtr p) {
    return (p->next);
}

//-----------------------------
void ass_idp(qtr p, int x) {
    p->idp = x;
}
void ass_pseudo(qtr p, const char* str) {
    strcpy(p->pseudo, str);  
}

void ass_date(qtr p, const char* str) {
    strcpy(p->date, str);  
}
void ass_domaines(qtr p, const char* str) {
    strcpy(p->domaines, str);  
}
void ass_n_partie(qtr p, int x) {
    p->n_partie = x;
}

void ass_score(qtr p, int x) {
    p->score = x;
}
void ass_adr_player(qtr p, qtr q) {
    p->next = q;
}

//=======================================================================================

// =============================== PARTIE ABSTRACT MACHINE ===============================
typedef struct question_partie question_partie;
typedef struct partie partie;

// ------------------------------- Question Partie -------------------------------
typedef struct question_partie {
    int id_question;
    char reponse_joueur[1000];
    int est_domaine_prefere;
    int score_question;
    struct question_partie *next;
} question_partie;

typedef question_partie *ptr_question_partie;

// Allocation
void allocate_question_partie(ptr_question_partie *p) {
    *p = (ptr_question_partie)malloc(sizeof(question_partie));
}

// Accessors
int id_question_partie(ptr_question_partie p) {
    return p->id_question;
}

char* reponse_joueur(ptr_question_partie p) {
    return p->reponse_joueur;
}

int est_domaine_prefere(ptr_question_partie p) {
    return p->est_domaine_prefere;
}

int score_question_partie(ptr_question_partie p) {
    return p->score_question;
}

ptr_question_partie next_question_partie(ptr_question_partie p) {
    return p->next;
}

// Assigners
void ass_id_question_partie(ptr_question_partie p, int x) {
    p->id_question = x;
}

void ass_reponse_joueur(ptr_question_partie p, const char* str) {
    strncpy(p->reponse_joueur, str, 999);
    p->reponse_joueur[999] = '\0';
}

void ass_est_domaine_prefere(ptr_question_partie p, int x) {
    p->est_domaine_prefere = x;
}

void ass_score_question_partie(ptr_question_partie p, int x) {
    p->score_question = x;
}

void ass_adr_question_partie(ptr_question_partie p, ptr_question_partie q) {
    p->next = q;
}

// ------------------------------- Partie -------------------------------
typedef struct partie {
    int idplayer;
    char pseudo[100];
    int niv_partie;
    char domaines[1000];
    ptr_question_partie questions;
    int score;
    struct partie *next;
} partie;

typedef partie *ptr_partie;

// Allocation
void allocate_partie(ptr_partie *p) {
    *p = (ptr_partie)malloc(sizeof(partie));
}

// Accessors
int idplayer_partie(ptr_partie p) {
    return p->idplayer;
}

char* pseudo_partie(ptr_partie p) {
    return p->pseudo;
}

int niv_partie(ptr_partie p) {
    return p->niv_partie;
}

char* domaines_partie(ptr_partie p) {
    return p->domaines;
}

ptr_question_partie questions_partie(ptr_partie p) {
    return p->questions;
}

int score_partie(ptr_partie p) {
    return p->score;
}

ptr_partie next_partie(ptr_partie p) {
    return p->next;
}

// Assigners
void ass_idplayer_partie(ptr_partie p, int x) {
    p->idplayer = x;
}

void ass_pseudo_partie(ptr_partie p, const char* str) {
    strncpy(p->pseudo, str, 99);
    p->pseudo[99] = '\0';
}

void ass_niv_partie(ptr_partie p, int x) {
    p->niv_partie = x;
}

void ass_domaines_partie(ptr_partie p, const char* str) {
    strncpy(p->domaines, str, 999);
    p->domaines[999] = '\0';
}

void ass_questions_partie(ptr_partie p, ptr_question_partie q) {
    p->questions = q;
}

void ass_score_partie(ptr_partie p, int x) {
    p->score = x;
}

void ass_adr_partie(ptr_partie p, ptr_partie q) {
    p->next = q;
}

//=======================================================================================

// Function to free the list of questions
void free_list(ptr liste) {
    ptr current = liste;
    ptr next_node;
    while (current != NULL) {
        next_node = next_question(current);
        free(current);
        current = next_node;
    }
}

// Function to free the list of players
void free_players(qtr liste) {
    qtr current = liste;
    qtr next_node;
    while (current != NULL) {
        next_node = next_player(current);
        free(current);
        current = next_node;
    }
}

// Function to create the list of questions from a text file
ptr creer_liste(char* filename) {
    printf("Opening file: %s\n", filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("fichier introuvable\n");
        return NULL;
    }
    ptr liste = NULL;
    ptr courant = NULL;
    ptr nouvelle = NULL;

    char line[2000];

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        int id;
        char domaine[100];
        int difficulte;
        char content[1000];
        char solution[1000];

        int offset;
        if (sscanf(line, "%d %s %d%n", &id, domaine, &difficulte, &offset) != 3) {
            printf("Failed to parse initial fields: %s\n", line);
            continue;
        }

        char* remaining = line + offset;
        char* last_space = strrchr(remaining, ' ');
        if (last_space == NULL) {
            printf("No solution found: %s\n", line);
            continue;
        }

        strcpy(solution, last_space + 1);
        *last_space = '\0';
        strcpy(content, remaining);

        printf("Parsed: id=%d, domaine=%s, difficulte=%d, content='%s', solution='%s'\n",
               id, domaine, difficulte, content, solution);

        allocate_question(&nouvelle);
        if (nouvelle == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            return NULL;
        }

        ass_id(nouvelle, id);
        ass_domaine(nouvelle, domaine);
        ass_difficulte(nouvelle, difficulte);
        ass_content(nouvelle, content);
        ass_solution(nouvelle, solution);

        if (liste == NULL) {
            liste = nouvelle;
            courant = nouvelle;
        } else {
            ass_adr_question(courant, nouvelle);
            courant = nouvelle;
        }
    }

    fclose(file);
    return liste;
}

// Function to print the list of questions
void print_list(ptr p) {
    while (p != NULL) {
        printf("id : %d\ndomaine : %s\ndifficulte : %d\ncontent : %s\nsolution : %s\n",
               id(p), domaine(p), difficulte(p), content(p), solution(p));
        p = next_question(p);
    }
}

// Function to create a list of players from a file
// Function to create a list of players from a file
qtr creer_liste_players(char* filename) {
    printf("Opening player file: %s\n", filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("fichier introuvable\n");
        return NULL;
    }

    qtr liste = NULL;
    qtr courant = NULL;
    qtr nouvelle = NULL;

    char line[2000];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        int idp, n_partie, score;
        char pseudo[100];
        char date[1000];
        char domaines[1000];

        int parsed = sscanf(line, "%d %99s %999s %999s %d %d",
                           &idp, pseudo, date, domaines, &n_partie, &score);

        if (parsed != 6) {
            printf("Failed to parse line: %s\n", line);
            continue;
        }

        allocate_player(&nouvelle);
        
        ass_idp(nouvelle, idp);
        ass_pseudo(nouvelle, pseudo);
        ass_date(nouvelle, date);
        ass_domaines(nouvelle, domaines);
        ass_n_partie(nouvelle, n_partie);
        ass_score(nouvelle, score);
        ass_adr_player(nouvelle, NULL);

        if (liste == NULL) {
            liste = nouvelle;
            courant = nouvelle;
        } else {
            ass_adr_player(courant, nouvelle);
            courant = nouvelle;
        }
    }

    fclose(file);
    return liste;
}
// Function to print the list of players
void print_players(qtr p) {
    while (p != NULL) {
        printf("ID: %d\n", idp(p));
        printf("Pseudo: %s\n", pseudo(p));
        printf("Date: %s\n", date(p));
        printf("Domaines préférés: %s\n", domaines(p));
        printf("Parties jouées: %d\n", n_partie(p));
        printf("Score total: %d\n", score(p));
        printf("-----------------------------\n");
        p = next_player(p);
    }
}

// Function to load propositions from a file
char** load_propositions(const char* filename) {
    char** propositions = calloc(101, sizeof(char*)); // Index 0 unused
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening propositions file!\n");
        return propositions;
    }

    char line[2000];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline

        int id;
        char* rest = line;
        
        // Extract question ID
        if (sscanf(rest, "%d", &id) != 1) continue;
        
        // Find the space after ID
        rest = strchr(rest, ' ');
        if (!rest) continue;
        rest++; // Skip space

        // Store propositions (skip empty lines)
        if (strlen(rest) > 0) {
            propositions[id] = strdup(rest);
        }
    }

    fclose(file);
    return propositions;
}

// Function to calculate the score of a question
int calculer_score_question(ptr question, const char* player_domaines, const char* player_response) {
    // Check if the player's response matches the question's solution
    if (strcmp(player_response, solution(question)) == 0) {
        // Calculate score based on difficulty and preferred domain
        int score = 0;
        int is_preferred_domain = (strstr(player_domaines, domaine(question)) != NULL);

        switch (difficulte(question)) {
            case 1: // Easy
                score = is_preferred_domain ? 1 : 2;
                break;
            case 2: // Medium
                score = is_preferred_domain ? 2 : 3;
                break;
            case 3: // Hard
                score = is_preferred_domain ? 4 : 5;
                break;
            default:
                score = 0; // Invalid difficulty
                break;
        }
        return score;
    } else {
        // Wrong answer
        return 0;
    }
}

// Function to play a session
void jouer_session(qtr player, ptr questions, char** propositions) {
    int difficulty;
    char response[1000];
    ptr selected_question = NULL;

    // Ask for difficulty level
    printf("Entrez le niveau de difficulté (1-3): ");
    scanf("%d", &difficulty);

    if (difficulty < 1 || difficulty > 3) {
        printf("Difficulté invalide. Choisissez 1, 2, ou 3.\n");
        return;
    }

    // Ask if the player wants a question from their preferred domains
    char choice;
    printf("Voulez-vous une question de vos domaines préférés? (o/n): ");
    scanf(" %c", &choice);

    if (choice == 'o' || choice == 'O') {
        // Show preferred domains
        printf("Vos domaines préférés sont: %s\n", domaines(player));

        // Ask the player to choose a domain
        char chosen_domain[100];
        printf("Entrez le domaine que vous souhaitez: ");
        scanf("%99s", chosen_domain);

        // Select a question from the chosen domain and difficulty
        selected_question = choisir_question_aleatoire(questions, propositions);
    } else {
        // Select a random question of the chosen difficulty
        selected_question = choisir_question_aleatoire(questions, propositions);
    }

    if (selected_question == NULL) {
        printf("Aucune question trouvée pour les critères donnés.\n");
        return;
    }

    // Display the question and propositions
    printf("\nQuestion sélectionnée:\n");
    printf("Domaine: %s\n", domaine(selected_question));
    printf("Content: %s\n", content(selected_question));
    if (propositions[id(selected_question)] && strcmp(propositions[id(selected_question)], "-") != 0) {
        printf("Options:\n");
        char* copy = strdup(propositions[id(selected_question)]);
        char* token = strtok(copy, "--");
        while (token) {
            printf("  %s\n", token);
            token = strtok(NULL, "--");
        }
        free(copy);
    } else {
        printf("No multiple-choice options available.\n");
    }

    // Ask the player for their response
    printf("Entrez votre réponse: ");
    scanf(" %[^\n]", response);

    // Calculate the score
    int question_score = calculer_score_question(selected_question, domaines(player), response);
    printf("Votre score pour cette question est: %d\n", question_score);

    // Update the player's total score and game count
    ass_score(player, score(player) + question_score);
    ass_n_partie(player, n_partie(player) + 1);
    printf("Votre score total est maintenant: %d\n", score(player));
}

// Function to split the questions list by difficulty
void eclater_liste(ptr liste, ptr *liste1, ptr *liste2, ptr *liste3) {
    *liste1 = NULL;
    *liste2 = NULL;
    *liste3 = NULL;
    
    ptr current = liste;
    ptr next_node;
    ptr tail1 = NULL, tail2 = NULL, tail3 = NULL;

    while (current != NULL) {
        next_node = next_question(current);  // Fixed function name
        
        switch(difficulte(current)) {
            case 1:
                if (*liste1 == NULL) {
                    *liste1 = current;
                    tail1 = current;
                } else {
                    ass_adr_question(tail1, current);  // Fixed function name
                    tail1 = current;
                }
                break;
            case 2:
                if (*liste2 == NULL) {
                    *liste2 = current;
                    tail2 = current;
                } else {
                    ass_adr_question(tail2, current);
                    tail2 = current;
                }
                break;
            case 3:
                if (*liste3 == NULL) {
                    *liste3 = current;
                    tail3 = current;
                } else {
                    ass_adr_question(tail3, current);
                    tail3 = current;
                }
                break;
        }
        
        ass_adr_question(current, NULL);  // Detach the node properly
        current = next_node;
    }
}

// Function to add a question
ptr add_question(ptr liste) {
    ptr nouvelle = NULL;
    allocate_question(&nouvelle);

    int id, difficulte;
    char domaine[100], content[1000], solution[1000];

    printf("Entrez l'ID de la question: ");
    scanf("%d", &id);
    printf("Entrez le domaine: ");
    scanf("%99s", domaine);
    printf("Entrez la difficulté (1-3): ");
    scanf("%d", &difficulte);
    printf("Entrez la question: ");
    scanf(" %[^\n]", content);
    printf("Entrez la solution: ");
    scanf(" %[^\n]", solution);

    ass_id(nouvelle, id);
    ass_domaine(nouvelle, domaine);
    ass_difficulte(nouvelle, difficulte);
    ass_content(nouvelle, content);
    ass_solution(nouvelle, solution);
    ass_adr_question(nouvelle, liste);

    return nouvelle;
}

// Function to delete a question
ptr delete_question(ptr liste, int target_id) {
    ptr current = liste;
    ptr previous = NULL;

    while (current != NULL) {
        if (id(current) == target_id) {
            if (previous == NULL) {
                liste = next_question(current);
            } else {
                ass_adr_question(previous, next_question(current));
            }
            free(current);
            printf("Question avec ID %d supprimée.\n", target_id);
            return liste;
        }
        previous = current;
        current = next_question(current);
    }

    printf("Aucune question trouvée avec l'ID %d.\n", target_id);
    return liste;
}

// Function to add a player
qtr add_player(qtr liste, ptr questions) {
    qtr nouvelle = NULL;
    allocate_player(&nouvelle);

    int idp, n_partie = 0, score = 0;
    char pseudo[100], date[1000], domaines[1000];

    printf("Entrez l'ID du joueur: ");
    scanf("%d", &idp);
    printf("Entrez le pseudo: ");
    scanf("%99s", pseudo);
    printf("Entrez la date (dd/mm/yyyy): ");
    scanf("%999s", date);

    printf("Domaines disponibles:\n");
    ptr current = questions;
    while (current != NULL) {
        printf("- %s\n", domaine(current));
        current = next_question(current);
    }

    printf("Entrez les domaines préférés (séparés par '-'): ");
    scanf("%999s", domaines);

    ass_idp(nouvelle, idp);
    ass_pseudo(nouvelle, pseudo);
    ass_date(nouvelle, date);
    ass_domaines(nouvelle, domaines);
    ass_n_partie(nouvelle, n_partie);
    ass_score(nouvelle, score);
    ass_adr_player(nouvelle, liste);

    return nouvelle;
}

// Function to delete a player
qtr delete_player(qtr liste, int target_idp) {
    qtr current = liste;
    qtr previous = NULL;

    while (current != NULL) {
        if (idp(current) == target_idp) {
            if (previous == NULL) {
                liste = next_player(current);
            } else {
                ass_adr_player(previous, next_player(current));
            }
            free(current);
            printf("Joueur avec ID %d supprimé.\n", target_idp);
            return liste;
        }
        previous = current;
        current = next_player(current);
    }

    printf("Aucun joueur trouvé avec l'ID %d.\n", target_idp);
    return liste;
}

// Function to choose a random question
ptr choisir_question_aleatoire(ptr liste, char** propositions) {
    char target_domaine[100];
    int target_difficulty;

    printf("Entrez le domaine (e.g., Math, Physics): ");
    scanf("%99s", target_domaine);

    printf("Entrez le niveau de difficulté (1-3): ");
    scanf("%d", &target_difficulty);

    if (target_difficulty < 1 || target_difficulty > 3) {
        printf("Difficulté invalide. Choisissez 1, 2, ou 3.\n");
        return NULL;
    }

    int count = 0;
    ptr current = liste;
    while (current != NULL) {
        if (strcmp(domaine(current), target_domaine) == 0 && difficulte(current) == target_difficulty) {
            count++;
        }
        current = next_question(current);
    }

    if (count == 0) {
        printf("Aucune question trouvée pour '%s' (difficulté %d).\n", target_domaine, target_difficulty);
        return NULL;
    }

    int random_index = rand() % count;
    current = liste;
    int idx = 0;

    while (current != NULL) {
        if (strcmp(domaine(current), target_domaine) == 0 && difficulte(current) == target_difficulty) {
            if (idx == random_index) {
                return current;  // Found the randomly selected question
            }
            idx++;
        }
        current = next_question(current);
    }

    return NULL;  // Should never reach here if count > 0
}

// Function to create and record a game session
ptr_partie partie_Question_reponse(qtr player, ptr questions, char** propositions) {
    // Create new game session
    ptr_partie nouvelle_partie = NULL;
    allocate_partie(&nouvelle_partie);
    
    // Set game session info
    ass_idplayer_partie(nouvelle_partie, idp(player));
    ass_pseudo_partie(nouvelle_partie, pseudo(player));
    ass_domaines_partie(nouvelle_partie, domaines(player));
    ass_score_partie(nouvelle_partie, 0);
    
    // Select game level
    int niveau;
    printf("\nSelect game level (1-3): ");
    scanf("%d", &niveau);
    while (niveau < 1 || niveau > 3) {
        printf("Invalid level. Please enter 1, 2 or 3: ");
        scanf("%d", &niveau);
    }
    ass_niv_partie(nouvelle_partie, niveau);
    
    // Determine question counts based on level
    int easy, medium, hard;
    switch(niveau) {
        case 1: easy = 6; medium = 6; hard = 3; break;
        case 2: easy = 5; medium = 5; hard = 5; break;
        case 3: easy = 2; medium = 5; hard = 8; break;
    }
    
    // Prepare question lists by difficulty
    ptr easy_questions = NULL, medium_questions = NULL, hard_questions = NULL;
    eclater_liste(questions, &easy_questions, &medium_questions, &hard_questions);
    
    // Game loop
    ptr_question_partie current_question_partie = NULL;
    int total_score = 0;
    
    // Process questions for each difficulty level
    for (int i = 0; i < easy + medium + hard; i++) {
        ptr selected_question = NULL;
        int is_preferred = 0;
        char domain_choice[100];
        
        // Determine current difficulty
        int current_difficulty;
        if (i < easy) {
            current_difficulty = 1;
            selected_question = easy_questions;
            easy_questions = next_question(easy_questions);
        } 
        else if (i < easy + medium) {
            current_difficulty = 2;
            selected_question = medium_questions;
            medium_questions = next_question(medium_questions);
        } 
        else {
            current_difficulty = 3;
            selected_question = hard_questions;
            hard_questions = next_question(hard_questions);
        }
        
        // Ask if player wants preferred domain
        printf("\nQuestion %d/%d (Difficulty: %d)\n", i+1, easy+medium+hard, current_difficulty);
        printf("Use preferred domain? (y/n): ");
        char use_preferred;
        scanf(" %c", &use_preferred);
        
        if (tolower(use_preferred) == 'y') {
            printf("Your preferred domains: %s\n", domaines(player));
            printf("Enter domain to use: ");
            scanf("%99s", domain_choice);
            is_preferred = 1;
        }
        
        // Display question
        printf("\nQuestion: %s\n", content(selected_question));
        if (propositions[id(selected_question)] && strcmp(propositions[id(selected_question)], "-") != 0) {
            printf("Options:\n");
            char* copy = strdup(propositions[id(selected_question)]);
            char* token = strtok(copy, "--");
            while (token) {
                printf("  %s\n", token);
                token = strtok(NULL, "--");
            }
            free(copy);
        }
        
        // Get answer
        char response[1000];
        printf("Your answer: ");
        scanf(" %[^\n]", response);
        
        // Calculate score
        int question_score = calculer_score_question(selected_question, domaines(player), response);
        total_score += question_score;
        
        // Create question record
        ptr_question_partie qp = NULL;
        allocate_question_partie(&qp);
        ass_id_question_partie(qp, id(selected_question));
        ass_reponse_joueur(qp, response);
        ass_est_domaine_prefere(qp, is_preferred);
        ass_score_question_partie(qp, question_score);
        
        // Add to game session
        if (current_question_partie == NULL) {
            ass_questions_partie(nouvelle_partie, qp);
        } else {
            ass_adr_question_partie(current_question_partie, qp);
        }
        current_question_partie = qp;
        
        printf("Question score: %d\n", question_score);
    }
    
    // Update total score
    ass_score_partie(nouvelle_partie, total_score);
    
    // Update player's total score and game count
    ass_score(player, score(player) + total_score);
    ass_n_partie(player, n_partie(player) + 1);
    
    printf("\n=== Game Finished! Total Score: %d ===\n", total_score);
    printf("Player's total score is now: %d\n", score(player));
    
    return nouvelle_partie;
}

// Function to print game session details
void print_partie_details(ptr_partie partie) {
    if (!partie) return;
    
    printf("\n=== Game Session Details ===\n");
    printf("Player: %s (ID: %d)\n", pseudo_partie(partie), idplayer_partie(partie));
    printf("Level: %d\n", niv_partie(partie));
    printf("Total Score: %d\n", score_partie(partie));
    printf("Questions:\n");
    
    ptr_question_partie q = questions_partie(partie);
    int question_num = 1;
    while (q) {
        printf("  %d. Q%d: %s (Score: %d)\n", 
               question_num++,
               id_question_partie(q),
               est_domaine_prefere(q) ? "[Preferred]" : "",
               score_question_partie(q));
        q = next_question_partie(q);
    }
}

// Function to sort and display players by score (descending order)
void afficher_joueurs_par_score(qtr liste) {
    if (liste == NULL) {
        printf("No players available.\n");
        return;
    }

    // Create a copy of the list to sort
    qtr sorted_list = NULL;
    qtr current = liste;
    
    while (current != NULL) {
        qtr new_player = NULL;
        allocate_player(&new_player);
        
        // Copy player data
        ass_idp(new_player, idp(current));
        ass_pseudo(new_player, pseudo(current));
        ass_date(new_player, date(current));
        ass_domaines(new_player, domaines(current));
        ass_n_partie(new_player, n_partie(current));
        ass_score(new_player, score(current));
        ass_adr_player(new_player, NULL);
        
        // Insert in sorted position
        if (sorted_list == NULL || score(new_player) >= score(sorted_list)) {
            ass_adr_player(new_player, sorted_list);
            sorted_list = new_player;
        } else {
            qtr temp = sorted_list;
            while (next_player(temp) != NULL && score(new_player) < score(next_player(temp))) {
                temp = next_player(temp);
            }
            ass_adr_player(new_player, next_player(temp));
            ass_adr_player(temp, new_player);
        }
        
        current = next_player(current);
    }

    // Display sorted list
    printf("\nPlayers sorted by score (highest first):\n");
    current = sorted_list;
    while (current != NULL) {
        printf("- %s (Score: %d)\n", pseudo(current), score(current));
        current = next_player(current);
    }

    // Free the temporary sorted list
    free_players(sorted_list);
}

// Function to sort and display players by number of games played (descending order)
void afficher_joueurs_par_parties(qtr liste) {
    if (liste == NULL) {
        printf("No players available.\n");
        return;
    }

    // Create a copy of the list to sort
    qtr sorted_list = NULL;
    qtr current = liste;
    
    while (current != NULL) {
        qtr new_player = NULL;
        allocate_player(&new_player);
        
        // Copy player data
        ass_idp(new_player, idp(current));
        ass_pseudo(new_player, pseudo(current));
        ass_date(new_player, date(current));
        ass_domaines(new_player, domaines(current));
        ass_n_partie(new_player, n_partie(current));
        ass_score(new_player, score(current));
        ass_adr_player(new_player, NULL);
        
        // Insert in sorted position
        if (sorted_list == NULL || n_partie(new_player) >= n_partie(sorted_list)) {
            ass_adr_player(new_player, sorted_list);
            sorted_list = new_player;
        } else {
            qtr temp = sorted_list;
            while (next_player(temp) != NULL && n_partie(new_player) < n_partie(next_player(temp))) {
                temp = next_player(temp);
            }
            ass_adr_player(new_player, next_player(temp));
            ass_adr_player(temp, new_player);
        }
        
        current = next_player(current);
    }

    // Display sorted list
    printf("\nPlayers sorted by games played (most first):\n");
    current = sorted_list;
    while (current != NULL) {
        printf("- %s (Games: %d)\n", pseudo(current), n_partie(current));
        current = next_player(current);
    }

    // Free the temporary sorted list
    free_players(sorted_list);
}

void printloading()
{
    system("cls");
    Sleep(200);
    printf("\033[0m\n\n\n\n\t\t\t\t\t\t       \033[34m\033[1mLoading.\033[0m\n\n");
    Sleep(200);
    system("cls");
    printf("\033[0m\n\n\n\n\t\t\t\t\t\t       \033[34m\033[1mLoading..\033[0m\n\n");
    Sleep(200);
    system("cls");
    printf("\033[0m\n\n\n\n\t\t\t\t\t\t       \033[34m\033[1mLoading...\033[0m\n\n");
    Sleep(200);
    system("cls");
    printf("\033[0m\n\n\n\n\t\t\t\t\t\t       \033[34m\033[1mDONE\033[0m\n\n");
    Sleep(200);
    system("cls");
}
void highlightLine(const char *str)
{
    printf(ANSI_COLOR_BG_WHITE ANSI_COLOR_BLACK "%s" ANSI_COLOR_RESET "\n", str);
}
//--------------------------------------------------------------------------------------------------

void printESI()
{
    system("cls");
    printf("\n\t        \033[0;107m                  \033[0m          \033[0;107m                  \033[0m     \033[0;104m         \033[0m \n");
    Sleep(150);
    printf("\t      \033[0;107m                      \033[0m      \033[0;107m                      \033[0m   \033[0;104m         \033[0m  \n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m      \033[0m            \033[0;107m      \033[0m \n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;104m         \033[0m \n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m      \033[0m            \033[0;107m      \033[0m             \n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m       \033[0m  \n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m      \033[0m                      \033[0;107m       \033[0m       L'ECOLE  NATIONALE\n");
    Sleep(150);
    printf("\t     \033[0;107m                        \033[0m    \033[0;107m                        \033[0m    \033[0;107m       \033[0m  \n");
    Sleep(150);
    printf("\t     \033[0;107m                        \033[0m    \033[0;107m                        \033[0m    \033[0;107m       \033[0m       SUPERIEURE\n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m                                        \033[0;107m      \033[0m    \033[0;107m       \033[0m  \n");
    Sleep(150);
    printf("\t     \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m      \033[0m            \033[0;107m      \033[0m    \033[0;107m       \033[0m       D'INFORMATIQUE\n");
    Sleep(150);
    printf("\t      \033[0;107m      \033[0m          \033[0;107m      \033[0m      \033[0;107m      \033[0m          \033[0;107m      \033[0m     \033[0;107m       \033[0m  \n");
    Sleep(150);
    printf("\t      \033[0;107m                      \033[0m      \033[0;107m                      \033[0m     \033[0;107m       \033[0m  \n");
    Sleep(150);
    printf("\t        \033[0;107m                  \033[0m          \033[0;107m                  \033[0m       \033[0;107m       \033[0m  \n\n\n");
    Sleep(220);
}

void Welcome()
{
    system("cls");
    printf("\t\t\t\033[96m                People's Democratic Republic of Algeria           \033[0m\n", 130, 130, 130);
    printf("\t\t\t\033[96m         Ministry of Higher Education and Scientific Research\033[0m\n", 130, 130);
    printf("\t\t\t      \033[96m _______________________________________________________\n");
    printf("\t\t\t      \033[96m|        \033[92m_______\033[0m    \033[91m _______\033[0m    \033[97m _\033[0m                      \033[96m|\n");
    printf("\t\t\t      \033[96m|       \033[92m|  _____|\033[0m   \033[91m|  _____|\033[0m   \033[97m| |\033[0m  \033[92mHigher National\033[0m    \033[96m|\n", 130);
    printf("\t\t\t      \033[96m|       \033[92m| |_____\033[0m    \033[91m| |_____\033[0m    \033[97m| |\033[0m                     \033[96m|\n");
    printf("\t\t\t      \033[96m|       \033[92m|  _____|\033[0m   \033[91m|_____  |\033[0m   \033[97m| |\033[0m  \033[91mSchool of\033[0m          \033[96m|\n", 130);
    printf("\t\t\t      \033[96m|       \033[92m| |_____\033[0m    \033[91m _____| |\033[0m   \033[97m| |\033[0m                     \033[96m|\n");
    printf("\t\t\t      \033[96m|       \033[92m|_______|\033[0m   \033[91m|_______|\033[0m   \033[97m|_|\033[0m  \033[97mComputer Science\033[0m   \033[96m|\n");
    printf("\t\t\t      \033[96m|_______________________________________________________|\033[0m\n\n");

    printf("\t\t\t\t\033[96m     PCI - First Year - Scholar Year: 2024/2025 \n");
    printf("\t\t\t\033[96m ___________________________________________________________________\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|             REALISED By :  \033[97mABDAT YOUNES \033[96m                          |\n");
    printf("\t\t\t\033[96m|                                 &                                 |\n");
    printf("\t\t\t\033[96m|                             \033[97mYASMINE HAMMA\033[96m                         |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|               SECTION :  \033[97mD\033[96m          GROUPE: \033[97m15\033[96m                    |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|                   TP2 :  \033[97mLinked list (LLC)\033[96m                        |\n");
    printf("\t\t\t\033[96m|                                                                   |\n");
    printf("\t\t\t\033[96m|                       <  \033[97mQuestion/response\033[96m  >                     |\n");
    printf("\t\t\t\033[96m|                         < \033[97m Game\033[96m  >                                |\n");
    printf("\t\t\t\033[96m|___________________________________________________________________|\n\n\n");

    printf("\t\t\t                            \033[91mPlease                                 \n");
    printf("\t\t\t                  Click any key to continue...\033[0m               ");
    getch();

    system("cls");
}

