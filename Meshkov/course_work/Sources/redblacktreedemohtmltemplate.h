#pragma once

constexpr const char *redBlackTreeDemoHtmlTemplateTopPart = R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Red-Black Tree Demo</title>
    <style>
      html {
        background-color: #faf9f5;
        font-family: sans-serif;
      }
      body {
        /* max-width: 600px; */
        margin: 0 auto;
        padding: 0 20px 20px;
      }
      h1 {
        text-align: center;
        letter-spacing: 3px;
        margin: 0;
        padding: 30px 0;
      }
      .red-node, .black-node {
        padding: 5px 10px;
        margin: 4px;
        border-radius: 100px; // TOFIX
      }
      .red-node {
        background-color: rgb(150,0,0);
        color: rgba(255, 255, 255, 0.9);
      }
      .black-node {
        background-color: #2f3437;
        color: rgba(255, 255, 255, 0.9);
      }
      .black-node.highlighted {
        box-shadow: 0 0 3px 3px dodgerblue;
      }
      .red-node.highlighted {
        box-shadow: 0 0 3px 4px coral;
      }
      .tree, .root, .children, .red-node, .black-node {
        display: inline-block;
      }
      .root {
        display: flex;
        justify-content: center;
      }
      .root > * {
        flex-grow: 0;
      }
      .children {
        display: flex;
        justify-content: center;
        align-items: flex-start;
      }
      .children > * {
        flex-grow: 0;
      }
      .tree-holder {
        position: relative;
        padding: 10px;
        text-align:center;
      }
      .tree-holder > canvas {
        position: absolute;
        z-index: -1;
      }
      .text, .heading {
        line-height: 1.5;
        letter-spacing: 1px;
        max-width: 600px;
        margin: 0 auto;
      }
      hr {
        width: 75%;
        border-top-width: 0px;
        max-width: calc(600px * 0.75);
      }
      .heading {
        text-align: center;
        font-weight: bold;
        margin: 8px auto 8px;
      }
    </style>
  </head>
  <body>
    <h1>Red-Black Tree Demo</h1>
)";

constexpr const char *redBlackTreeDemoHtmlTemplateBottomPart = R"(
  <script>
    let treeHolders = document.getElementsByClassName("tree-holder");
    for (let treeHolder of treeHolders) {
      let canvas = document.createElement("canvas")
      treeHolder.insertBefore(canvas, treeHolder.firstChild)
      let context = canvas.getContext('2d')

      let mainTree = treeHolder.querySelector(":scope > .tree")
      if (mainTree == null)
        continue
      let dpr = window.devicePixelRatio || 1 // fallback to 1
      canvas.style.width = mainTree.offsetWidth + 'px'
      canvas.style.height = mainTree.offsetHeight + 'px'
      canvas.width = mainTree.offsetWidth * dpr
      canvas.height = mainTree.offsetHeight * dpr
      context.scale(dpr, dpr)

      context.lineWidth = 2
      context.strokeStyle = "#5f6d70"

      let trees = treeHolder.querySelectorAll(".tree")
      for (let tree of trees) {
        let root = tree.querySelector(":scope > .root").firstElementChild
        let children = tree.querySelector(":scope > .children").children

        let canvasX = canvas.getBoundingClientRect().left
        let canvasY = canvas.getBoundingClientRect().top
        let rootX = root.getBoundingClientRect().left + root.offsetWidth / 2
        let rootY = root.getBoundingClientRect().top + root.offsetHeight / 2

        for (var child of children) {
          if (child.classList.contains("tree")) {
            child = child.querySelector(":scope > .root").firstElementChild
          }
          let childX = child.getBoundingClientRect().left + child.offsetWidth / 2
          let childY = child.getBoundingClientRect().top + child.offsetHeight / 2

          context.beginPath()
          context.moveTo(rootX - canvasX, rootY - canvasY)
          context.lineTo(childX - canvasX, childY - canvasY)
          context.closePath()
          context.stroke()
        }
      }
    }
  </script>

  </body>
</html>
)";
