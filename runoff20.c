#include <cs50.h>
#include <stdio.h>
#include<string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES]; 
int voter_count;
int candidate_count;


bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main (int argc, string argv[])
{
    if(argc<2)
    {
        printf(" Candidate Error\n");
        return 1;
    }

    candidate_count = argc - 1; 

    if(candidate_count > MAX_CANDIDATES)
    {
        printf("please enter valid no. of candidates. Max candidates are %i\n",MAX_CANDIDATES);
        return 2;
    }

    for(int i =0; i< candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // first cell has name of function so i+1
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }
    voter_count = get_int("Number of voters: ");

     if (voter_count > MAX_VOTERS)
    {
        printf("Max no. of voters is %i\n", MAX_VOTERS);
        return 3;
    }

   
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1); //user should see ranks they filled starting from 1 not 0

            if(!vote(i,j, name))
            {
                printf("INVALID INPUT\n");
                return 4;
            }

        }
        printf("\n");
    }

    //conducting election till we get a winner

    while(true)
    {
        tabulate();

        bool won = print_winner();//to see if someone already won

        if(won)
            break;

        int min = find_min();
        bool tie = is_tie(min);

        if(tie)
        {
            for(int i = 0; i<candidate_count; i++) //printing candidates who has a tie
            {
                if(!candidates[i].eliminated)
                {
                    printf("%s\n",candidates[i].name);
                }
            }
            break;
        }


        eliminate(min); // this eliminates anyone with min votes

    // once a candidates has been eliminated there has to a re-election
    //therefore number of votes has to be set to zero

         for(int i = 0; i < candidate_count; i++)
             {
              candidates[i].votes = 0;
             }
          }
    return 0;

}

//All functions to be used in the code are as follow

bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i].name, name))
        {
            preferences[voter][rank] = i; //voter means the which (No.) voter is voting and the rank is the rank given to each candidate by each voter the
                                        // the candidate indentity is done by doing string compare which is selected through user input
            return true;
        }
    }
    return false;
}

void tabulate(void) // here we configure how many votes did each candidate get
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated) //the program proceeds if the candidate has not been already eliminated
            {
                candidates[preferences[i][j]].votes += 1;
                break; //go to that candidate vote section and add 1 to it
            }
        }
    }
}

bool print_winner(void)
{
    int majority = (voter_count / 2) + 1; // more than 50%
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

int find_min(void)
{
    int min = INT_MAX;
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

bool is_tie(int min)
{
    // TODO
    int remaine_candidates = 0;
    int candidates_min_votes = 0;
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            remaine_candidates += 1;
            if (candidates[i].votes == min)
            {
                candidates_min_votes += 1;
            }
        }
    }
    return remaine_candidates == candidates_min_votes;
}

void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}




