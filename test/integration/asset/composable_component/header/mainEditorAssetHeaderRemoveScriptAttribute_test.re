open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe("MainEditorAssetHeader->remove script event function", () => {
    let sandbox = getSandboxDefaultVal();

    beforeEach(() => {
      sandbox := createSandbox();
      MainEditorSceneTool.initState(~sandbox, ());
    });

    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe(
      {|
        select script event function;
        click remove-button;
            |},
      () =>
      test("should remove it from assetTreeRoot", () => {
        let assetTreeData =
          MainEditorAssetTreeTool.BuildAssetTree.ScriptAttribute.buildOneScriptAttributeAssetTree();

        MainEditorAssetHeaderOperateNodeTool.removeScriptAttributeNode(
          ~scriptAttributeNodeId=
            MainEditorAssetTreeTool.BuildAssetTree.ScriptAttribute.getFirstScriptAttributeNodeId(
              assetTreeData,
            ),
          (),
        );

        BuildComponentTool.buildAssetChildrenNode()
        |> ReactTestTool.createSnapshotAndMatch;
      })
    );

    describe("should remove from script components", () => {
      beforeEach(() => {
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setFirstCubeToBeCurrentSceneTreeNode,
        );

        MainEditorInspectorAddComponentTool.addScriptComponent();
      });

      test("test", () => {
        let script = GameObjectTool.getCurrentSceneTreeNodeScript();
        let assetTreeData =
          MainEditorAssetTreeTool.BuildAssetTree.buildEmptyAssetTree();
        let addedNodeId = MainEditorAssetIdTool.getNewAssetId();
        MainEditorAssetHeaderOperateNodeTool.addScriptAttribute();
        MainEditorScriptAttributeTool.addScriptAttribute(
          ~script,
          ~send=SinonTool.createOneLengthStub(sandbox^),
          (),
        );

        MainEditorAssetHeaderOperateNodeTool.removeScriptAttributeNode(
          ~scriptAttributeNodeId=addedNodeId,
          (),
        );

        MainEditorSceneTreeTool.Select.selectGameObject(
          ~gameObject=GameObjectTool.unsafeGetCurrentSceneTreeNode(),
          (),
        );
        BuildComponentTool.buildInspectorComponent(
          TestTool.buildEmptyAppState(),
          InspectorTool.buildFakeAllShowComponentConfig(),
        )
        |> ReactTestTool.createSnapshotAndMatch;
      });
    });
  });