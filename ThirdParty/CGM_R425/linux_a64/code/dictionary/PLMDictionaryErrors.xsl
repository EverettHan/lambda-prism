<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Edited by XMLSpy® -->
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
  <html>
  <body>
	<a href="http://plminf2e/plminf_plmdico_wiki/index.html"><img src="http://plminf2e/plminf_plmdico_wiki/PLMDictionaryBanner.png" border="0"/></a>
    <h2>Results of PLMDictionaryCheck...(<xsl:value-of select="count(/AllErrors/Error)"/>)</h2>
    <table border="0" cellspacing="10">
      <tr bgcolor="#fff5d7">
        <th>errorNo</th>
		<th>error Message</th>
        <th>Metadata</th>
		<th>Element</th>
      </tr>
	  <xsl:for-each select="AllErrors/Error">
		  <xsl:sort select="attribute::metadata"/>
		  <xsl:variable name="j" select="attribute::errorNo"/>
	      <tr>
			<td valign="top"><b><xsl:value-of select="attribute::errorNo"/></b></td>
			<xsl:if test="substring($j,1,1) = 'C'">
			
		        <td><xsl:copy-of select="document('PLMDictionaryDeclarationConstraints.xml')/AllConstraints/ConstraintSet/Constraint[@errorNo=$j]"/></td>
				<td><xsl:value-of select="attribute::metadata"/></td>
				<td><xsl:value-of select="attribute::elementName"/> <font size="-2"> (<xsl:value-of select="attribute::uuid"/>)</font></td>
				
			</xsl:if>
			<xsl:if test="substring($j,1,1) = 'D'">
			
		        <td>
				
					<xsl:copy-of select="document('PLMDictionaryMlcConstraints.xml')/AllMlcConstraints/mlcConstraint[@errorNo=$j]"/>
				</td>
				<td><xsl:value-of select="attribute::metadata"/></td>
				<td>
						<font size="-1"><xsl:value-of select="attribute::xPath"/></font>
					
				</td>
				
			</xsl:if>
			
		</tr>
	 </xsl:for-each>

    </table>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>
