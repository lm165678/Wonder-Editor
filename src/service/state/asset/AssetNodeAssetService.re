open AssetTreeNodeType;
open AssetNodeType;

let _getTreeNodeName = (index, state) =>
  index === (state |> AssetTreeRootAssetService.getRootTreeNodeId) ?
    "Asset" : "newFolder";

let buildFolderResult = (index, state) => {
  name: _getTreeNodeName(index, state),
};

let renameFolderNodeResult = (name, folderNodeResult: folderResultType) => {
  ...folderNodeResult,
  name,
};

let buildJsonNodeResult = (fileResult: nodeResultType) => {
  name: fileResult.name,
  jsonResult: fileResult.result,
};

let renameJsonNodeResult = (name, jsonNodeResult) => {
  ...jsonNodeResult,
  name,
};

/* TODO rename textureId to textureIndex */
let buildTextureNodeResult = textureId => {textureId: textureId};

let buildAssetTreeNodeByIndex = (index, type_) => {
  id: index,
  type_,
  children: [||],
};