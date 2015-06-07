package org.samp;

import net.gtaun.shoebill.constant.PlayerState;
import net.gtaun.shoebill.data.Color;
import net.gtaun.shoebill.event.player.PlayerStateChangeEvent;
import net.gtaun.shoebill.object.Player;
import net.gtaun.shoebill.object.Vehicle;
import net.gtaun.shoebill.resource.Gamemode;
import net.gtaun.util.event.EventManager;

import java.util.Arrays;

/**
 * Created by marvin on 07.06.15 in project open-pawn.
 * Copyright (c) 2015 Marvin Haschker. All rights reserved.
 */
public class OpenPawn extends Gamemode {

    private EventManager eventManager;

    @Override
    protected void onEnable() throws Throwable {
        eventManager = getEventManager();
        registerHandler();
    }

    private void registerHandler() {
        eventManager.registerHandler(PlayerStateChangeEvent.class, e -> {
            Player player = e.getPlayer();
            player.sendMessage(Color.LIGHTGREEN, "* OldState: " + e.getOldState().name() + " NewState: " + player.getState().name());
            if(player.getState() == PlayerState.DRIVER) {
                Vehicle vehicle = player.getVehicle();
                player.sendMessage(Color.LIGHTGREEN, "* VID: " + vehicle.getId() + " Model: " + vehicle.getModelName() + " Color: " + Arrays.toString(new int[] {
                        vehicle.getColor1(),
                        vehicle.getColor2()
                }));
            }
        });
    }

    @Override
    protected void onDisable() throws Throwable {

    }
}
