<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:template match="/">
    <html>
      <head>
        <title>Visual quality management</title>
        <style>  
          th {
          text-align: left;
          }
        </style>
      </head>
      <body>
        <h1>Visu quality preset definitions:</h1>
        <xsl:for-each select="VisRenderQuality/VisRenderQualityDef">

          <h2>
            For version,
            <xsl:value-of select="@MajorVersion"/>.<xsl:value-of select="@MinorVersion"/>.
          </h2>

          <h3>Parameter declaration:</h3>
          <table border="1">
            <tr bgcolor="#9acd32">
              <th>Name</th>
              <th>Type</th>
              <th>Range</th>
            </tr>
            <xsl:for-each select="ParamGroup">
              <tr>
                <th colspan="3" bgcolor="#e6e6e6">
                  <xsl:value-of select="@Name"/>
                </th>
              </tr>
              <xsl:for-each select="Param">
                <tr>
                  <td>
                    <xsl:value-of select="@Name"/>
                  </td>
                  <td>
                    <xsl:value-of select="@Type"/>
                  </td>
                  <xsl:choose>
                    <xsl:when test="@Type='eBool'">
                      <td>true;false</td>
                    </xsl:when>
                    <xsl:otherwise>
                      <td>
                        <xsl:value-of select="@Range"/>
                      </td>
                    </xsl:otherwise>
                  </xsl:choose>
                </tr>
              </xsl:for-each>
            </xsl:for-each>
          </table>

          <h3>Preset definition:</h3>
          <table border="1">
            <tr bgcolor="#9acd32">
              <xsl:for-each select="PresetDef[@Name='Default' and @RenderMode='Static']/@*">
                <th>
                  <xsl:value-of select="name()"/>
                </th>
              </xsl:for-each>
            </tr>
            <xsl:for-each select="PresetDef">
              <tr>
                <th>
                  <xsl:value-of select="@Name"/>
                </th>
                <td>
                  <xsl:value-of select="@RenderMode"/>
                </td>
                <xsl:for-each select="./@*">
                  <xsl:if test="name()!='Name' and name()!='RenderMode'">
                    <td>
                      <xsl:value-of select="."/>
                    </td>
                  </xsl:if>
                </xsl:for-each>
              </tr>
            </xsl:for-each>
          </table>

          <h3>Disabled Parameters:</h3>
          <ul>
            <li>Static mode:</li>
            <ul>
              <xsl:for-each select="DisableParam[@RenderMode='Static']">
                <li>
                  <xsl:value-of select="@Name"/>
                </li>
              </xsl:for-each>
            </ul>
            <li>Dynamic mode:</li>
            <ul>
              <xsl:for-each select="DisableParam[@RenderMode='Dynamic']">
                <li>
                  <xsl:value-of select="@Name"/>
                </li>
              </xsl:for-each>
            </ul>
          </ul>

          <h3>Modified parameter range:</h3>
          <table border="1">
            <tr bgcolor="#9acd32">
              <th>Parameter</th>
              <th>New range</th>
            </tr>
            <xsl:for-each select="ModifyParamRange">
              <tr>
                <th>
                  <xsl:value-of select="@Name"/>
                </th>
                <td>
                  <xsl:value-of select="@Range"/>
                </td>
              </tr>
            </xsl:for-each>
          </table>

          <h3>GPU Optimization:</h3>
          <table border="1">
            <tr bgcolor="#9acd32">
              <th>Preset</th>
              <th>Render mode</th>
              <th>Base preset</th>
              <th>Parameter values</th>
            </tr>
            <xsl:for-each select="GPUOptimization/GPUGroup">
              <tr>
                <th colspan="4">
                  <xsl:value-of select="@GPUs"/>
                </th>
              </tr>
              <xsl:apply-templates select="PresetDef"/>
            </xsl:for-each>
          </table>

          <h3>App override:</h3>
          <table border="1">
            <tr bgcolor="#9acd32">
              <th>Preset</th>
              <th>Render mode</th>
              <th>Base preset</th>
              <th>Parameter values</th>
            </tr>
            <xsl:for-each select="AppOverride">
              <tr>
                <th colspan="4">
                  <xsl:value-of select="@Name"/>
                </th>                
              </tr>
              <xsl:apply-templates select="PresetDef"/>
            </xsl:for-each>
          </table>

        </xsl:for-each>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="PresetDef">
    <tr>
      <td>
        <xsl:value-of select="@Name"/>
      </td>
      <td>
        <xsl:value-of select="@RenderMode"/>
      </td>
      <td>
        <xsl:value-of select="@BasePreset"/>
      </td>
      <td>
        <xsl:for-each select="@*">
          <xsl:if test="name()!='Name' and name()!='RenderMode' and name()!='BasePreset'">
            <xsl:value-of select="name()"/> = <xsl:value-of select="."/><br></br>
          </xsl:if>
        </xsl:for-each>
      </td>
    </tr>
    
  </xsl:template>
  
</xsl:stylesheet>
