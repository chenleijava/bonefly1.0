#include "ListViewLayerTest.h"


ListViewLayerTest::ListViewLayerTest( )
{
}


ListViewLayerTest::~ListViewLayerTest( )
{
}

Scene* ListViewLayerTest::createSence( )
{
	auto _scene = Scene::create( );
	_scene->addChild( ListViewLayerTest::create( ) );
	return _scene;
}

bool ListViewLayerTest::init( )
{
	if(!Layer::init( ))
	{
		return true;
	}

	auto listview_ui = GUIReader::getInstance( )->widgetFromJsonFile( "ui/ListViewLayer/ListViewLayer.ExportJson" );
	this->addChild( listview_ui );

	return true;
}

void ListViewLayerTest::onExit( )
{
	Layer::onExit( );
	this->removeAllChildrenWithCleanup( true );
	GUIReader::destroyInstance( );
}
