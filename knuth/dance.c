#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "dance.h"
#include "mytypes.h"  // for RankSet

int maxb = 0;
int maxl = 0;

int level;
void print_row(Node *p){
    Node *q = p;
    int k;
    do { printf(" %s", q->col->name);
         q = q->right;
    } while (q != p);
    for (q = p->col->head.down, k = 1; q != p; k++) {
        if (q == &(p->col->head)) {   
            printf("\n");
            return;
        } else
            q = q->down;
    }
    printf(" (%d of %d)\n", k, p->col->len);
}

void print_state(int lev) {
    int l;
    for (l = 0; l <= lev; l++)
        print_row(choice[l]);
}

cover(Column *c) {
    Column *l, *r;
    Node *rr, *nn, *uu, *dd;
    l = c->prev;
    r = c->next;
    l->next = r;
    r->prev = l;
    for (rr = c->head.down; rr != &(c->head); rr = rr->down) {
        for (nn = rr->right; nn != rr; nn = nn->right) {
            uu = nn->up;
            dd = nn->down;
            uu->down = dd;
            dd->up = uu;
            nn->col->len--;
        }
    }   
}

uncover(Column *c) {
    Column *l, *r;
    Node *rr, *nn, *uu, *dd;
    for (rr = c->head.up; rr != &(c->head); rr = rr->up) {
        for (nn = rr->left; nn != rr; nn = nn->left) {
            uu = nn->up;
            dd = nn->down;
            uu->down = dd->up = nn;
            nn->col->len++;
        }
    }
    l = c->prev;
    r = c->next;
    l->next = r->prev = c;
}

bool solver(RankSet spades, RankSet hearts, 
           RankSet diamonds, RankSet clubs) {
    Column *cur_col;
    char *p, *q;
    Node *cur_node;

    Column *best_col;
    Node *pp;

    int j, k, x;

    cur_col = columns + 1;
  
    for (p = buf, *p; p++)
    {
        while (isspace(*p))
            p++;
        if (!*p)
            break;
        if (*p == '|')
        {
            primary = 0;
            if (cur_col == col_array + 1)
                panic("No primary columns");
            (cur_col - 1)->next = &root; 
            root.prev = cur_col - 1;
            continue;
        }
        for (q = p + 1; !isspace(*q); q++)
            ;
        if (q > p + 7)
            panic("Column name too long");
        if (cur_col >= &col_array[max_cols])
            panic("Too many columns");
        for (q = cur_col->name; !isspace(*p); q++, p++)
            *q = *p;
        cur_col->head.up = cur_col->head.down = &cur_col->head;
        cur_col->len = 0;
        if (primary)
            cur_col->prev = cur_col - 1, (cur_col - 1)->next = cur_col;
        else
            cur_col->prev = cur_col->next = cur_col;
        cur_col++;
    }
    if (primary)
    {
        if (cur_col == col_array + 1)
            panic("No primary columns");
        (cur_col - 1)->next = &root, root.prev = cur_col - 1;
    }

    cur_node = nodes;
    while (fgets(buf, buf_size, stdin))
    {
        Column *ccol;
        Node *row_start;
        if (buf[strlen(buf) - 1] != '\n')
            panic("Input line too long");
        row_start = NULL;
        for (p = buf; *p; p++)
        {
            while (isspace(*p))
                p++;
            if (!*p)
                break;
            for (q = p + 1; !isspace(*q); q++)
                ;
            if (q > p + 7)
                panic("Column name too long");
            for (q = cur_col->name; !isspace(*p); q++, p++)
                *q = *p;
            *q = '\0';
            for (ccol = col_array; strcmp(ccol->name, cur_col->name); ccol++)
                ;
            if (ccol == cur_col)
                panic("Unknown column name");
            if (cur_node == &node_array[max_nodes])
                panic("Too many nodes");
            if (!row_start)
                row_start = cur_node;
            else
                cur_node->left = cur_node - 1, (cur_node - 1)->right = cur_node;
            cur_node->col = ccol;
            cur_node->up = ccol->head.up, ccol->head.up->down = cur_node;
            ccol->head.up = cur_node, cur_node->down = &ccol->head;
            ccol->len++;
            cur_node++;
        }
        if (!row_start)
            panic("Empty row");
        row_start->left = cur_node - 1, (cur_node - 1)->right = row_start;
    }
    level = 0;

forward: /*19:*/


    int minlen = 100000;
    
    for (cur_col = root.next; cur_col != &root; cur_col = cur_col->next)
    {
        if (verbose > 2)
            printf(" %s(%d)", cur_col->name, cur_col->len);
        if (cur_col->len < minlen)
            best_col = cur_col, minlen = cur_col->len;
    }
    if (verbose)
    {
        if (level > maxl)
        {
            if (level >= max_level)
                panic("Too many levels");
            maxl = level;
        }
        if (minlen > maxb)
        {
            if (minlen >= max_degree)
                panic("Too many branches");
            maxb = minlen;
        }
        profile[level][minlen]++;
        if (verbose > 2)
            printf(" branching on %s(%d)\n", best_col->name, minlen);
    }

/*:19*/
#line 236 "dance.w"
    ;
    cover(best_col);
    cur_node = choice[level] = best_col->head.down;
advance:
    if (cur_node == &(best_col->head))
        goto backup;
    if (verbose > 1)
    {
        printf("L%d:", level);
        print_row(cur_node);
    }
/*17:*/
#line 307 "dance.w"

    for (pp = cur_node->right; pp != cur_node; pp = pp->right)
        cover(pp->col);

/*:17*/
#line 244 "dance.w"
    ;
    if (root.next == &root) /*21:*/
#line 342 "dance.w"

    {
        count++;
        if (verbose)
        {
            profile[level + 1][0]++;
            if (count % spacing == 0)
            {
                printf("%lld:\n", count);
                for (k = 0; k <= level; k++)
                    print_row(choice[k]);
            }
        }
        goto recover;
    }

/*:21*/
#line 245 "dance.w"
    ;
    level++;
    goto forward;
backup:
    uncover(best_col);
    if (level == 0)
        goto done;
    level--;
    cur_node = choice[level];
    best_col = cur_node->col;

recover: 

    for (pp = cur_node->left; pp != cur_node; pp = pp->left)
        uncover(pp->col);

/*:18*/
#line 252 "dance.w"
    ;
    cur_node = choice[level] = cur_node->down;
    goto advance;
done:
    if (verbose > 3)
/*22:*/
#line 355 "dance.w"

    {
        printf("Final column lengths");
        for (cur_col = root.next; cur_col != &root; cur_col = cur_col->next)
            printf(" %s(%d)", cur_col->name, cur_col->len);
        printf("\n");
    }

/*:22*/
#line 255 "dance.w"
    ;

/*:12*/
#line 46 "dance.w"
    ;
    printf("Altogether %lld solutions, after %.15g updates.\n", count, updates);
    if (verbose) /*23:*/
#line 363 "dance.w"

    {
        double tot, subtot;
        tot = 1;
        for (level = 1; level <= maxl + 1; level++)
        {
            subtot = 0;
            for (k = 0; k <= maxb; k++)
            {
                printf(" %5.6g", profile[level][k]);
                subtot += profile[level][k];
            }
            printf(" %5.15g nodes, %.15g updates\n", subtot, upd_prof[level - 1]);
            tot += subtot;
        }
        printf("Total %.15g nodes.\n", tot);
    }

/*:23*/
#line 48 "dance.w"
    ;
    exit(0);
}

/*:1*/
