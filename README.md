# The 2021 ICPC Asia Jakarta Regional Contest - Problem Repository

## Repository Structure

Each problem (from PA to PD for trial and A to M for contest) has their own folder. The folder name is the `slug` of the problem, which is the codename we used when we internally prepare the problems. The following table describes the slug for each problem

| Problem Code | Problem Slug      | Problem Title              |
| ------------ | ----------------- | -------------------------- |
| PA           | double            | Non Classical Problem      |
| PB           | homework          | Copying Homework           |
| PC           | bottleneck        | Exchange Bottleneck        |
| PD           | beauty            | Tree Beauty                |
| A            | xor               | XOR Pairs                  |
| B            | bike              | Bicycle Tour               |
| C            | energy-generation | Energy Generation          |
| D            | uniform           | Uniform Maker              |
| E            | concert           | Concerto de Pandemic       |
| F            | not-one           | Not One                    |
| G            | greedy            | Greedy Knapsack            |
| H            | cell-game         | Cell Game                  |
| I            | planetary         | Stable Planetary System    |
| J            | robot             | Feeder Robot               |
| K            | tree              | White-Black Tree           |
| L            | travelling        | Happy Travelling           |
| M            | maxdiff           | Maxdifficent Group         |

In the problem folder, there should be exactly the following file/folder:

- `description.pdf`. The problem statement distributed to the contestants during the contest.
- `data/`. A folder consisting of all testcases. The sample inputs given in the problem statement will be in the form of `sample/<slug>_sample_<testcase number>.in/ans`, while the hidden testcases will be in the form of `secret/<slug>_1_<testcase number>.in/ans`.
- `solution.cpp`. The official solution used to generate the outputs of the testcases
- `scorer.cpp`. A validator used to validate contestants' output. The code accepts three arguments.
  - The first parameter will be used as the filename of the input file
  - The second parameter will be used as the filename of the judge's output file
  - The third parameter will be used as the filename of the contestant's output file
  - This code will print `WA` to stdout if the contestant's output is intended to be judged `WRONG ANSWER`, while it will print `AC` to stdout if the contestants's output is intended to be judged `CORRECT`.
- `verifier.py`. A verifier used to validate the input of the testcases. The code will crash if the input violates the problem constraint, while it will exit gracefully and will not output anything if the input satisfies the problem constraint.

## Limitations

The following table describes the time limit for each problem.

| Problem Code | Problem Slug      | Time Limit |
| ------------ | ----------------- | ---------- |
| PA           | double            | 1 sec      |
| PB           | homework          | 1 sec      |
| PC           | bottleneck        | 1 sec      |
| PD           | beauty            | 2 sec      |
| A            | xor               | 1 sec      |
| B            | bike              | 1 sec      |
| C            | energy-generation | 1 sec      |
| D            | uniform           | 1 sec      |
| E            | concert           | 2 sec      |
| F            | not-one           | 1 sec      |
| G            | greedy            | 1 sec      |
| H            | cell-game         | 2 sec      |
| I            | planetary         | 1 sec      |
| J            | robot             | 1 sec      |
| K            | tree              | 1 sec      |
| L            | travelling        | 1 sec      |
| M            | maxdiff           | 1 sec      |

The memory limit for all problems is 256MB.

## Solutions

Note that while there is only one official published solution, we have a lot of other solutions prepared for our internal testing. These other solutions include, but not limited to:

- Solutions in several other languages
- Solutions that is intended to be incorrect (e.g. WA, TLE, etc.)
- Other correct solutions (especially on problems with more than one correct outputs for each input)

## Errata

None.
