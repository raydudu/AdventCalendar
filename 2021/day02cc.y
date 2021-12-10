%{
int yylex();
void yyerror(const char *msg);

void print_part_one(unsigned depth, unsigned distance);
void print_part_two(unsigned depth, unsigned distance, unsigned aim);

static unsigned depth;
static unsigned distance;

static unsigned aim;
static unsigned depth_p2;
%}


%union {
    unsigned int steps;
}

%token <steps> STEP
%token UP
%token DOWN
%token FORWARD

%%
done: seq { print_part_one(depth, distance);
            print_part_two(depth_p2, distance, aim);
          }
    ;

seq:
   | seq command
   ;

command: UP STEP         { depth -= $2; aim -= $2; }
      | DOWN STEP       { depth += $2; aim += $2; }
      | FORWARD STEP    { distance += $2; depth_p2 += aim * $2; }
      ;
%%