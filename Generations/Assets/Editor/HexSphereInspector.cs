using UnityEngine;
using UnityEditor;
using Generations;

namespace GenerationsEditor
{
    [CustomEditor(typeof(HexSphere))]
    public class HexSphereInspector : Editor
    {
        public override void OnInspectorGUI()
        {
            this.DrawDefaultInspector();

            if (GUILayout.Button("Rebuild"))
            {
                //this.serializedObject.FindProperty("");
                EditorApplication.delayCall += ((HexSphere)this.target).RebuildGrid;
            }
        }
    }
}