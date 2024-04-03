#include <iostream>
#include <raylib.h>

struct AnimData {
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float runningTime;
};

bool isOnGround(AnimData data, int windowHeight) {
	return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAniData(AnimData data, float deltaTime, int maxFrame) {
	//update runingtime
	data.runningTime += deltaTime;
	if (data.runningTime >= data.updateTime) {
		data.runningTime = 0.0;
		data.rec.x = data.frame * data.rec.width;
		data.frame++;
			if (data.frame > maxFrame) {
				data.frame = 0;
		}
	}
	return data;
}


int main() {

	

//==========================================
	int windowDismension[2];
	windowDismension[0] = 512;
	windowDismension[1] = 380;

// ==Initialization=========================
	InitWindow(windowDismension[0], windowDismension[1], "Dapper dasher");

//==Acceleration due to gravity(pixels/s)/s
	const int gravity{ 1'000 };


//==Scarfy object=========================	
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData;
	scarfyData.rec.width = scarfy.width / 6;
	scarfyData.rec.height = scarfy.height;
	scarfyData.rec.x = 0;
	scarfyData.rec.y = 0;

	scarfyData.pos.x = windowDismension[0] / 2 - scarfyData.rec.width / 2;
	scarfyData.pos.y = windowDismension[1] - scarfyData.rec.height;

	scarfyData.frame = 0;
	scarfyData.updateTime = 1.0 / 12.0;
	scarfyData.runningTime = 0.0;


	

//==Nebula object=========================	
	Texture2D nebulaT = LoadTexture("textures/12_nebula_spritesheet.png");

	
	const int sizeOfNebulae{ 3 };
	AnimData nebulae[sizeOfNebulae]{};

	for (int i = 0; i < sizeOfNebulae;i++) {
		nebulae[i].rec.x = 0.0;
		nebulae[i].rec.y = 0.0;
		nebulae[i].rec.width = nebulaT.width / 8;
		nebulae[i].rec.height = nebulaT.height / 8;

		nebulae[i].pos.y = windowDismension[1] - nebulaT.height / 8;
		nebulae[i].pos.x = windowDismension[0] + i * 300;

		nebulae[i].frame = 0;
		nebulae[i].runningTime = 0.0;
		nebulae[i].updateTime = 1.0 / 16.0;
	}

	float finishline{nebulae[sizeOfNebulae -1].pos.x};
	

	// nebula X velocity(pixel/second)
	int nebVel{ -600 };

	
	//int posY{ windowHeight - height };
	int velocity{ 0 };
	
// ==Jump variables=========================	
	// jumping tes/not?
	bool isInAir{};
	//jump velocity pixels per sec
	const int jumpVel{ -600 };
	
	Texture2D background = LoadTexture("textures/far-buildings.png");
	float bgX{};

	Texture2D midground = LoadTexture("textures/back-buildings.png");
	float mgX{};
	Texture2D foreground = LoadTexture("textures/foreground.png");
	float fgX{};


	bool collision{};
	SetTargetFPS(60);
//==Main game loop=======================================================================================================Main game loop======================
	while (!WindowShouldClose()) {
//==delta time (time since last frame)
		float dT{ GetFrameTime() };

		//==Start Drawing=====
		BeginDrawing();
		ClearBackground(WHITE);

		bgX -= 20 * dT;
		if (bgX <= -background.width * 2) {
			bgX = 0.0;
		}

		mgX -= 40 * dT;
		if (mgX <= -midground.width * 2) {
			mgX = 0.0;
		}

		fgX -= 80 * dT;
		if (fgX <= -foreground.width * 2) {
			fgX = 0.0;
		}

//==draw the background
		Vector2 bg1Pos{ bgX,0.0 };
		DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
		Vector2 bg2Pos{ bgX + background.width*2,0.0 };
		DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

		Vector2 mg1Pos{ mgX,0.0 };
		DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
		Vector2 mg2Pos{ mgX + midground.width * 2,0.0 };
		DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

		Vector2 fg1Pos{ fgX,0.0 };
		DrawTextureEx(foreground, mg1Pos, 0.0, 2.0, WHITE);
		Vector2 fg2Pos{ fgX + foreground.width * 2,0.0 };
		DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);


		

//==Ground check=============================
		if (isOnGround(scarfyData,windowDismension[1])) {
			//rectangle on the ground
			velocity = 0;
			isInAir = false;
			
		}
		else {
			//rectangle on the air
	//==Apply gravity====================
			velocity += gravity*dT;
			isInAir = true;
		}

//=Jumpping check==============================
		if (IsKeyPressed(KEY_SPACE) && !isInAir) {
			velocity += jumpVel;
		}

//==nebula position============================

		for (int i = 0; i < sizeOfNebulae; i++) {
			nebulae[i].pos.x += nebVel * dT;
		}

//update finishline
		finishline += nebVel * dT;

//==update position==============
		scarfyData.pos.y += velocity*dT;


//==update animation frame============scarfy
		
		if (!isInAir) {
			scarfyData = updateAniData(scarfyData, dT, 5);
		}

		for (int i = 0; i < sizeOfNebulae; i++)
		{
			nebulae[i] = updateAniData(nebulae[i], dT, 7);
		}

		
		for (AnimData nebula : nebulae) {
			float pad{ 20 };
			Rectangle nebRec{
				nebula.pos.x + pad ,
				nebula.pos.y + pad,
				nebula.rec.width - 2 * pad,
				nebula.rec.height - 2 * pad,
			};
			Rectangle scarfyRec{
				scarfyData.pos.x,
				scarfyData.pos.y,
				scarfyData.rec.width,
				scarfyData.rec.height,
			};

			if (CheckCollisionRecs(nebRec, scarfyRec)) {
				collision = true;
				
			}

			if (collision) {
				// lose the game
				DrawText("Game Over!", windowDismension[0] / 4, windowDismension[1] / 2, 40, WHITE);
			}
			else if (scarfyData.pos.x >= finishline) {
				DrawText("You win", windowDismension[0] / 4, windowDismension[1] / 2, 40, WHITE);
			}
			else {
				for (int i = 0; i < sizeOfNebulae; i++) {
					DrawTextureRec(nebulaT, nebulae[i].rec, nebulae[i].pos, WHITE);
				}
				

				DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
			}
		}

		
		

		//==End Drawing=====
		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebulaT);
	UnloadTexture(background);
	UnloadTexture(foreground);
	UnloadTexture(midground);
	CloseWindow();



}

