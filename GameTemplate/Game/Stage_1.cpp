#include "stdafx.h"
#include "Stage_1.h"

#include "BreakBox.h"
#include "Bumper.h"
#include "Door.h"
#include "Drone.h"
#include "Duct.h"
#include "Energy.h"
#include "Engine.h"
#include "Goal.h"
#include "HoneyCombBlock.h"
#include "JumpBoard.h"
#include "Nut.h"
#include "Pipe.h"
#include "Player.h"
#include "ReSpawnPoint.h"
#include "SignBoard.h"
#include "SpeedUpRail.h"
#include "Stage_1_Stage.h"
#include "Stage_1_Wall.h"
#include "Truck.h"
#include "Turret.h"
#include "Volt.h"

Stage_1::Stage_1()
{

}

Stage_1::~Stage_1()
{
    DeleteGO(m_stage_1_Stage);
    DeleteGO(m_stage_1_Wall);

    const auto& breakBoxs = FindGOs<BreakBox>("breakBox");
    int breakBoxSize = breakBoxs.size();
    for (int i = 0; i < breakBoxSize; i++)
    {
        DeleteGO(breakBoxs[i]);
    }
    const auto& bumpers = FindGOs<Bumper>("bumper");
    int bumperSize = bumpers.size();
    for (int i = 0; i < bumperSize; i++)
    {
        DeleteGO(bumpers[i]);
    }
    const auto& doors = FindGOs<Door>("door");
    int doorSize = doors.size();
    for (int i = 0; i < doorSize; i++)
    {
        DeleteGO(doors[i]);
    }
    const auto& drones = FindGOs<Drone>("drone");
    int droneSize = drones.size();
    for (int i = 0; i < droneSize; i++)
    {
        DeleteGO(drones[i]);
    }
    const auto& ducts = FindGOs<Duct>("duct");
    int ductSize = ducts.size();
    for (int i = 0; i < ductSize; i++)
    {
        DeleteGO(ducts[i]);
    }
    const auto& energys = FindGOs<Energy>("energy");
    int energySize = energys.size();
    for (int i = 0; i < energySize; i++)
    {
        DeleteGO(energys[i]);
    }
    const auto& engines = FindGOs<Engine>("engine");
    int engineSize = engines.size();
    for (int i = 0; i < engineSize; i++)
    {
        DeleteGO(engines[i]);
    }
    const auto& goals = FindGOs<Goal>("goal");
    int goalize = goals.size();
    for (int i = 0; i < goalize; i++)
    {
        DeleteGO(goals[i]);
    }
    const auto& honeyCombBlocks = FindGOs<HoneyCombBlock>("honeyCombBlock");
    int honeyCombBlockSize = honeyCombBlocks.size();
    for (int i = 0; i < honeyCombBlockSize; i++)
    {
        DeleteGO(honeyCombBlocks[i]);
    }
    const auto& jumpBoards = FindGOs<JumpBoard>("jumpBoard");
    int jumpBoardSize = jumpBoards.size();
    for (int i = 0; i < jumpBoardSize; i++)
    {
        DeleteGO(jumpBoards[i]);
    }
    const auto& nuts = FindGOs<Nut>("nut");
    int nutSize = nuts.size();
    for (int i = 0; i < nutSize; i++)
    {
        DeleteGO(nuts[i]);
    }
    const auto& pipes = FindGOs<Pipe>("pipe");
    int pipeSize = pipes.size();
    for (int i = 0; i < pipeSize; i++)
    {
        DeleteGO(pipes[i]);
    }
    const auto& reSpawnPoints = FindGOs<ReSpawnPoint>("reSpawnPoint");
    int reSpawnPointSize = reSpawnPoints.size();
    for (int i = 0; i < reSpawnPointSize; i++)
    {
        DeleteGO(reSpawnPoints[i]);
    }
    const auto& signBoards = FindGOs<SignBoard>("signBoard");
    int signBoardSize = signBoards.size();
    for (int i = 0; i < signBoardSize; i++)
    {
        DeleteGO(signBoards[i]);
    }
    const auto& speedUpRails = FindGOs<SpeedUpRail>("speedUpRail");
    int speedUpRailSize = speedUpRails.size();
    for (int i = 0; i < speedUpRailSize; i++)
    {
        DeleteGO(speedUpRails[i]);
    }
    const auto& trucks = FindGOs<Truck>("truck");
    int truckSize = trucks.size();
    for (int i = 0; i < truckSize; i++)
    {
        DeleteGO(trucks[i]);
    }
    const auto& turrets = FindGOs<Turret>("turret");
    int turretSize = turrets.size();
    for (int i = 0; i < turretSize; i++)
    {
        DeleteGO(turrets[i]);
    }
    const auto& volts = FindGOs<Volt>("volt");
    int voltSize = volts.size();
    for (int i = 0; i < voltSize; i++)
    {
        DeleteGO(volts[i]);
    }
    m_levelRender.ReleaseBoxCollider();
}

bool Stage_1::Start()
{
    m_levelRender.Init("Assets/modelData/Stage_0/Stage_1.tkl",
        [&](LevelObjectData& objData)
        {
            if (objData.EqualObjectName(L"Stage_1_ground") == true)
            {
                m_stage_1_Stage = NewGO<Stage_1_Stage>(0, "stage_1_Stage");         //��������B
                m_stage_1_Stage->SetPosition(objData.position);                     //���W��ݒ肷��B
                m_stage_1_Stage->SetScale(objData.scale);                           //�T�C�Y��ݒ肷��B
                m_stage_1_Stage->SetRotation(objData.rotation);                     //��]��ݒ肷��B
                return true;
            }
            if (objData.EqualObjectName(L"Stage_1_wall") == true)
            {
                m_stage_1_Wall = NewGO<Stage_1_Wall>(0, "stage_1_Wall");         //��������B
                m_stage_1_Wall->SetPosition(objData.position);                     //���W��ݒ肷��B
                m_stage_1_Wall->SetScale(objData.scale);                           //�T�C�Y��ݒ肷��B
                m_stage_1_Wall->SetRotation(objData.rotation);                     //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"box") == true)
            {
                m_levelRender.InitBoxCollider(objData,0.3f);
                return true;
            }
            else if (objData.ForwardMatchName(L"BreakBox") == true)
            {
                auto breakBox = NewGO<BreakBox>(0, "breakBox");                     //��������B
                breakBox->SetPosition(objData.position);                            //���W��ݒ肷��B
                breakBox->SetScale(objData.scale);                                  //�T�C�Y��ݒ肷��B
                breakBox->SetRotation(objData.rotation);                            //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Bumper") == true)
            {
                auto bumper = NewGO<Bumper>(0, "bumper");                           //��������B
                bumper->SetPosition(objData.position);                              //���W��ݒ肷��B
                bumper->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                bumper->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Door") == true)
            {
                auto door = NewGO<Door>(0, "door");                                 //��������B
                door->SetPosition(objData.position);                                //���W��ݒ肷��B
                door->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                door->SetRotation(objData.rotation);                                //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Drone") == true)
            {
                auto drone = NewGO<Drone>(0, "drone");                              //��������B
                drone->SetPosition(objData.position);                               //���W��ݒ肷��B
                drone->SetScale(objData.scale);                                     //�T�C�Y��ݒ肷��B
                drone->SetRotation(objData.rotation);                               //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Duct") == true)
            {
                auto duct = NewGO<Duct>(0, "duct");                                 //��������B
                duct->SetPosition(objData.position);                                //���W��ݒ肷��B
                duct->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                duct->SetRotation(objData.rotation);                                //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Energy") == true)
            {
                auto energy = NewGO<Energy>(0, "energy");                           //��������B
                energy->SetPosition(objData.position);                              //���W��ݒ肷��B
                energy->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                energy->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Engine") == true)
            {
                auto engine = NewGO<Engine>(0, "engine");                           //��������B
                engine->SetPosition(objData.position);                              //���W��ݒ肷��B
                engine->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                engine->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Goal") == true)
            {
                auto goal = NewGO<Goal>(0, "goal");                                 //��������B
                goal->SetPosition(objData.position);                                //���W��ݒ肷��B
                goal->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                goal->SetRotation(objData.rotation);                                //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"HoneyComb") == true)
            {
                auto honeyCombBlock = NewGO<HoneyCombBlock>(0, "honeyCombBlock");   //��������B
                honeyCombBlock->SetPosition(objData.position);                      //���W��ݒ肷��B
                honeyCombBlock->SetScale(objData.scale);                            //�T�C�Y��ݒ肷��B
                honeyCombBlock->SetRotation(objData.rotation);                      //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"JumpBoard") == true)
            {
                auto jumpBoard = NewGO<JumpBoard>(0, "jumpBoard");                  //��������B
                jumpBoard->SetPosition(objData.position);                           //���W��ݒ肷��B
                jumpBoard->SetScale(objData.scale);                                 //�T�C�Y��ݒ肷��B
                jumpBoard->SetRotation(objData.rotation);                           //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Nut") == true)
            {
                auto nut = NewGO<Nut>(0, "nut");                                    //��������B
                nut->SetPosition(objData.position);                                 //���W��ݒ肷��B
                nut->SetScale(objData.scale);                                       //�T�C�Y��ݒ肷��B
                nut->SetRotation(objData.rotation);                                 //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Pipe") == true)
            {
                auto pipe = NewGO<Pipe>(0, "pipe");                                 //��������B
                pipe->SetPosition(objData.position);                                //���W��ݒ肷��B
                pipe->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                pipe->SetRotation(objData.rotation);                                //��]��ݒ肷��B
            return true;
            }
            else if (objData.ForwardMatchName(L"ReSpawnPoint") == true)
            {
                auto reSpawnPoint = NewGO<ReSpawnPoint>(0, "reSpawnPoint");         //��������B
                reSpawnPoint->SetPosition(objData.position);                        //���W��ݒ肷��B
                reSpawnPoint->SetScale(objData.scale);                              //�T�C�Y��ݒ肷��B
                reSpawnPoint->SetRotation(objData.rotation);                        //��]��ݒ肷��B
            return true;
            }
            else if (objData.ForwardMatchName(L"Signboard") == true)
            {
                auto signBoard = NewGO<SignBoard>(0, "signBoard");                  //��������B
                signBoard->SetPosition(objData.position);                           //���W��ݒ肷��B
                signBoard->SetScale(objData.scale);                                 //�T�C�Y��ݒ肷��B
                signBoard->SetRotation(objData.rotation);                           //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"SpeedUpRail") == true)
            {
                auto speedUpRail = NewGO<SpeedUpRail>(0, "speedUpRail");            //��������B
                speedUpRail->SetPosition(objData.position);                         //���W��ݒ肷��B
                speedUpRail->SetScale(objData.scale);                               //�T�C�Y��ݒ肷��B
                speedUpRail->SetRotation(objData.rotation);                         //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Truck") == true)
            {
            auto truck = NewGO<Truck>(0, "truck");                                  //��������B
            truck->SetPosition(objData.position);                                   //���W��ݒ肷��B
            truck->SetScale(objData.scale);                                         //�T�C�Y��ݒ肷��B
            truck->SetRotation(objData.rotation);                                   //��]��ݒ肷��B
            return true;
            }
            else if (objData.ForwardMatchName(L"Turret") == true)
            {
                auto turret = NewGO<Turret>(0, "turret");                           //��������B
                turret->SetPosition(objData.position);                              //���W��ݒ肷��B
                turret->SetScale(objData.scale);                                    //�T�C�Y��ݒ肷��B
                turret->SetRotation(objData.rotation);                              //��]��ݒ肷��B
                return true;
            }
            else if (objData.ForwardMatchName(L"Volt") == true)
            {
                auto volt = NewGO<Volt>(0, "volt");                                 //��������B
                volt->SetPosition(objData.position);                                //���W��ݒ肷��B
                volt->SetScale(objData.scale);                                      //�T�C�Y��ݒ肷��B
                volt->SetRotation(objData.rotation);                                //��]��ݒ肷��B
                return true;
            }
        });
    return true;
}

void Stage_1::Update()
{
    m_levelRender.Update();
}