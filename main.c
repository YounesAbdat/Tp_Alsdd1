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
        printf("1. Register new player\n");
        printf("2. Delete a player\n");
        printf("3. Play as new player (single question)\n");
        printf("4. Play as existing player (single question)\n");
        printf("5. Start a game session (15 questions)\n");
        printf("6. Add new question\n");
        printf("7. Delete a question\n");
        printf("8. Show current lists\n");
        printf("9. Show game sessions\n");
        printf("10. Sort players\n");
        printf("11. Exit\n");
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
                
            case 2: { // Delete a player
                if (!players) {
                    printf("No players available to delete.\n");
                    break;
                }
                printf("\n=== Current Players ===\n");
                print_players(players);
                
                int player_id;
                printf("\nEnter ID of player to delete: ");
                scanf("%d", &player_id);
                
                players = delete_player(players, player_id);
                printf("\n=== Updated Players List ===\n");
                print_players(players);
                break;
            }
                
            case 3: { // Play as new player (single question)
                printf("\n=== New Player Registration ===\n");
                qtr new_player = add_player(players, questions);
                players = new_player;
                printf("\n=== Starting Game ===\n");
                jouer_session(players, questions, propositions);
                break;
            }
                
            // [Rest of your existing cases, renumbered...]
            case 4: { // Play as existing player (single question)
                if (!players) {
                    printf("No players available. Register first.\n");
                    break;
                }
                // ... existing code ...
                break;
            }
                
            case 5: { // Start a game session (15 questions)
                // ... existing code ...
                break;
            }
                
            case 6: { // Add new question
                // ... existing code ...
                break;
            }
                
            case 7: { // Delete a question
                if (!questions) {
                    printf("No questions available to delete.\n");
                    break;
                }
                printf("\n=== Current Questions ===\n");
                print_list(questions);
                
                int question_id;
                printf("\nEnter ID of question to delete: ");
                scanf("%d", &question_id);
                
                questions = delete_question(questions, question_id);
                printf("\n=== Updated Questions List ===\n");
                print_list(questions);
                break;
            }
                
            case 8: { // Show current lists
                // ... existing code ...
                break;
            }
                
            case 9: { // Show game sessions
                // ... existing code ...
                break;
            }
                
            case 10: { // Sort players
                // ... existing code ...
                break;
            }
                
            case 11: // Exit
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 11);


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
