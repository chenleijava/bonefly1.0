#ifndef _EFFECT_HH_
#define  _EFFECT_HH_
#include "res.h"
#include "Kit.h"

class Effect:public Node
{
public:
	Effect( );

	~Effect( );

	static Effect *CreateEffect( );

	
	//************************************
	// Method:    explosion
	// FullName:  Effect::explosion
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: Node * gameStage  容器
	// Parameter: Vec2 pos   位置
	//************************************
	void explosion( Node *gameStage, Vec2 pos, float scale = 1.0f );


	//************************************
	// Method:    hit  
	// FullName:  Effect::hit
	// Access:    public 
	// Returns:   void
	// Qualifier: 飞机被击中 效果
	// Parameter: Node * gameStage
	// Parameter: Vec2 pos
	// Parameter: float scale
	//************************************
	void hit( Node *gameStage, Vec2 pos, float scale = 0.2f );



	//_emitter = ParticleSystemQuad::create( "Particles/LavaFlow.plist" );
	//_emitter->retain( );
	//auto batch = ParticleBatchNode::createWithTexture( _emitter->getTexture( ) );
	//batch->addChild( _emitter );

private:
	Sprite *m_sprite;
};
#endif

