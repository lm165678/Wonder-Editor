open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe(
    "redo_undo: inspector",
    () => {
      let sandbox = getSandboxDefaultVal();
      let _buildInspectorComponent = (allShowComponentConfig) =>
        ReactTestRenderer.create(
          <MainEditorInspector
            store=(TestToolUI.buildEmptyAppState())
            dispatch=(TestToolUI.getDispatch())
            allShowComponentConfig
          />
        );
      beforeEach(
        () => {
          sandbox := createSandbox();
          TestToolEngine.prepare(sandbox)
        }
      );
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      describe(
        "test simulate set currentGameObject",
        () => {
          let _buildEngineSceneTree = () =>
            ReactTestRenderer.create(
              <MainEditorSceneTree
                store=(SceneTreeToolUI.buildAppStateSceneGraphFromEngine())
                dispatch=(TestToolUI.getDispatch())
              />
            );
          let _setSpecificGameObject = (clickTreeNodeIndex) => {
            let component = _buildEngineSceneTree();
            EventToolUI.triggerComponentEvent(
              component,
              SceneTreeEventTool.triggerClickEvent(clickTreeNodeIndex)
            )
          };
          describe(
            "test snapshot",
            () => {
              beforeEach(
                () => {
                  TestToolEditor.closeContractCheck();
                  TestToolUI.initMainEditor(sandbox);
                  MainEditorSceneToolEditor.prepareDefaultScene(() => ());
                  StateHistoryToolEditor.clearAllState();
                  _setSpecificGameObject(1)
                }
              );
              afterEach(() => TestToolEditor.openContractCheck());
              describe(
                "test undo operate",
                () => {
                  test(
                    "test not undo",
                    () =>
                      _buildInspectorComponent(InspectorToolUI.buildFakeAllShowComponentConfig())
                      |> ReactTestTool.createSnapshotAndMatch
                  );
                  describe(
                    "test undo one step",
                    () =>
                      test(
                        "step from second to first",
                        () => {
                          StateHistoryToolEditor.undo();
                          _buildInspectorComponent(
                            InspectorToolUI.buildFakeAllShowComponentConfig()
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                  );
                  describe(
                    "test undo two step",
                    () =>
                      test(
                        "step from second to zero",
                        () => {
                          StateHistoryToolEditor.undo();
                          StateHistoryToolEditor.undo();
                          _buildInspectorComponent(
                            InspectorToolUI.buildFakeAllShowComponentConfig()
                          )
                          |> ReactTestTool.createSnapshotAndMatch
                        }
                      )
                  )
                }
              )
            }
          )
        }
      )
    }
  );