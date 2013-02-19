#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define JACK 11
#define QUEEN 12
#define KING 13
#define ACE 14

#define ROYAL_FLUSH 100
#define STRAIGHT_FLUSH 99 
#define FOUR_OF_A_KIND 98
#define FULL_HOUSE 97
#define FLUSH 96 
#define STRAIGHT 95 
#define THREE_OF_A_KIND 94 
#define TWO_PAIR 93 
#define PAIR 92 
#define HIGH_CARD 91

typedef struct {
    int num[5];
    int suit[5];
} hand_t;

typedef struct {
    int rank;
    int high_hand;
    int low_hand;
    int num_hand;
    int non_hand[5];
} rank_t;

int cmp(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;

    return (*ia) - (*ib);
}

void read_hand(const char *txt, hand_t *hand)
{
    int i;
    for(i = 0; i < 5; i++) {
        char n = txt[0];
        char s = txt[1];

        switch(n) {
            case 'T':
                hand->num[i] = 10;
                break;
            case 'J':
                hand->num[i] = JACK;
                break;
            case 'Q':
                hand->num[i] = QUEEN;
                break;
            case 'K':
                hand->num[i] = KING;
                break;
            case 'A':
                hand->num[i] = ACE;
                break;
            default:
                hand->num[i] = n - '0';
        }

        switch(s) {
            case 'D':
                hand->suit[i] = 0;
                break;
            case 'H':
                hand->suit[i] = 1;
                break;
            case 'S':
                hand->suit[i] = 2;
                break;
            case 'C':
                hand->suit[i] = 3;
                break;
        }

        txt += 3;
    }
}

int is_straight(int sorthand[])
{
    int i;
    for(i = 0; i < 4; i++)
        if(sorthand[i+1] != 1 + sorthand[i])
            return 0;

    return 1;
}

void rank_hand(hand_t *hand, rank_t *rank)
{
    int suitcount[5];
    int sorthand[5];
    int numcount[ACE+1];

    int hit2[2];
    int hit3;
    int hit4;
    int i;

    memset(suitcount, 0, sizeof(suitcount));
    memset(numcount, 0, sizeof(numcount));
    memset(rank, 0, sizeof(rank[0]));
    memset(rank->non_hand, 0, sizeof(rank->non_hand));

    for(i = 0; i < 5; i++) {
        suitcount[hand->suit[i]]++;

        numcount[hand->num[i]]++;
    }

    int nsuit = 0;
    for(i = 0; i < 5; i++) {
        nsuit += suitcount[i] > 0;
    }

    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    for(i = 0; i <= ACE; i++) {
        if(numcount[i] == 2) {
            hit2[num2++] = i;
        }
        if(numcount[i] == 3) {
            hit3 = i;
            num3++;
        }
        if(numcount[i] == 4) {
            hit4 = i;
            num4++;
        }
    }

    memcpy(sorthand, hand->num, sizeof(sorthand));
    qsort(sorthand, 5, sizeof(int), cmp);

    int straight = is_straight(sorthand);

    if(nsuit == 1 && is_straight) {
        if(sorthand[0] == 10) {
            rank->rank = ROYAL_FLUSH;
        } else {
            rank->rank = STRAIGHT_FLUSH;
        }
        rank->high_hand = sorthand[4];
        rank->low_hand = sorthand[0];
        return;
    }

    if(num4) { // 4 of a kind
        rank->rank = FOUR_OF_A_KIND;
        rank->high_hand = hit4;
        rank->low_hand = hit4;

        if(sorthand[0] == hit4)
            rank->non_hand[0] = sorthand[4];
        else
            rank->non_hand[0] = sorthand[0];

        return;
    }

    if(num2 && num3) { // full house
        rank->rank = FULL_HOUSE;
        rank->high_hand = hit3;
        rank->low_hand= hit2[0] ;
        return;
    }

    if(nsuit == 1) {
        rank->rank = FLUSH;

        memcpy(rank->non_hand, sorthand, sizeof(sorthand));

        return;
    }

    if(straight) {
        rank->rank = STRAIGHT;
        rank->high_hand = sorthand[4];
        rank->low_hand = sorthand[0];
        return;
    }

    if(num3) {
        rank->rank = THREE_OF_A_KIND;
        rank->high_hand = hit3;
        rank->low_hand = hit3;

        if(hit3 != sorthand[4]) {
            rank->non_hand[1] = sorthand[4];
            if(hit3 != sorthand[3])
                rank->non_hand[0] = sorthand[3];
            else
                rank->non_hand[0] = sorthand[0];
        } else {
            rank->non_hand[1] = sorthand[1];
            rank->non_hand[0] = sorthand[0];
        }
        return; 
    }

    if(num2 == 2) {
        rank->rank = TWO_PAIR;
        rank->high_hand = (hit2[0] > hit2[1]) ? hit2[0] : hit2[1];
        rank->low_hand = (hit2[0] > hit2[1]) ? hit2[1] : hit2[0];

        for(i = 0; i < 5; i++) {
            if(sorthand[i] != hit2[0] && sorthand[i] != hit2[1]) {
                rank->non_hand[0] = sorthand[i];
                break;
            }
        }
        return;
    }

    if(num2) {
        rank->rank = PAIR;
        rank->high_hand = hit2[0];
        rank->low_hand = hit2[0];

        memcpy(rank->non_hand, sorthand, sizeof(sorthand));
        for(i = 0; i < 5; i++) {
            if(sorthand[i] == hit2[0]) {
                memmove(rank->non_hand + i, rank->non_hand + i + 2, sizeof(int)*(3-i));
                break;
            }
        }
         
        return;
    }

   rank->rank = HIGH_CARD;
   rank->high_hand = 0;
   rank->low_hand = 0;
   memcpy(rank->non_hand, sorthand, sizeof(sorthand)); 

   return;
}

int atest(rank_t *r1, rank_t *r2)
{ // assume r1->rank and r2->rank are equal
    int ret = 0;
    if(r1->high_hand > r2->high_hand)
        return 1;
    else
        if(r1->high_hand < r2->high_hand)
            return 2;

    int i;
    int start;
    switch(r1->rank) {
        case FULL_HOUSE:
            if(r1->low_hand > r2->low_hand) {
                ret = 1;
            } else if(r1 -> low_hand < r2->low_hand) {
                ret = 2;
            }
            break;
        case FOUR_OF_A_KIND:
            if(r1->non_hand[0] > r2->non_hand[0])
                ret = 1;
            else if(r1->non_hand[0] < r2->non_hand[0])
                ret = 2;
            break;
        case FLUSH:
        case HIGH_CARD:
            start = 2;
        case PAIR:
            start += 3;
            for(i = start; i; i--) {
                if(r1->non_hand[i] == r2->non_hand[i])
                    continue;
                
                ret = r2->non_hand[i] > r1->non_hand[i];
                ret++;
                break;
            }

            break;
    }

    return ret;
}

int main(void)
{
    FILE *fp = fopen("poker.txt", "r");
    if(!fp) {
        perror("poker.txt");
        exit(0);
    }
    char buf[128];
    hand_t h1, h2;
    rank_t r1, r2;

    while(NULL != fgets(buf, sizeof(buf), fp)) {
        read_hand(buf, &h1);
        read_hand(buf + 15, &h2);

        rank_hand(&h1, &r1);
        rank_hand(&h2, &r2);

        if(r1.rank > r2.rank) {
            printf("P1 wins\n");
        } else if(r1.rank < r2.rank) {
            printf("P2 wins\n");
        } else {
            int winner = atest(&r1, &r2);
            if(!winner) {
                printf("no winner! RANK %d\n", r1.rank);
            } else {
                printf("P%d wins *\n", winner);
            }
        }
    }

    return 0;
}
