
#ifndef _DashSmoke_H_
#define _DashSmoke_H_
#include "Effect.h"
#include "Camera.h"
#include <vector>
#include "Animation.h"
using namespace std;
class DashSmoke : public Effect
{
private:
	void createEffectInfinity(int x, int y) override {};

public:
	DashSmoke(UINT animation);
	void createEffect(int x, int y) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	~DashSmoke();
};
#endif // !_DashSmoke_H_
