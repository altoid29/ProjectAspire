#include "../../Header Files/Hacks.h"

void ESPRelated::Handle()
{
    if ( !Settings::ESP::enable )
        return;

    if ( !g_globals->localPlayer )
        return;

    for ( size_t i = 0; i < Util::GetPlayerCount(); i++ )
    {
        Player* entity = g_interfaces->EntList->GetClientEntity( i );
        if ( !entity || !entity->IsAlive() || entity->IsDormant() || entity == g_globals->localPlayer )
            continue;

        if ( Settings::ESP::visibleCheck && !entity->IsVisible( entity, g_globals->localPlayer->GetEyeOrigin() ) )
            continue;

        if ( Settings::ESP::teamCheck && entity->GetTeam() == g_globals->localPlayer->GetTeam() )
            continue;

        Vector2 Screen{};
        if ( !World::WorldToScreen( entity->GetHitboxPosition( HITBOX_HEAD ), Screen ) )
            continue;

        // Failed to get the player bounding box.
        World::BoxT box{};
        if ( !World::GetPlayerBox( entity, box ) )
            continue;

        // Head dot ESP.
        if ( Settings::ESP::dot )
            Renderer::AddFilledRect( Renderer::DetermineColorFromSelection( Settings::Colors::dotSelection ), Screen.x, Screen.y, 2, 2 );

        // Box ESP.
        if ( Settings::ESP::box )
        {
            // Outer outline.
            Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), box.x - 1, box.y - 1, box.w + 2, box.h + 2 );

            // Box.
            Renderer::AddRect( Renderer::DetermineColorFromSelection( Settings::Colors::boxSelection ), box.x, box.y, box.w, box.h );

            // Inner outline.
            Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), box.x + 1, box.y + 1, box.w - 2, box.h - 2 );
        }

        // Name ESP.
        if ( Settings::ESP::name )
        {
            static const auto tahoma = g_globals->renderer->tahoma;

            PlayerInfo_t info{};
            g_interfaces->Engine->GetPlayerInfo( entity->Index(), &info );

            const auto nameW = Renderer::GetTextWidth( tahoma, info.Name );
            Renderer::AddString( tahoma, Renderer::DetermineColorFromSelection( Settings::Colors::nameSelection ), Screen.x - nameW / 2 + 2, box.y - 16, false, info.Name, true );
        }

        // Health ESP.
        if ( Settings::ESP::health )
        {
            // Health bar outline.
            Renderer::AddRect( Renderer::UIColorT( 0, 0, 0, 255 ), box.x - 8, box.y - 1, 4, box.h + 2 );

            const int r = std::min( ( 510 * ( 100 - entity->GetHealth() ) / 100 ), 255 );
            const int g = std::min( ( 510 * entity->GetHealth() ) / 100, 255 );

            // Dynamic health factor.
            const auto healthHeight = ( box.h * entity->GetHealth() ) / 100;

            // Health bar background.
            if ( entity->GetHealth() < 100 )
                Renderer::AddRectGradient( Renderer::UIColorT( 5, 5, 5, 200 ), Renderer::UIColorT( 45, 45, 45, 200 ), box.x - 7, box.y - 1, 3, box.h + 2 );

            // Health bar.
            Renderer::AddRectGradient( Renderer::UIColorT( r, g, 0, 255 ), Renderer::UIColorT( r / 2, g / 2, 0, 255 ), box.x - 7, box.y, 3, healthHeight + 1 );

            // Draw health value.
            if ( entity->GetHealth() < 100 )
            {
                const USHORT additive = entity->GetHealth() < 10 ? 8 : 10;
                Renderer::AddString( g_globals->renderer->smallFonts, Renderer::UIColorT( 255, 255, 255, 255 ), box.x - additive, box.y - 4, false, std::to_string( entity->GetHealth() ).c_str(), true );
            }
        }

        // Distance ESP.
        if ( Settings::ESP::distance )
        {
            std::string distFromMe = tfm::format( _( "%iFT" ), ( int )( g_globals->localPlayer->GetOrigin().dist( entity->GetOrigin() ) ) / 20 );
            Renderer::AddString( g_globals->renderer->smallFonts, Renderer::DetermineColorFromSelection( Settings::Colors::distanceSelection ), box.x + box.w + 3, box.y - 2, false, distFromMe.c_str(), true );
        }

        // Area ESP.
        if ( Settings::ESP::area )
        {
            std::string mapArea = entity->GetMapAreaName();
            std::transform( mapArea.begin(), mapArea.end(), mapArea.begin(), ::toupper );

            Renderer::AddString( g_globals->renderer->smallFonts, Renderer::DetermineColorFromSelection( Settings::Colors::areaSelection ), 
                                 box.x + box.w + 3, Settings::ESP::distance ? box.y + 7 : box.y - 2, 
                                 false, mapArea.c_str(), true );
        }

        // Skeleton ESP.
        if ( Settings::ESP::skeleton )
        {
            auto studioModel = g_interfaces->ModelInfo->GetStudioModel( entity->Model() );
            if ( studioModel )
            {
                static matrix3x4_t boneToWorld[ 128 ];
                if ( entity->SetupBones( boneToWorld, 128, 256, 0 ) )
                {
                    for ( int i = 0; i < studioModel->numbones; i++ )
                    {
                        auto currentBone = studioModel->GetBone( i );
                        if ( !( !currentBone || !( currentBone->flags & 256 ) || currentBone->parent == -1 ) )
                        {
                            Vector3 bonePos{};
                            if ( World::WorldToScreen( Vector3( boneToWorld[ i ][ 0 ][ 3 ], boneToWorld[ i ][ 1 ][ 3 ], boneToWorld[ i ][ 2 ][ 3 ] ), bonePos ) )
                            {
                                Vector3 bonePos2{};
                                if ( World::WorldToScreen( Vector3( boneToWorld[ currentBone->parent ][ 0 ][ 3 ], boneToWorld[ currentBone->parent ][ 1 ][ 3 ], boneToWorld[ currentBone->parent ][ 2 ][ 3 ] ), bonePos2 ) )
                                    Renderer::AddLine( Renderer::DetermineColorFromSelection( Settings::Colors::skeletonSelection ), bonePos.x, bonePos.y, bonePos2.x, bonePos2.y );
                            }
                        }
                    }
                }
            }
        }

        // Lines ESP.
        if ( Settings::ESP::lines )
        {
            switch ( Settings::ESP::linesPosition )
            {
                // Top.
                case 0:
                    Renderer::AddLine( Renderer::DetermineColorFromSelection( Settings::Colors::linesSelection ), CROSSHAIR_X, 0, Screen.x, Screen.y );
                    break;

                    // Middle.
                case 1:
                    Renderer::AddLine( Renderer::DetermineColorFromSelection( Settings::Colors::linesSelection ), CROSSHAIR_X, CROSSHAIR_Y, Screen.x, Screen.y );
                    break;

                    // Bottom.
                case 2:
                    Renderer::AddLine( Renderer::DetermineColorFromSelection( Settings::Colors::linesSelection ), CROSSHAIR_X, g_globals->screenH, Screen.x, Screen.y );
                    break;
            }
        }
    }
}