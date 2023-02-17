<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Zertifikate importieren | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-macosx.php" title="44. Kapitel - VPN mit Mac OS X"><link rel="prev" href="vpn-macosx-cert-create.php" title="44.2. Zertifikate erzeugen"><link rel="next" href="vpn-macosx-connection.php" title="44.4. Verbindungen konfigurieren">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-macosx-cert-import.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-macosx-cert-import.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">44.3. Zertifikate importieren</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-macosx-cert-create.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">44. Kapitel - VPN mit Mac OS X</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-macosx-connection.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-macosx-cert-import"></a>44.3. Zertifikate importieren</h2></div></div></div><div class="orderedlist"><ol type="1"><li><p>Starten Sie <span class="application">IPSecuritas</span> und &ouml;ffnen das Men&uuml;
            <span class="guimenu">Certificates</span>, <span class="guisubmenu">Edit certificates</span>.</p><div class="mediaobject"><img src="../images/vpn/macosx/cert_mgr.png"></div></li><li><p>Klicken Sie links unten auf das <span class="guibutton">Importieren</span>-Symbol.</p></li><li><p>W&auml;hlen Sie die Datei mit dem eigenen Zertifikat (im Beispiel
            <code class="filename">newcert.pem</code>) und stellen den Typ auf <span class="guimenuitem">PEM/DER encoded
            own certificate</span>.</p><div class="mediaobject"><img src="../images/vpn/macosx/cert_import_own.png"></div></li><li><p>Als n&auml;chstes werden Sie nach der Datei mit dem passenden privaten Schl&uuml;ssel gefragt
          (im Beispiel <code class="filename">private_key.pem</code>). Ein Passwort ist nicht
          notwendig.</p><div class="mediaobject"><img src="../images/vpn/macosx/cert_import_private.png"></div><p>Neuere Versionen von <span class="application">IPSecuritas</span>
          erwarten, da&szlig; Schl&uuml;ssel und Zertifikat gemeinsam im Format
          PKCS&nbsp;12 vorliegen.
          Anstelle der Dateien <code class="filename">newcert.pem</code> und
          <code class="filename">private_key.pem</code> mu&szlig; dann, wie im letzten
          Abschnitt beschrieben, die Datei <code class="filename">newcert.p12</code>
          ausgew&auml;hlt und der Zertifikatstyp auf <span class="guimenuitem">PKCS#12
            Datei</span> gesetzt werden.
          Au&szlig;erdem tragen Sie das bei der Erstellung verwendete Passwort in das
          entsprechende Feld ein.</p></li><li><p>Das importierte Zertifikat wird im Zertifikatsmanager angezeigt.</p><div class="mediaobject"><img src="../images/vpn/macosx/cert_mgr_show_own.png"></div></li><li><p>&Ouml;ffnen Sie das eigene Zertifikat (z.B. <code class="filename">newcert.pem</code>) in einem
          Texteditor und &uuml;bernehmen den Inhalt in die Zwischenablage. &Ouml;ffnen Sie im Intranator das
          Men&uuml; System&nbsp;&gt;&nbsp;Schl&uuml;ssel&nbsp;&gt;&nbsp;Fremde
          Schl&uuml;ssel und legen einen neuen an. Geben Sie dem Schl&uuml;ssel einen Namen (z.B. den des
          Benutzers) und kopieren Sie die
          Zertifikatsdaten aus der Zwischenablage in das Feld <span class="guilabel">Copy &amp; Paste
            Schl&uuml;ssel</span>.</p></li><li><p>&Ouml;ffnen Sie im Intranator das Men&uuml;
          System&nbsp;&gt;&nbsp;Schl&uuml;ssel&nbsp;&gt;&nbsp;Eigene
          Schl&uuml;ssel&nbsp;:&nbsp;Daten. W&auml;hlen Sie das gew&uuml;nschte Zertifikat aus und
          exportieren es &uuml;ber den Men&uuml;punkt <span class="guimenuitem">Zertifikat exportieren</span> in
          eine .pem-Datei.</p></li><li><p>W&auml;hlen Sie im <span class="guimenu">Certificate Manager</span> von
            <span class="application">IPSecuritas</span> wieder die
          <span class="guimenuitem">Import</span>-Funktion. Importieren Sie die eben vom Intranator
          gespeicherte Zertifikatsdatei und stellen den Typ auf <span class="guimenuitem">PEM/DER encoded foreign
            certificate</span>.</p><div class="mediaobject"><img src="../images/vpn/macosx/cert_import_foreign.png"></div></li><li><p>Das importierte Zertifikat wird im Zertifikatsmanager angezeigt.</p><div class="mediaobject"><img src="../images/vpn/macosx/cert_mgr_show_foreign.png"></div></li></ol></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-macosx-cert-create.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-macosx.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-macosx-connection.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">44.2. Zertifikate erzeugen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;44.4. Verbindungen konfigurieren</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>