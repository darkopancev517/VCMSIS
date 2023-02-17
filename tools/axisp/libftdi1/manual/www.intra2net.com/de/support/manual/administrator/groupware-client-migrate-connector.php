<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Migration vom Intranator Groupware Connector | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client.php" title="Teil&nbsp;3.&nbsp;Groupware Client"><link rel="prev" href="groupware-client-compatibility-other.php" title="23.4. Sonstige Programme"><link rel="next" href="groupware-client-migrate-connector-automatic.php" title="24.2. Die automatische Migration">
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

<a href="groupware-client-migrate-connector.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-migrate-connector.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">24. Kapitel - Migration vom Intranator Groupware Connector</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-compatibility-other.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;3.&nbsp;Groupware Client</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-migrate-connector-automatic.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="groupware-client-migrate-connector"></a>24. Kapitel - Migration vom Intranator Groupware Connector</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="groupware-client-migrate-connector.php#groupware-client-migrate-connector-overview">24.1. Wahl des Migrationsverfahrens</a></span></dt><dt><span class="sect1"><a href="groupware-client-migrate-connector-automatic.php">24.2. Die automatische Migration</a></span></dt><dd><dl><dt><span class="sect2"><a href="groupware-client-migrate-connector-automatic.php#groupware-client-migrate-connector-automatic-overview">24.2.1. &Uuml;berblick</a></span></dt><dt><span class="sect2"><a href="groupware-client-migrate-connector-automatic.php#groupware-client-migrate-connector-automatic-steps">24.2.2. Die Migration in einzelnen Schritten</a></span></dt></dl></dd><dt><span class="sect1"><a href="groupware-client-migrate-connector-manual.php">24.3. Die manuelle Migration</a></span></dt><dd><dl><dt><span class="sect2"><a href="groupware-client-migrate-connector-manual.php#groupware-client-migrate-connector-manual-overview">24.3.1. &Uuml;berblick</a></span></dt><dt><span class="sect2"><a href="groupware-client-migrate-connector-manual.php#groupware-client-migrate-connector-manual-steps">24.3.2. Die Migration in einzelnen Schritten</a></span></dt></dl></dd></dl></div><a class="indexterm" name="groupware-client-migrate-connector1"></a><a class="indexterm" name="groupware-client-migrate-connector2"></a><a class="indexterm" name="groupware-client-migrate-connector3"></a><p>Wenn Sie bisher den Intranator Groupware Connector verwenden und nun auf den Intra2net
        Groupware Client umsteigen m&ouml;chten, gehen Sie am besten wie im Folgenden beschrieben
        vor.</p><p>Die Migration der Daten auf dem Client PC durch den Intra2net Groupware Client ist n&ouml;tig,
        um die Daten vollst&auml;ndig in das neue Datenformat des Intra2net Groupware Clients zu
        &uuml;bertragen. W&uuml;rde stattdessen nur ein neues Profil mit dem Intra2net Groupware Client
        eingerichtet und die Daten ohne Migration vom Server eingelesen, w&uuml;rden Teile der Daten
        verloren gehen (z.B. alle Serientermine). Nur durch die im Folgenden beschriebenen
        Migrationsschritte ist sichergestellt, dass es nicht zu Datenverlust kommt.</p><p>Der parallele Einsatz des Groupware Connectors und des Groupware Clients ist nur m&ouml;glich,
        wenn sichergestellt ist, dass beide nicht auf die selben Daten zugreifen.</p><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-migrate-connector-overview"></a>24.1. Wahl des Migrationsverfahrens</h2></div></div></div><p>Die Migration kann entweder automatisch oder manuell erfolgen.</p><p>Bei der automatischen Migration werden alle Daten aus der Datendatei des alten
            Groupware Connectors vollautomatisch auf den Intranator Server migriert. Der Vorteil
            davon ist, dass bei vielen Groupwareordnern weniger manuelle Schritte durch den Benutzer
            vorgenommen werden m&uuml;ssen. Nachteilig dagegen ist, dass das Verfahren eine konsistente
            Datendatei voraussetzt und bei Fehlern in der Datendatei aus Sicherheitsgr&uuml;nden
            blockieren kann. Manuelle Eingriffsm&ouml;glichkeiten in den Migrationsprozess bestehen
            nicht.</p><p>Bei der manuellen Migration werden die zu migrierenden Daten auf dem Server gel&ouml;scht,
            von Hand per Drag&amp;Drop Ordner f&uuml;r Ordner in den Groupware Client &uuml;bernommen und
            auf den Server synchronisiert. Hierbei muss der Benutzer alle n&ouml;tigen Schritte von Hand
            ausf&uuml;hren und hat daher die volle Kontrolle &uuml;ber den Prozess.</p><p>Beide Verfahren werden in den folgenden Abschnitten im Detail beschrieben.</p></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-compatibility-other.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-migrate-connector-automatic.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">23.4. Sonstige Programme&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;24.2. Die automatische Migration</td></tr></table></div>
      
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