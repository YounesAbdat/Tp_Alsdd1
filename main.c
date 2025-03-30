#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "mylib.h"
int main() {
    srand(time(NULL));

    Welcome();      // Show ESI welcome screen
    printESI();     // Show ESI logo animation
    printloading();
    // Load initial data
    ptr questions = creer_liste("question.txt");
    char** propositions = load_propositions("propositions.txt");
    qtr players = creer_liste_players("players.txt");
    ptr_partie parties = NULL; // List to store game sessions

    if (!questions || !propositions) {
        printf("Failed to load questions/propositions. Exiting.\n");
        return 1;
    }

    // Display initial lists
    printf("\n=== Initial Questions List ===\n");
    print_list(questions);
    printf("\n=== Initial Players List ===\n");
    if (players) print_players(players);
    else printf("No existing players found.\n");

    // Main menu
    int choice;
    do {
        printf("\n=== Main Menu ===\n");
        printf("1. Register new player (without playing)\n");
        printf("2. Play as new player (single question)\n");
        printf("3. Play as existing player (single question)\n");
        printf("4. Start a game session (15 questions)\n");
        printf("5. Add new question\n");
        printf("6. Show current lists\n");
        printf("7. Show game sessions\n");
        printf("8. Sort players\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: { // Register new player without playing
                printf("\n=== New Player Registration ===\n");
                players = add_player(players, questions);
                printf("\n=== Updated Players List ===\n");
                print_players(players);
                printf("\nThank you for registering!\n");
                break;
            }
                
            case 2: { // Play as new player (single question)
                printf("\n=== New Player Registration ===\n");
                qtr new_player = add_player(players, questions);
                players = new_player;
                printf("\n=== Starting Game ===\n");
                jouer_session(players, questions, propositions);
                break;
            }
                
            case 3: { // Play as existing player (single question)
                if (!players) {
                    printf("No players available. Register first.\n");
                    break;
                }
                printf("\n=== Existing Players ===\n");
                print_players(players);
                
                int player_id;
                printf("\nEnter player ID to play as: ");
                scanf("%d", &player_id);
                
                qtr current = players;
                while (current) {
                    if (idp(current) == player_id) {
                        printf("\n=== Playing as %s ===\n", pseudo(current));
                        jouer_session(current, questions, propositions);
                        break;
                    }
                    current = next_player(current);
                }
                if (!current) printf("Player not found!\n");
                break;
            }
                
            case 4: { // Start a game session (15 questions)
                int player_choice;
                printf("\n=== Game Session Options ===\n");
                printf("1. Play as new player\n");
                printf("2. Play as existing player\n");
                printf("Enter your choice: ");
                scanf("%d", &player_choice);
                
                qtr current_player = NULL;
                
                if (player_choice == 1) {
                    // Register new player
                    printf("\n=== New Player Registration ===\n");
                    current_player = add_player(players, questions);
                    players = current_player;
                    printf("\n=== Starting Game Session ===\n");
                }
                else if (player_choice == 2) {
                    // Select existing player
                    if (!players) {
                        printf("No players available. Register first.\n");
                        break;
                    }
                    printf("\n=== Existing Players ===\n");
                    print_players(players);
                    
                    int player_id;
                    printf("\nEnter player ID to play as: ");
                    scanf("%d", &player_id);
                    
                    qtr current = players;
                    while (current) {
                        if (idp(current) == player_id) {
                            current_player = current;
                            break;
                        }
                        current = next_player(current);
                    }
                    if (!current_player) {
                        printf("Player not found!\n");
                        break;
                    }
                    printf("\n=== Starting Game Session ===\n");
                }
                else {
                    printf("Invalid choice!\n");
                    break;
                }
                
                // Start the game session
                ptr_partie new_game = partie_Question_reponse(current_player, questions, propositions);
                // Add to parties list
                ass_adr_partie(new_game, parties);
                parties = new_game;
                break;
            }
                
            case 5: { // Add new question
                printf("\n=== Adding New Question ===\n");
                if (!questions) {
                    questions = add_question(NULL);
                } else {
                    ptr current = questions;
                    while (next_question(current)) current = next_question(current);
                    ass_adr_question(current, add_question(NULL));
                }
                printf("\nThank you for your contribution! The question has been added.\n");
                printf("\n=== Updated Questions List ===\n");
                print_list(questions);
                break;
            }
                
            case 6: { // Show current lists
                printf("\n=== Current Questions ===\n");
                print_list(questions);
                printf("\n=== Current Players ===\n");
                print_players(players);
                break;
            }
                
            case 7: { // Show game sessions
                printf("\n=== Game Sessions History ===\n");
                ptr_partie current = parties;
                int session_count = 1;
                
                while (current) {
                    printf("\n--- Session %d ---\n", session_count++);
                    printf("Player: %s (ID: %d)\n", pseudo_partie(current), idplayer_partie(current));
                    printf("Level: %d\n", niv_partie(current));
                    printf("Total Score: %d\n", score_partie(current));
                    printf("Questions:\n");
                    
                    ptr_question_partie q = questions_partie(current);
                    int question_num = 1;
                    while (q) {
                        printf("  %d. Q%d: %s (Score: %d)\n", 
                               question_num++,
                               id_question_partie(q),
                               est_domaine_prefere(q) ? "[Preferred]" : "",
                               score_question_partie(q));
                        q = next_question_partie(q);
                    }
                    current = next_partie(current);
                }
                if (session_count == 1) printf("No game sessions recorded yet.\n");
                break;
            }
                
            case 8: { // Sort players
                printf("\n=== Sorting Options ===\n");
                printf("1. Sort by score (highest first)\n");
                printf("2. Sort by games played (most first)\n");
                printf("Enter your choice: ");
                int sort_choice;
                scanf("%d", &sort_choice);
                
                if (sort_choice == 1) {
                    afficher_joueurs_par_score(players);
                } else if (sort_choice == 2) {
                    afficher_joueurs_par_parties(players);
                } else {
                    printf("Invalid choice!\n");
                }
                break;
            }
                
            case 9: // Exit
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 9);

    // Cleanup
    free_list(questions);
    free_players(players);
    // Free game sessions
    ptr_partie current_partie = parties;
    while (current_partie) {
        ptr_partie next = next_partie(current_partie);
        ptr_question_partie current_q = questions_partie(current_partie);
        while (current_q) {
            ptr_question_partie next_q = next_question_partie(current_q);
            free(current_q);
            current_q = next_q;
        }
        free(current_partie);
        current_partie = next;
    }
    for (int i = 0; i < 101; i++) free(propositions[i]);
    free(propositions);

    return 0;
}
