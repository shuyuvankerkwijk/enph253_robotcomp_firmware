#ifndef CRANE_H
#define CRANE_H

// functions
void craneSetupF();
void craneSetupB();
void craneSetupZAxisB();
void craneSetupRAxisB();
void craneSetupYAxisB();

void craneSetDirectionZF(int dir);
bool craneMoveZF(int final_pos);

void craneSetDirectionRF(int dir);
bool craneMoveRF(int final_pos);

void craneSetDirectionYF(int dir);
bool craneMoveYF(int final_pos);

void craneSetDirectionZB(int dir);
bool craneMoveZB(int final_pos);

void craneSetDirectionRB(int dir);
bool craneMoveRB(int final_pos);

void craneSetDirectionYB(int dir);
bool craneMoveYB(int final_pos);

#endif // CRANE_H