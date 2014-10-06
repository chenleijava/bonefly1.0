#pragma once

#include "Kit.h"
class ListViewLayerTest:public Layer
{
public:
	ListViewLayerTest( );
	~ListViewLayerTest( );

	virtual bool init( );

	virtual void onExit( );

	static Scene*createSence( );

	CREATE_FUNC( ListViewLayerTest);
};

